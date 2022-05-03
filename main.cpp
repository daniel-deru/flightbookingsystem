#include <iostream>
#include <string>

// Structs
struct {
    std::string depart;
    std::string arrive;
} Flights;

// Function declarations
std::string getname();
int getflight();

// Constants 
const float economy_price = 1600.00;
const int flight_times = 5;
const int flight_pair = 2;
const std::string flights[flight_times][flight_pair] = {
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
        std::string name = getname();
        int flight = getflight();
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

    std::cout << "The available flight times are:\n\tDepart\tArrive" << std::endl;

    for(int i = 0; i < flight_times; i++){
        std::cout <<  (i + 1) << ".\t" << flights[i][0] << "\t" << flights[i][1] << std::endl;
    }

    std::cout << message << std::endl;
    std::cin >> time;

    return time;
}