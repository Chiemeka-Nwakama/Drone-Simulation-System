#include "WalletDecorator.h"
#include "DroneWallet.h"
#include "BeelineStrategy.h"

DroneWallet::DroneWallet(Drone* entity_) : WalletDecorator(entity) {
    // $100 capacity - standard for drones/robots
    capacity = 100;

    money = 0;
    entity = entity_;
}

DroneWallet::~DroneWallet() {
    delete entity;
    delete toBank;
}

void DroneWallet::Update(double dt, std::vector<IEntity*> scheduler) {
    // if the drone is available, check if it needs to go to the bank
    if (entity->GetAvailability() && (money >= capacity)){
        if (!toBank){ //if not already moving to a bank
            std::cout << "Wallet full! Visiting bank." << std::endl;
            // find closeset bank
            Vector3 nearestBank = entity->GetNearestBank();
            // set toBank to that location
            toBank = new BeelineStrategy(entity->GetPosition(), nearestBank);
        }
        else if (!toBank->IsCompleted()){
          toBank->Move(entity, dt); // move to bank
        }
        else if (toBank->IsCompleted()){
            delete toBank;
            toBank = nullptr;
            Remove(money);
        }
    }
    // otherwise if available, find nearest entity to pick up
    else if (entity->GetAvailability()){
        entity->GetNearestEntity(scheduler);
        // trip will be made if availability has changed; add cost of trip here. 
        if (!entity->GetAvailability()) {
            Add(30);
        }

    }
    // otherwise call Drone update; making trip
    else {
        entity->Update(dt, scheduler);
    }
}
