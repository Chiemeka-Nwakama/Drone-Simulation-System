#ifndef WALLET_DECORATOR_H_
#define WALLET_DECORATOR_H_

#include "IEntity.h"
#include "IStrategy.h"
#include "Bank.h" // IMPLEMENT THIS IN FACTORY

/**
 * @brief This class is the base abstract Wallet Decorator class that will hold 
 * an entity's money, used to either receive payments (Drone) or make payments
 * for rides (Robot).
*/
class WalletDecorator {
    protected:
        IStragegy* strategy;
        double money;
        IEntity* entity;
    
    public:
        /**
         * @brief Construct a new WalletDecorator object
         * 
         * @param strategy the strategy that the entity uses for movement
         * @param entity the entity associated with this Wallet
        */
        WalletDecorator(IStrategy* strategy, IEntity* entity);

        /**
         * @brief Move the associated Entity to the assocaited bank
         * 
         * @param dt Delta time
         * @param bank The bank to which the entity will move towards
        */
        ToBank(double dt, Bank* bank);

        /**
         * @brief Indicate whether or not the IEntity is at the assocaited bank
         * 
         * @param bank The bank that the IEntity may or may not be at
         * 
         * @return If the IEntity object is at the bank
        */
       bool AtBank(Bank* bank);

        /**
         * @brief Pure virtual WalletDecorator destructor. Made pure virtual in order
         * to prevent instantiation of bare WalletDecorator object. 
        */
        virtual ~WalletDecorator() = 0;
}

#endif