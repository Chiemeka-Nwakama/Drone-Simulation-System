#ifndef ROBOT_WALLET_H_
#define ROBOT_WALLET_H_

#include "WalletDecorator.h"
#include "IEntity.h"
#include "DroneWallet.h"

/**
 * @brief This class inherits from the WalletDecorator class and constitutes
 * the wallets that will be used by the Robots (Drone simulation passengers). 
 * Robot wallets can withdraw money from banks or make payments to Drone wallets.
*/
class RobotWallet : public WalletDecorator {
    public:
        /**
         * @brief Construct a new RobotWallet object
         * 
         * @param entity the entity associated with this wallet
        */
        RobotWallet(IEntity* entity);

        /**
         * @brief Destructor for the RobotWallet class
        */
        ~RobotWallet();

        /**
         * @brief "Withdraw" the associated amount from a bank, incrementing the
         * RobotWallet's associated money attribute.
         * 
         * @param amount The amount of money to be added to the RobotWallet
        */
        Withdraw(double amount);

        /**
         * @brief Attempt to pay the Drone driver the assoaciated amount for a ride.
         * 
         * @param amount The cost of the trip/the amount by which the RobotWallet's money will be reduced
         * @param drone_w The DroneWallet associated with the Drone driver
         * 
         * @return If the RobotWallet has sufficient funds to make the payment
        */
        bool Pay(double amount, DroneWallet* drone_w);
}

#endif