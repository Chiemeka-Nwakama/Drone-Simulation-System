#include "WalletDecorator.h"
#include "RobotWallet.h"
#include "Robot.h"
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
    entity->SetTripDistance(entity->GetPosition().Distance(entity->GetDestination())); // set trip distance
    tripCost = (int) ceil(0.1 * entity->GetTripDistance());
    std::cout << "Robot will pay $" << tripCost << " for this trip." << std::endl;
    start = true;
}

RobotWallet::~RobotWallet() {
    delete entity;
    delete toBank;
}

void RobotWallet::Update(double dt, std::vector<IEntity*> scheduler) {
   // robot does not need funds; can be picked up 
   if (start){
        if ((money >= tripCost)){
            Remove(tripCost);  
            entity->SetAvailability(true);
            start = false; // update function should now do nothing
        }
        // if robot needs funds and has not started moving to the bank yet
        else if ((!toBank) && (money < tripCost)){
                std::cout << "Insufficient funds. Visiting bank." << std::endl;
                Vector3 nearestBank = GetNearestBank();
                std::string strat = entity->GetStrategyName(); // set toBank to that location
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
            entity->SetTripDistance(entity->GetPosition().Distance(entity->GetDestination())); // set trip distance
            std::cout << entity->GetTripDistance() << std::endl;
            tripCost = (int) ceil(0.1 * entity->GetTripDistance());
            std::cout << "From the bank, the robot will now pay $" << tripCost << " for this trip." << std::endl;
            Add(tripCost-money); // add only amount that is needed
            entity->SetAvailability(true);
            Remove(tripCost); // a little weird; but necessary for data tracking.
            start = false; // update function should now do nothing
        }
   }
}
