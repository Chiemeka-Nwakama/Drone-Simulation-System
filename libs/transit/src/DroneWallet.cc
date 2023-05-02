#include "WalletDecorator.h"
#include "DroneWallet.h"

DroneWallet::DroneWallet(Drone* entity_) : WalletDecorator(entity) {
    // $100 capacity - standard for drones/robots
    capacity = 100;

    money = 0;
    entity = entity_;
}

DroneWallet::~DroneWallet() {
    delete entity;
}

void DroneWallet::Update(double dt, std::vector<IEntity*> scheduler) {
    if (entity->GetAvailability()) {
        entity->GetNearestEntity(scheduler);
    }

    // Calculate trip cost here
    int cost = 100;

    if (capacity - money < cost) {
        entity->MoveToBank(dt, scheduler, cost);
        Remove(money);
    }

    entity->Update(dt, scheduler);
}
