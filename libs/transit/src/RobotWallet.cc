#include "WalletDecorator.h"
#include "RobotWallet.h"
#include "DroneWallet.h"
#include "IEntity.h"

#include <ctime>
#include <cstdlib>

RobotWallet::RobotWallet(IEntity* entity) : WalletDecorator(entity) {
    // initialize money to random amount between 0 and 100
    std::srand(std::time(nullptr));
    money = std::rand() % 101;

}

void RobotWallet::Withdraw(int amount){
    this->money += amount;
}

bool RobotWallet::Pay(int amount, DroneWallet* drone_w){
    // only withdraw money if the wallet has sufficieent funds
    if (money >= amount){
        this->money -= amount;
        drone_w->ReceivePayment(amount);
        return true;
    }
    return false;
}
