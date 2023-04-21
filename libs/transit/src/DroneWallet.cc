#include "DroneWallet.h"
#include "WalletDecorator.h"
#include "IEntity.h"

DroneWallet::DroneWallet(IEntity* entity) : WalletDecorator(entity) {
    // arbitrary capacity
    capacity = 100;
    money = 0;
}

void DroneWallet::Deposit() { money = 0; }

void DroneWallet::ReceivePayment(int amount){
    money += amount;
}

bool DroneWallet::IsFull(){
    // possible that receiving a payment surpasses capacity
    return money >= capacity;
}
