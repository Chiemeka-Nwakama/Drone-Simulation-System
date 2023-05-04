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
            Vector3 nearestBank = GetNearestBank();
            // set toBank to that location
            toBank = new BeelineStrategy(entity->GetPosition(), nearestBank);

            holdWalletPos = GetPosition();
            
        }
        else if (!toBank->IsCompleted()){
          toBank->Move(entity, dt); // move to bank
        }
        else if (toBank->IsCompleted()){
            delete toBank;
            toBank = nullptr;

            //singleton data collection
            DataCollection* dc = DataCollection::getInstance();
            dc->writeMoneyDeposited(this, money);
            dc->writeNumBankTrip(this);
            dc->writeDeliveryDist(this, holdWalletPos.Distance(GetPosition()));
            
            Remove(money);
        }
    }
    // otherwise if available, find nearest entity to pick up
    else if (entity->GetAvailability()){
        entity->Update(dt, scheduler);
        // trip will be made if availability has changed; add cost of trip here. 
        if (!entity->GetAvailability()) {
            int tripCost = (int) ceil(0.1 * entity->GetTripDistance());
            std::cout << "Drone will be paid $" << tripCost << " for this trip." << std::endl;
            
            //singleton data collection
            DataCollection* dc = DataCollection::getInstance();
            dc->writeDroneTotalMoney(this, tripCost);
            
            Add(tripCost);
        }
    }
    // otherwise call Drone update; making trip
    else {
        entity->Update(dt, scheduler);
    }
}
