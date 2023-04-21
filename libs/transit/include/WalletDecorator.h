#ifndef WALLET_DECORATOR_H_
#define WALLET_DECORATOR_H_

#include "IEntity.h"

/**
 * @brief This class is the base abstract Wallet Decorator class that will hold 
 * an entity's money, used to either receive payments (Drone) or make payments
 * for rides (Robot).
*/
class WalletDecorator {
    protected:
        int money;
        IEntity* entity;
    
    public:
        /**
         * @brief Construct a new WalletDecorator object
         * 
         * @param entity the entity associated with this Wallet
        */
        WalletDecorator(IEntity* entity);

        /**
         * @brief Pure virtual WalletDecorator destructor. Made pure virtual in order
         * to prevent instantiation of bare WalletDecorator object. 
        */
        // virtual ~WalletDecorator() = 0;
};

#endif
