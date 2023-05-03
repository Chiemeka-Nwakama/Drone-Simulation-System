#include "WalletDecorator.h"
#include "RobotWallet.h"
#include "AstarStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"

#include <ctime>
#include <cstdlib>

RobotWallet::RobotWallet(Robot* entity_) : WalletDecorator(entity) {
    // initialize money to random amount between 0 and 100
    std::srand(std::time(nullptr));
    money = std::rand() % 101;

    // $100 capacity - standard for drones/robots
    capacity = 100;

    entity = entity_;

    // calculate trip cost
    tripCost = (int) ceil(0.1 * entity->GetPosition().Distance(entity->GetDestination()));
    std::cout << "Robot will pay $" << tripCost << " for this trip." << std::endl;
}

RobotWallet::~RobotWallet() {
    delete entity;
    delete toBank;
}

void RobotWallet::Update(double dt, std::vector<IEntity*> scheduler) {
   // robot does not need funds; can be picked up 
   // only do this if the robot is not already at its destination
   if ((!entity->GetAvailability()) && (money >= tripCost) && (entity->GetPosition().Distance(entity->GetDestination()) >= 4.0)){
    std::cout << entity->GetAvailability() << std::endl;
        std::cout << "Setting avail to true!" << std::endl;
      entity->SetAvailability(true);
   }
   // if robot needs funds and has not started moving to the bank yet
   else if (!toBank && (money < tripCost)){
        std::cout << "Insufficient funds. Visiting bank." << std::endl;
        // find closeset bank
        Vector3 nearestBank = entity->GetNearestBank();
        // set toBank to that location
        std::string strat = entity->GetStrategyName();
        if (strat == "astar")
            toBank = new AstarStrategy(entity->GetPosition(), nearestBank, graph);
        else if (strat == "dfs")
            toBank = new DfsStrategy(entity->GetPosition(), nearestBank, graph);
        else // default to Dijkstra; robots canot do beeline movement
            toBank = new DijkstraStrategy(entity->GetPosition(), nearestBank, graph);
   }
   // robot is moving towards bank
   else if (toBank && !toBank->IsCompleted()){
      toBank->Move(entity, dt);
   }
   // robot is at the bank
   else if (toBank && toBank->IsCompleted()){
      delete toBank;
      toBank = nullptr;
      // recalculate what trip will now cost if pickup is from bank
      tripCost = (int) ceil(0.1 * entity->GetPosition().Distance(entity->GetDestination()));
      std::cout << "From the bank, the robot will now pay $" << tripCost << " for this trip." << std::endl;
      // add only amount that is needed
      Add(tripCost-money);
      entity->SetAvailability(true);
      Remove(tripCost-money); // a little weird; but necessary for data tracking.
   }
   else {
    entity->SetAvailability(false);
   }
}
