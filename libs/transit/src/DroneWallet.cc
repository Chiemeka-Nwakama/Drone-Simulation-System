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
    std::cout << "Checked availability and got nearest entity" << std::endl;

    // Calculate trip cost here
    int cost = 100;

    if (capacity - money < cost) {
        std::cout << "Before move to bank function" << std::endl;
        entity->MoveToBank(dt, scheduler, cost);
        std::cout << "Made it past the move to bank function" << std::endl;
        Remove(money);
    }

    entity->Update(dt, scheduler);
}
