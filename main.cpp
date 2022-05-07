#include <iostream>
#include <string>
#include <typeinfo>
#include <regex>
#include <iomanip>
#include "helpers.h"

// Constants 
const float ECO_PRICE = 1600.00;
const int SEATS_PER_ROW = 6;
const int TOTAL_SEATS = 50;
const int FLIGHTS = 5;
const int PAIRS = 2;

const std::string flighttimes[FLIGHTS][PAIRS] = 
{
    {"7:00", "9:30"},
    {"9:00", "11:30"},
    {"11:00", "13:30"},
    {"13:00", "15:30"},
    {"15:00", "17:30"},
};

// Structs
struct Seating {
    std::string seat;
    bool occupied;
};

struct Flights {
    int flightnum;
    std::string depart;
    std::string arrive;
    Seating* seats;
};

// Function declarations
std::string getname();
int getflight(Flights &flights);
int getseat(Flights &flight);
Seating* create_seats();
Flights* createflights(const std::string flighttimes[FLIGHTS][PAIRS]);
void display_ticket(std::string name, Flights flight, Seating seat);

int main(){
    // Check if the user is ready to leave the main loop
    bool done = false;
    // Contstruct the flights object that will be used as the main flight data structure
    Flights* flights = createflights(flighttimes);

    while(!done){
        std::string name = getname();
        int flightIndex = getflight(*flights);
        int seat = getseat(flights[flightIndex]);
        display_ticket(name, flights[flightIndex], flights[flightIndex].seats[seat]);

        char cont;
        std::cout << "Do you want to make another booking (Y/N)?" << std::endl;
        std::cin >> cont;

        if(cont == 'N' || cont == 'n') done = true;
    }

    system("pause>0");
    return 0;
}

std::string getname(){
    std::string name;
    std::cout << "Welcome to COS1511 Flight booking system \n\nEnter full name" << std::endl;
    std::getline(std::cin, name);
    std::cout << std::endl;
    return name;
}

int getflight(Flights &flights_pointer){
    int time;
    Flights* flights = &flights_pointer;
    std::string message = "Choose the time by entering the option number from the displayed list:";
    bool valid_time = false;

    std::cout << "The available flight times are:\n\tDepart\tArrive" << std::endl;

    for(int i = 0; i < FLIGHTS; i++){
        std::cout <<  (i + 1) << ".\t" << flights[i].depart << "\t" << flights[i].arrive << std::endl;
    }

    while(!valid_time){

        std::cout << message << std::endl;
        std::cin >> time;

        if(std::cin.good() && (time >= 1 && time <= 5)) valid_time = true;
        else {
            message = "Incorrect option! Please choose from 1-5";
            std::cin.clear();
            std::cin.ignore();
        }
    }
    std::cout << std::endl;

    return time - 1;
}

int getseat(Flights &flight){
    // Flights* targetflight = &flight;
    std::string seat_number;
    int seatNumber;
    std::string message = "Please key in a seat number to choose a seat (eg: A2)";

    std::cout << "The available seats for " << flight.depart << " are as follows:" << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    for(int row = 0; row < TOTAL_SEATS; row++){
         Seating seat = flight.seats[row];

        // Show the prices to the two classes
        if(row  == 0) std::cout << "First Class(" << ECO_PRICE * 1.2 << ')' << std::endl;
        if((row) == SEATS_PER_ROW * 4) std::cout << "Economy Class(" << ECO_PRICE << ')' << std::endl;

        // Show the available seats
        if(seat.occupied == true){
            std::cout << "|**|";
            message = "Seats that are already taken, are indicated with an asterisk\n" + message;
        } 
        else std::cout << "|" << flight.seats[row].seat << "|";

        // Add the spacers to make the content readable
        if((row + 1) % 3 == 0 && !((row + 1) % 6 == 0)) std::cout << "--- ";
        if((row + 1) % 6 == 0) std::cout << std::endl;
    }

    std::cout << "\n" << std::endl;
    while(!std::regex_match(seat_number, std::regex("[A-I]{1}[1-6]{1}"))){
        std::cout << message << std::endl;
        std::cin >> seat_number;
        message = "The seat you entered is not valid. Please choose a valid seat";
        for(int i = 0; i < TOTAL_SEATS; i++){
            Seating seat = flight.seats[i];
            if(seat.seat == seat_number){
                if(seat.occupied) message = "Sorry, the seat is taken please choose a seat that is available";
                else seatNumber = i;
            }
        }
        
    }

    return seatNumber;
}

void display_ticket(std::string name, Flights flight, Seating seat){
    bool isFirstClass = std::regex_match(seat.seat, std::regex("[A-D]{1}[1-6]{1}"));

    int price = isFirstClass ? ECO_PRICE * 1.2 : ECO_PRICE;
    std::string cls = isFirstClass ? "First Class" : "Economy Class";

    std::cout << "*************************" << std::endl;
    std::cout << "Travel Ticket for flight" << std::endl;
    std::cout << "*************************" << std::endl;
    std::cout << "Name\t\t : " << name << "\t\t";
    std::cout << "Travel Ticket Class\t: " << cls << std::endl;
    std::cout << "\t\t\t\t\tSeat No\t\t\t: " << seat.seat << std::endl;
    std::cout << "Departure\t: Johannesburg\t\t";
    std::cout << "Departure time\t\t: " << flight.depart << std::endl;
    std::cout << "Destination\t: Cape Town\t\t";
    std::cout << "Arrival Time\t\t: " << flight.arrive << std::endl;
    std::cout << "*************************" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Amount: R" << price << " Thank you for booking with COS1511. Your travel agent for queries is Jon Snow" << std::endl;
    std::cout << "*************************\n" << std::endl;

}

Seating* create_seats(){
    static Seating seats[TOTAL_SEATS];

    // ASCII value for A
    const int from = 65;
    // ASCII value for I
    const int to = 73;
    int k = 0;
    
    for(int i = 0; i <= (to - from); i++){
        for(int j = 1; j <= SEATS_PER_ROW; j++){
            std::string num = char(i + from) + to_string(j);
            Seating seat = {num, false};
            seats[k] = seat;
            k++;
            if(k > 49) break;
        }
        
    }

    return seats;
}

Flights* createflights(const std::string flighttimes[FLIGHTS][PAIRS]){
    static Flights flights[FLIGHTS];

    for(int i = 0; i < FLIGHTS; i++){
        Seating* seats = create_seats();
        int flightnum = i + 1;
        std::string depart = flighttimes[i][0];
        std::string arrive = flighttimes[i][1];

        Flights flight = {flightnum, depart, arrive, seats};
        flights[i] = flight;
    }

    return flights;
}