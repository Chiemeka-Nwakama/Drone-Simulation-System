#define _USE_MATH_DEFINES
using namespace std;

#include "DataCollection.h"
#include "Drone.h"
#include "Robot.h"
#include "IEntity.h"
#include <iostream>
#include <fstream>

#include <cmath>
#include <limits>

#include <map>

static std::map<IEntity*, float> totalDistTrav;
// std::map<Drone, int> totalMoney;
static std::map<IEntity*, int> totalDelTrips;
static std::map<IEntity*, float> robotsAndMoney;

// std::map<Drone, int> totalBankTrips;
// std::map<Drone, int> moneyDeposited;
// std::map<Drone, double> totalDistToBank;
// std::map<Bank, int> numVisits;
// std::map<Robot, int> tripCost;

//writeToCSV helpers
static IEntity* droneName;



DataCollection* DataCollection::instance = nullptr;
std::ofstream DataCollection::myfile;

void  DataCollection::writeDeliveryDist(IEntity* entity, float dist){
    //std::cout << "Distance inputted: " << dist << std::endl;
    if (totalDistTrav.size() == 0){
        totalDistTrav.insert(std::pair<IEntity*, float>(entity, dist));
        droneName = entity; //to help with accessing in CSV
    }
    else {
        totalDistTrav[entity] += dist;  
    }
    std::cout << "Testing distance: " << totalDistTrav[entity] << std::endl;
}   

void  DataCollection::writeNumDelTrip(IEntity* entity){
    if (totalDelTrips.size() == 0){
   	int trips = 1;
        totalDelTrips.insert(std::pair<IEntity*, int>(entity, trips));
    }
    else {
        totalDelTrips[entity] += 1;  
    }
    std::cout << "Testing trip number: " << totalDelTrips[entity] << std::endl;
}  

//not logically functional, adding it for testing with robots
void DataCollection::writeRobotMoneyGiven(IEntity* entity, float money){
    robotsAndMoney.insert(std::pair<IEntity*, float>(entity, money));
    std::cout << "Robot gave this much money: " << robotsAndMoney[entity] << std::endl;
}  

double DataCollection::calcDelDistPerTrip(IEntity* entity){
    double distper = totalDistTrav[entity] / totalDelTrips[entity];
    std::cout << "Delivery Distance per Trip: " << distper << std::endl;
    return distper;
}

 void DataCollection::writeToCSV(){
    std::cout << "write to csv is being called..." << std::endl;

    ofstream myfile;
    myfile.open("data.csv");
    //prints ou the first row, the heading
    myfile << "Enitity, Total Distance, Total Money, Total Trips, Total Money Paid, Money Collected, etc., Distance per Trip, Money per Trip, etc.\n";

    //drone data
    myfile << "Drone," << totalDistTrav.at(droneName) << ",$ HOLDER," << totalDelTrips.at(droneName) << ", N/A," << "$ HOLDER," << "etc.," << calcDelDistPerTrip(droneName) << ",$ HOLDER," << "etc.,\n";

    //bank data
    myfile << "Bank 1," << "N/A," << "N/A," << "N/A," << "N/A," << "$ HOLDER," << "etc.," << "N/A," << "N/A," << "etc.,\n";
    myfile << "Bank 2," << "N/A," << "N/A," << "N/A," << "N/A," << "$ HOLDER," << "etc.," << "N/A," << "N/A," << "etc.,\n";
    myfile << "Bank 3," << "N/A," << "N/A," << "N/A," << "N/A," << "$ HOLDER," << "etc.," << "N/A," << "N/A," << "etc.,\n";
    myfile << "Bank 4," << "N/A," << "N/A," << "N/A," << "N/A," << "$ HOLDER," << "etc.," << "N/A," << "N/A," << "etc.,\n";

    // for (int i = 0; i++; i > robotsAndMoney.size()){
    //     myfile << "Robot " << (i + 1) << "," << "N/A," << "N/A," << "N/A," << robotsAndMoney.at(i) << "," << "N/A," << "etc.," << "N/A," << "N/A," << "etc.,\n";
    // }

    int count = 1;
    for (auto& i: robotsAndMoney){
        myfile << "Robot " << count << "," << "N/A," << "N/A," << "N/A," << i.second << "," << "N/A," << "etc.," << "N/A," << "N/A," << "etc.,\n";
        count++;
    }

    // examples
    // myfile<< "a,b,c,\n";
    // myfile<< "c,s,v,\n";
    // myfile << "1,2,3.456\n";
    // myfile << "semi;colon";
    myfile.close();
}
