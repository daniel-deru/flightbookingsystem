#include <iostream>
#include <string>
#include <typeinfo>
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
    Seating seats[TOTAL_SEATS];
};

// Function declarations
std::string getname();
Flights getflight(Flights &flights);
std::string getseat(Flights flight);
Flights* createflights(const std::string flighttimes[FLIGHTS][PAIRS]);

int main(){
    // Check if the user is ready to leave the main loop
    bool done = false;
    // Contstruct the flights object that will be used as the main flight data structure
    Flights *flights = createflights(flighttimes);
    // std::string name = getname();
    Flights flight = getflight(*flights);
    std::string seat = getseat(flight);

    system("pause>0");
    return 0;
}

std::string getname(){
    std::string name;
    std::cout << "Welcome to COS1511 Flight booking system \n\nEnter full name" << std::endl;
    std::getline(std::cin, name);
    return name;
}

Flights getflight(Flights &flights_pointer){
    int time;
    Flights* flights = &flights_pointer;
    std::string message = "Choose the time by entering the option number from the displayed list:";
    bool valid_time = false;

    std::cout << "The available flight times are:\n\tDepart\tArrive" << std::endl;

    for(int i = 0; i < FLIGHTS; i++){
        std::cout <<  (i + 1) << ".\t" << flights[i].depart << "\t" << flights[i].arrive << std::endl;
    }

    while(!valid_time){

        std::cout << "Incorrect option! Please choose from 1-5" << std::endl;
        std::cin >> time;

        if(std::cin.good() && (time >= 1 && time <= 5)) valid_time = true;
        else {
            std::cin.clear();
            std::cin.ignore();
        }
    }

    return flights[time];
}

std::string getseat(Flights flight){
    std::cout << "The available seats for " << flight.depart << " are as follows:" << std::endl;
     std::cout << "|" << flight.seats[0].seat << "|" << std::endl;
     std::cout << "|" << flight.seats[1].seat << "|" << std::endl;
     std::cout << "|" << flight.seats[2].seat << "|" << std::endl;
     std::cout << "|" << flight.seats[3].seat << "|" << std::endl;
    // for(int row = 0; row <= TOTAL_SEATS; row++){
    //      std::cout << "|" << flight.seats[row]->seat << "|" << std::endl;
    // }
    return "";
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
            if(k >= 49) break;
        }
        
    }

    return seats;
}

Flights* createflights(const std::string flighttimes[FLIGHTS][PAIRS]){
    static Flights flights[FLIGHTS];

    for(int i = 0; i < FLIGHTS; i++){
        static Seating *seats = create_seats();
        int flightnum = i + 1;
        std::string depart = flighttimes[i][0];
        std::string arrive = flighttimes[i][1];

        Flights flight = {flightnum, depart, arrive, *seats};
        // std::cout << flight.seats[1].seat << std::endl;
        flights[i] = flight;
    }

    return flights;
}