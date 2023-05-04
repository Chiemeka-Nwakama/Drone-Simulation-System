#ifndef WALLET_DECORATOR_H_
#define WALLET_DECORATOR_H_

#include <vector>
#include "math/vector3.h"
#include "IEntity.h"
#include "IStrategy.h"

/**
 * @brief This class is the base abstract Wallet Decorator class that will hold 
 * an entity's money, used to either receive payments (Drone) or make payments
 * for rides (Robot).
*/
class WalletDecorator : public IEntity {
    protected:
        int money;
        int capacity;
        IEntity* entity;
        IStrategy* toBank = nullptr;
    
    public:
        /**
         * @brief Construct a new WalletDecorator object
         * 
         * @param entity the entity associated with this Wallet
        */
        WalletDecorator(IEntity* entity_);

        /**
         * @brief Virtual method for returning the amount of money in the wallet
         * 
         * @return Amount of money in wallet 
        */
        int GetMoney() { return money; }

        /**
         * @brief Virtual method for adding money to wallet
         * 
         * @param amount how much money to add to wallet 
        */
        virtual void Add(int amount) {}

        /**
         * @brief Virtual method for removing money from wallet -
         * paying or depositing
         * 
         * @param amount how much money to remove from wallet
        */
        virtual void Remove(int amount) {}

        /**
         * @brief How much money the entity can carry
         * 
         * @return The maximum capacity of the wallet
        */
        int GetCapacity() { return capacity; }

        /**
         * @brief Pure virtual WalletDecorator destructor. Made pure virtual in order
         * to prevent instantiation of bare WalletDecorator object. 
        */
        virtual ~WalletDecorator() = 0;

        /**
         * @brief Determines the position of the nearest bank in the simulation.
         * 
         * @return The position of the nearest bank.
        */
        Vector3 GetNearestBank(std::vector<IEntity*> scheduler);
};

#endif
