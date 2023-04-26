#define _USE_MATH_DEFINES

#include "DataCollection.h"
#include "Drone.h"
#include "Robot.h"
#include "IEntity.h"

#include <cmath>
#include <limits>

std::map<Drone*, float> totalDistTrav;
// std::map<Drone, int> totalMoney;
// std::map<Drone, int> totalDelTrips;
// std::map<Drone, int> totalBankTrips;
// std::map<Drone, int> moneyDeposited;
// std::map<Drone, double> totalDistToBank;
// std::map<Bank, int> numVisits;
// std::map<Robot, int> tripCost;

void writeDeliveryDist(Drone* dr, float dist){
    if (totalDistTrav.size() == 0){
        totalDistTrav.insert(std::pair<Drone*, float>(dr, dist));
    }
    else {
        totalDistTrav[dr] += dist;  
    }
    //std::cout << "Testing distance: " << totalDistTrav[drone] << std::endl;
}   