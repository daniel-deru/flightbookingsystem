#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>

struct Seating {
    std::string seat;
    bool occupied;
} ;

// Function declarations
std::string getname();
int getflight();
std::string getseat();
Seating* create_seats();
std::string to_string(int a);

// Constants 
const float ECO_PRICE = 1600.00;
const int TOTAL_SEATS = 50;
const int FLIGHTS = 5;
const int PAIRS = 2;
const std::string flights[FLIGHTS][PAIRS] = {
    {"7:00", "9:30"},
    {"9:00", "11:30"},
    {"11:00", "13:30"},
    {"13:00", "15:30"},
    {"15:00", "17:30"},
    };



int main(){
    // Check if the user is ready to leave the main loop
    bool done = false;

    // while(!done){
        // std::string name = getname();
        // int flight = getflight();
        Seating* seats = create_seats();
    // }

    system("pause>0");
    return 0;
}

std::string getname(){
    std::string name;
    std::cout << "Welcome to COS1511 Flight booking system \n\nEnter full name" << std::endl;
    std::getline(std::cin, name);
    return name;
}

int getflight(){
    int time;
    std::string message = "Choose the time by entering the option number from the displayed list:";
    bool valid_time = false;

    std::cout << "The available flight times are:\n\tDepart\tArrive" << std::endl;

    for(int i = 0; i < FLIGHTS; i++){
        std::cout <<  (i + 1) << ".\t" << flights[i][0] << "\t" << flights[i][1] << std::endl;
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

    return time;
}

std::string getseat(){
    return "";
}

Seating* create_seats(){
    static Seating seats[TOTAL_SEATS];
    const int MAX_ROW_NUMS = 6;
    // ASCII value for A
    const int from = 65;
    // ASCII value for I
    const int to = 73;
    int k = 0;
    for(int i = 0; i <= (to - from); i++){
        for(int j = 1; j <= MAX_ROW_NUMS; j++){
            std::string num = char(i + from) + to_string(j);
            // std::cout << num << std::endl;
            Seating seat = {num, false};
            seats[k] = seat;
            if(k >= 49) break;
            k++;
        }
        
    }

    return seats;
}

std::string to_string(int a){
    std::ostringstream s;
    s << a;
    return s.str();
}

