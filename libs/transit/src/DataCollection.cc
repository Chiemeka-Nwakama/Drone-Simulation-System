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

//map variables, hold all of the simulation data
static std::map<IEntity*, float> totalDistTrav;
static std::map<IEntity*, int> totalMoney;
static std::map<IEntity*, int> totalDelTrips;
static std::map<IEntity*, int> totalBankTrips;
static std::map<IEntity*, float> robotsAndMoney;
static std::map<IEntity*, int> moneyDeposited;
static std::map<IEntity*, int> bankVisits;

//writeToCSV helpers
static IEntity* droneName;
static IEntity* droneNameWal;
static IEntity* droneNameDelTrip;
static IEntity* droneNameBankTrip;
static IEntity* droneNameDepos;

//tracking the singleton instance and csv file
DataCollection* DataCollection::instance = nullptr;
std::ofstream DataCollection::myfile;

void DataCollection::writeDeliveryDist(IEntity* entity, float dist){
    //if there is nothing entered into the map yet, enter in the first element
    if (totalDistTrav.size() == 0){ 
        totalDistTrav.insert(std::pair<IEntity*, float>(entity, dist));
        droneName = entity; //to help with accessing in CSV
    }
    else {
        totalDistTrav[entity] += dist;  
    }
}   

void DataCollection::writeNumDelTrip(IEntity* entity){
    //if there is nothing entered into the map yet, enter in the first element
    if (totalDelTrips.size() == 0){
   	    int trips = 1;
        totalDelTrips.insert(std::pair<IEntity*, int>(entity, trips));
        droneNameDelTrip = entity;
    }
    else {
        totalDelTrips[entity] += 1;  
    }
}

void DataCollection::writeNumBankTrip(IEntity* entity){
    //if there is nothing entered into the map yet, enter in the first element
    if (totalBankTrips.size() == 0){
   	    int trips = 1;
        totalBankTrips.insert(std::pair<IEntity*, int>(entity, trips));
        droneNameBankTrip = entity;
    }
    else {
        totalBankTrips[entity] += 1;  
    }
}  

void DataCollection::writeRobotMoneyGiven(IEntity* entity, float money){
    //since all robots are different, can just add in the element
    robotsAndMoney.insert(std::pair<IEntity*, float>(entity, money));
}

void DataCollection::writeDroneTotalMoney(IEntity* entity, int money){
    //if there is nothing entered into the map yet, enter in the first element
    if (totalMoney.size() == 0){
        totalMoney.insert(std::pair<IEntity*, int>(entity, money));
        droneNameWal = entity; //to help with accessing in CSV
    }
    else {
        totalMoney[entity] += money;  
    }
}

void DataCollection::writeMoneyDeposited(IEntity* entity, int money){
    //if there is nothing entered into the map yet, enter in the first element
    if (moneyDeposited.size() == 0){
        moneyDeposited.insert(std::pair<IEntity*, int>(entity, money));
        droneNameDepos = entity; //to help with accessing in CSV
    }
    else {
        moneyDeposited[entity] += money;  
    }
}

void DataCollection::writeBankVisit(IEntity* bk){
    //if there is nothing entered into the map yet, enter in the first element
    if (bankVisits.find(bk) == bankVisits.end()){
        bankVisits.insert(std::pair<IEntity*, int>(bk, 1));
    }
    else {
        bankVisits[bk] += 1;
    }
}

double DataCollection::calcDelDistPerTrip(IEntity* entity){
    //if there is nothing entered into the maps, just return zero
    if ((totalDelTrips.size() == 0) && (totalBankTrips.size() == 0)){
        return 0;
    }
    else {
        //takes all of the distance travelled
        double numerator;
        for (auto& i: totalDistTrav){
            numerator += i.second;
        }
        
        //takes all of the trips completed
        double denominator;
        for (auto& i: totalDelTrips){
            denominator += i.second;
        }
        for (auto& i: totalBankTrips){
            denominator += i.second;
        }

        double distper = numerator / denominator;
        return distper;
    }
}

