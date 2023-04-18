#ifndef DRONE_WALLET_H_
#define DRONE_WALLET_H_

#include "WalletDecorator.h"
#include "Bank.h" // IMPLEMENT THIS IN FACTORY

/**
 * @brief This class inherits from the WalletDecorator class and constitutes
 * the wallets that will be used by the Drones (Drone simulation drivers). 
 * Drone wallets can deposit money into banks or receive payments.
*/
class DroneWallet : public WalletDecorator {
    protected:
        double capacity;

    public:
        /**
         * @brief Construct a new DroneWallet object
         * 
         * @param strategy the strategy that the entity uses for movement
         * @param entity the entity associated with this wallet
        */
        DroneWallet(IStrategy* strategy, IEntity* entity);

        /**
         * @brief Destructor for the DroneWallet class
        */
        ~DroneWallet();

        /**
         * @brief "Deposit" all of the Drone's money into the bank.
        */
        Deposit();

        /**
         * @brief Receive a payment and increase the DroneWallet's money.
         * 
         * @param amount The payment received/the amount by which the DroneWallet's money will be increased
        */
        ReceivePayment(double amount);

        /**
         * @brief Indicate if the DroneWallet is at its maximum monetary capacity
         * 
         * @return If the DroneWallet cannot hold any more money
        */
        bool IsFull();
}

#endif