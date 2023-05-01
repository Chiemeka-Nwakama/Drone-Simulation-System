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

static std::map<IEntity*, float> totalDistTrav;
// std::map<Drone, int> totalMoney;
static std::map<IEntity*, int> totalDelTrips;

// std::map<Drone, int> totalBankTrips;
// std::map<Drone, int> moneyDeposited;
// std::map<Drone, double> totalDistToBank;
// std::map<Bank, int> numVisits;
// std::map<Robot, int> tripCost;





DataCollection* DataCollection::instance = nullptr;
std::ofstream DataCollection::myfile;

void  DataCollection::writeDeliveryDist(IEntity* entity, float dist){
    //std::cout << "Distance inputted: " << dist << std::endl;
    if (totalDistTrav.size() == 0){
        totalDistTrav.insert(std::pair<IEntity*, float>(entity, dist));
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

double DataCollection::calcDelDistPerTrip(IEntity* entity){
    double distper = totalDistTrav[entity] / totalDelTrips[entity];
    std::cout << "Delivery Distance per Trip: " << distper << std::endl;
    return distper;
}

 void DataCollection::writeToCSV(){
    myfile.open("data.csv");
    //prints ou the first row, the heading
    myfile << "Enitity, Total Distance, Total Money, Total Trips, Total Money Paid, Money Collected, etc., Distance per Trip, Money per Trip, etc.\n";
    

    // examples
    myfile<< "a,b,c,\n";
    myfile<< "c,s,v,\n";
    myfile << "1,2,3.456\n";
    myfile << "semi;colon";
    myfile.close();
}
