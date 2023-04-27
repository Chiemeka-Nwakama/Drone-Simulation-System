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
        int capacity;
        IEntity* entity;
    
    public:
        /**
         * @brief Construct a new WalletDecorator object
         * 
         * @param entity the entity associated with this Wallet
        */
        WalletDecorator(IEntity* entity);

        /**
         * @brief Virtual method for returning the amount of money in the wallet
         * 
         * @return Amount of money in wallet 
        */
        virtual int GetMoney() { return money; }

        /**
         * @brief Virtual method for withdrawing from the bank
         * 
         * @param amount how much money to add to wallet 
        */
        virtual void Withdraw(int amount) {}

        /**
         * @brief Virtual method for depositing to bank
         * 
         * @param amount how much money to remove from wallet
        */
        virtual void Deposit(int amount) {}

        /**
         * @brief Virtual method for recieving money from other entities
         * 
         * @param amount how of money to add to wallet
        */
        virtual void ReceivePayment(int amount) {}

        /**
         * @brief Virtual method for recieving money from other entities
         * 
         * @param amount how of money to pay other entity
        */
        virtual void Pay(int amount) {}

        /**
         * @brief How much money the entity can carry
         * 
         * @return The maximum capacity of the wallet
        */
        virtual int GetCapacity();

        /**
         * @brief Pure virtual WalletDecorator destructor. Made pure virtual in order
         * to prevent instantiation of bare WalletDecorator object. 
        */
        // virtual ~WalletDecorator() = 0;
};

#endif