int DataCollection::calcMoneyPerTrip(){ 
    //if there is nothing entered into the maps, just return zero
    if ((totalDelTrips.size() == 0) && (totalBankTrips.size() == 0)){
        return 0;
    }
    else {

        //gets all of the money collected
        int numerator;
        for (auto& i: totalMoney){
            numerator = i.second;
        }
        
        //gets all of the trips completed
        double denominator;
        for (auto& i: totalDelTrips){
            denominator += i.second;
        }
        for (auto& i: totalBankTrips){
            denominator += i.second;
        }

        int moneyper = numerator / denominator;
        return moneyper;
    }
}

int DataCollection::calcMoneyPerDeposit(){ 
    //if there is nothing entered into the map, just return zero
    if (totalBankTrips.size() == 0){
        return 0;
    }
    else {

        //gets all of the money in the bank
        int numerator;
        for (auto& i: moneyDeposited){
            numerator = i.second;
        }
        
        //gets all of the bank trips
        int denominator;
        for (auto& i: totalBankTrips){
            denominator = i.second;
        }

        int moneyper = numerator / denominator;
        return moneyper;
    }
}

int DataCollection::calcPopularBank(){
    //variables for tracking the current greatest bank
    int greatest = 0;
    int returnVal = 0;

    //runs through each bank that has been visited
    for (auto& i: bankVisits){
        if (i.second >= greatest){
            //if the bank has more visits than the last, replace the holder and move to the next index
            greatest = i.second;
            returnVal++;
        }
    }
    //return the index of the bank, will be the same variable as the other
    return returnVal;
}

 void DataCollection::writeToCSV(){
    //std::cout << "write to csv is being called..." << std::endl;

    //file io operations
    ofstream myfile;
    myfile.open("data.csv");

    //prints out the first row, the heading
    myfile << "Enitity, Total Distance, Total Money Collected, Total Delivery Trips, Total Bank Trips, Total Trips, Bank Visits, Total Money Deposited, Trip Cost, Distance per Trip, Money per Trip, Money Per Deposit, Most Popular Bank \n";

    //drone data holders
    float tDist;
    int tMon;
    int tDTrips;
    int tBTrips;
    int tMDep;

    //makes sure that somesort of data has been entered into the map
    //if not, the csv will return 0 in that cell
    if (totalDistTrav.size() == 0){tDist = 0;} else {tDist = totalDistTrav.at(droneName);}
    if (totalMoney.size() == 0){tMon = 0;} else {tMon = totalMoney.at(droneNameWal);}
    if (totalDelTrips.size() == 0){tDTrips = 0;} else {tDTrips = totalDelTrips.at(droneNameDelTrip);}
    if (totalBankTrips.size() == 0){tBTrips = 0;} else {tBTrips = totalBankTrips.at(droneNameBankTrip);}
    if (moneyDeposited.size() == 0){tMDep = 0;} else {tMDep = moneyDeposited.at(droneNameDepos);}

    //calculates the total amount of trips
    int totalTrips = tDTrips + tBTrips;

    //drone data
    myfile << "Drone," << tDist << "," << tMon << "," << tDTrips << "," << tBTrips << "," << totalTrips << ", N/A," << tMDep << ", N/A," << calcDelDistPerTrip(droneName) << "," << calcMoneyPerTrip() << "," << calcMoneyPerDeposit() << "," << calcPopularBank() << "\n";

    //bank data
    int bankCount = 1;
    for (auto& k: bankVisits){
        //only data for banks currently is how many times they have been visited
        myfile << "Bank " << bankCount << "," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << k.second << "," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "\n";
        bankCount++;
    }

    //robot data
    int count = 1;
    for (auto& i: robotsAndMoney){
        //only data for banks currently is how much their trip costed
        myfile << "Robot " << count << "," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << "N/A," << i.second << ", N/A," << "N/A," << "N/A," << "N/A,\n";
        count++;
    }

    //closes the file
    myfile.close();
}
