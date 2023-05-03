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

    // calculate trip cost; hard coded right now to 30
    tripCost = 30;
}

RobotWallet::~RobotWallet() {
    delete entity;
    delete toBank;
}

void RobotWallet::Update(double dt, std::vector<IEntity*> scheduler) {
   // robot does not need funds; can be picked up 
   if (money >= tripCost){
      std::cout << "Sufficient funds" << std::endl;
      entity->SetAvailability(true);
   }
   // if robot needs funds and has not started moving to the bank yet
   else if (!toBank){
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
   else if (!toBank->IsCompleted()){
      toBank->Move(entity, dt);
   }
   // robot is at the bank
   else {
      delete toBank;
      toBank = nullptr;
      // recalculate what trip will now cost if pickup is from bank
      // TODO THIS WHEN CALCULATION IS DONE
      // add only amount that is needed
      Add(tripCost-money);
      Remove(tripCost-money); // a little weird; but necessary for data tracking.
      entity->SetAvailability(true);
   }
}
