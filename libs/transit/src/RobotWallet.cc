#include "WalletDecorator.h"
#include "RobotWallet.h"

#include <ctime>
#include <cstdlib>

RobotWallet::RobotWallet(Robot* entity_) : WalletDecorator(entity) {
    // initialize money to random amount between 0 and 100
    std::srand(std::time(nullptr));
    money = std::rand() % 101;

    // $100 capacity - standard for drones/robots
    capacity = 100;

    entity = entity_;

}

RobotWallet::~RobotWallet() {
    delete entity;
}

void RobotWallet::Update(double dt, std::vector<IEntity*> scheduler) {
   
}
