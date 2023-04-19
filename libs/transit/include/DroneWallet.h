#ifndef DRONE_WALLET_H_
#define DRONE_WALLET_H_

#include "WalletDecorator.h"
#include "IEntity.h"

/**
 * @brief This class inherits from the WalletDecorator class and constitutes
 * the wallets that will be used by the Drones (Drone simulation drivers). 
 * Drone wallets can deposit money into banks or receive payments.
*/
class DroneWallet : public WalletDecorator {
    protected:
        int capacity;

    public:
        /**
         * @brief Construct a new DroneWallet object
         * 
         * @param entity the entity associated with this wallet
        */
        DroneWallet(IEntity* entity);

        /**
         * @brief Destructor for the DroneWallet class
        */
        ~DroneWallet();

        /**
         * @brief "Deposit" all of the Drone's money into the bank.
        */
        void Deposit();

        /**
         * @brief Receive a payment and increase the DroneWallet's money.
         * 
         * @param amount The payment received/the amount by which the DroneWallet's money will be increased
        */
        void ReceivePayment(int amount);

        /**
         * @brief Indicate if the DroneWallet is at its maximum monetary capacity
         * 
         * @return If the DroneWallet cannot hold any more money
        */
        bool IsFull();
};

#endif