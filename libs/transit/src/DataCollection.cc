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
static std::map<IEntity*, int> totalMoney;
static std::map<IEntity*, int> totalDelTrips;
static std::map<IEntity*, int> totalBankTrips;
static std::map<IEntity*, float> robotsAndMoney;
static std::map<IEntity*, int> moneyDeposited;

// std::map<Drone, double> totalDistToBank;
// std::map<Bank, int> numVisits;
// std::map<Robot, int> tripCost;

//writeToCSV helpers
static IEntity* droneName;
static IEntity* droneNameWal;
static IEntity* droneNameDelTrip;
static IEntity* droneNameBankTrip;
static IEntity* droneNameDepos;

//bank visit helpers
int bank1Visits = 0;
int bank2Visits = 0;
int bank3Visits = 0;
int bank4Visits = 0;



DataCollection* DataCollection::instance = nullptr;
std::ofstream DataCollection::myfile;

void DataCollection::writeDeliveryDist(IEntity* entity, float dist){
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

void DataCollection::writeNumDelTrip(IEntity* entity){
    if (totalDelTrips.size() == 0){
   	int trips = 1;
        totalDelTrips.insert(std::pair<IEntity*, int>(entity, trips));
        droneNameDelTrip = entity;
    }
    else {
        totalDelTrips[entity] += 1;  
    }
    std::cout << "Testing delivery trip number: " << totalDelTrips[entity] << std::endl;
}

void DataCollection::writeNumBankTrip(IEntity* entity){
    if (totalBankTrips.size() == 0){
   	int trips = 1;
        totalBankTrips.insert(std::pair<IEntity*, int>(entity, trips));
        droneNameBankTrip = entity;
    }
    else {
        totalBankTrips[entity] += 1;  
    }
    std::cout << "Testing bank trip number: " << totalBankTrips[entity] << std::endl;
}  

//not logically functional, adding it for testing with robots
void DataCollection::writeRobotMoneyGiven(IEntity* entity, float money){
    robotsAndMoney.insert(std::pair<IEntity*, float>(entity, money));
    std::cout << "Robot gave this much money: " << robotsAndMoney[entity] << std::endl;
}

void DataCollection::writeDroneTotalMoney(IEntity* entity, int money){
    if (totalMoney.size() == 0){
        totalMoney.insert(std::pair<IEntity*, int>(entity, money));
        droneNameWal = entity; //to help with accessing in CSV
    }
    else {
        totalMoney[entity] += money;  
    }
    std::cout << "Testing total money paid: " << totalMoney[entity] << std::endl;
}

void DataCollection::writeMoneyDeposited(IEntity* entity, int money){
    if (moneyDeposited.size() == 0){
        moneyDeposited.insert(std::pair<IEntity*, int>(entity, money));
        droneNameDepos = entity; //to help with accessing in CSV
    }
    else {
        moneyDeposited[entity] += money;  
    }
    std::cout << "Testing total money paid: " << moneyDeposited[entity] << std::endl;
}

void DataCollection::writeBankVisit(int check){
    if (check == 0){bank1Visits++;}
    else if (check == 1){bank2Visits++;}
    else if (check == 2){bank3Visits++;}
    else if (check == 3){bank4Visits++;}
    else {std::cout << "something went wrong in bank visits..." << std::endl;}
}

double DataCollection::calcDelDistPerTrip(IEntity* entity){
    //double distper = totalDistTrav[entity] / (totalDelTrips[entity] + totalBankTrips[entity]);
    
    double numerator;
    for (auto& i: totalDistTrav){
        numerator += i.second;
    }
    
    double denominator;
    for (auto& i: totalDelTrips){
        denominator += i.second;
    }
    for (auto& i: totalBankTrips){
        denominator += i.second;
    }

    double distper = numerator / denominator;
    std::cout << "Delivery Distance per Trip: " << distper << std::endl;
    return distper;
}

int DataCollection::calcMoneyPerTrip(){ 
    //double distper = totalDistTrav[entity] / (totalDelTrips[entity] + totalBankTrips[entity]);
    std::cout << "--------------------" << std::endl;
    int numerator;
    for (auto& i: totalMoney){numerator += i.second;}
    std::cout << "mpt numerator: " << numerator << std::endl;
    
    int denominator;
    for (auto& i: totalDelTrips){denominator += i.second;}
    for (auto& i: totalBankTrips){denominator += i.second;}
    std::cout << "mpt denominator: " << denominator << std::endl;

    int moneyper = numerator / denominator;
    std::cout << "Money per Trip: " << moneyper << std::endl;
    std::cout << "--------------------" << std::endl;
    return moneyper;
}

int DataCollection::calcMoneyPerDeposit(){ 
    //double distper = totalDistTrav[entity] / (totalDelTrips[entity] + totalBankTrips[entity]);
    
    int numerator;
    for (auto& i: moneyDeposited){numerator += i.second;}
    //std::cout << "mpt numerator: " << numerator << std::endl;
    
    int denominator;
    for (auto& i: totalBankTrips){denominator += i.second;}
    //std::cout << "mpt denominator: " << denominator << std::endl;

    int moneyper = numerator / denominator;
    std::cout << "Money per Deposit: " << moneyper << std::endl;
    return moneyper;
}

int DataCollection::calcPopularBank(){
    int greatest = bank1Visits;
    if (bank2Visits > greatest){greatest = bank2Visits;}
    if (bank3Visits > greatest){greatest = bank3Visits;}
    if (bank4Visits > greatest){greatest = bank4Visits;}
    return greatest;
}

 void DataCollection::writeToCSV(){
    std::cout << "write to csv is being called..." << std::endl;

    ofstream myfile;
    myfile.open("data.csv");
    //prints ou the first row, the heading
    myfile << "Enitity, Total Distance, Total Money Collected, Total Delivery Trips, Total Bank Trips, Total Trips, Bank Visits, Total Money Deposited, Trip Cost, Distance per Trip, Money per Trip, Money Per Deposit, Most Popular Bank \n";

    //drone data
    float tDist;
    int tMon;
    int tDTrips;
    int tBTrips;
    int tMDep;

    if (totalDistTrav.size() == 0){tDist = 0;} else {tDist = totalDistTrav.at(droneName);}
    if (totalMoney.size() == 0){tMon = 0;} else {tMon = totalMoney.at(droneNameWal);}
    if (totalDelTrips.size() == 0){tDTrips = 0;} else {tDTrips = totalDelTrips.at(droneNameDelTrip);}
    if (totalBankTrips.size() == 0){tBTrips = 0;} else {tBTrips = totalBankTrips.at(droneNameBankTrip);}
    if (moneyDeposited.size() == 0){tMDep = 0;} else {tMDep = moneyDeposited.at(droneNameDepos);}

    int totalTrips = tDTrips + tBTrips;
    myfile << "Drone," << tDist << "," << tMon << "," << tDTrips << "," << tBTrips << "," << totalTrips << ", N/A," << tMDep << ", N/A," << calcDelDistPerTrip(droneName) << "," << calcMoneyPerTrip() << "," << calcMoneyPerDeposit() << "," << calcPopularBank() << "\n";

    //bank data
    myfile << "Bank 1," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << bank1Visits << "," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "\n";
    myfile << "Bank 2," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << bank2Visits << "," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "\n";
    myfile << "Bank 3," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << bank3Visits << "," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "\n";
    myfile << "Bank 4," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << bank4Visits << "," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "\n";
    
    //robot data
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
