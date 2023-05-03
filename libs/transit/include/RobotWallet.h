#ifndef ROBOT_WALLET_H_
#define ROBOT_WALLET_H_

#include "WalletDecorator.h"
#include "Robot.h"

// Robot-specific function, implemented inherited, point to just robot

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
         * @param entity_ the entity associated with this wallet
        */
        RobotWallet(Robot* entity_);

        /**
         * @brief Destructor for the RobotWallet class
        */
        ~RobotWallet();

        /**
         * @brief Virtual method for adding money to wallet
         * 
         * @param amount how much money to add to wallet 
        */
        void Add(int amount) { money += amount; }

        /**
         * @brief Virtual method for removing money from wallet -
         * paying or depositing
         * 
         * @param amount how much money to remove from wallet
        */
        void Remove(int amount) { money -= amount; }

        /**
         * @brief Updates the robot if it needs to go to a bank
         * 
         *@param dt Delta time
        * @param scheduler Vector containing all the entities in the system
        * @param cost Cost of trip
        */
        void Update(double dt, std::vector<IEntity*> scheduler, int cost);

        /**
         * @brief How much money the entity can carry
         * 
         * @return The maximum capacity of the wallet
        */
        int GetCapacity() { return capacity; }

        /**
         * @brief method for returning the amount of money in the wallet
         * 
         * @return Amount of money in wallet 
        */
        int GetMoney() { return money; }

        /**
         * @brief Gets the robot's position
         * @return The robot's position
         */
        Vector3 GetPosition() const { return entity->GetPosition(); }

        /**
         * @brief Gets the robot's direction
         * @return The robot's direction
         */
        Vector3 GetDirection() const { return entity->GetDirection(); }

        /**
         * @brief Gets the robot's destination
         * @return The robot's destination
         */
        Vector3 GetDestination() const { return entity->GetDestination(); }

        /**
         * @brief Gets the robot's availability
         * @return The robot's availability
         */
        bool GetAvailability() const { return entity->GetAvailability(); }

        /**
         * @brief Gets the robot's details
         * @return The robot's details
         */
        JsonObject GetDetails() { return entity->GetDetails(); }

        /**
         * @brief Gets the robot's speed
         * @return The robot's speed
         */
        float GetSpeed() const { return entity->GetSpeed(); }

        /**
         * @brief Get the Strategy Name
         *
         * @return Streategy name
         */
        std::string GetStrategyName() const { return entity->GetStrategyName(); }

        /**
         * @brief Gets the robot's details
         * @return The robot's details
         */
        JsonObject GetDetails() const { return entity->GetDetails(); };

        /**
         * @brief Set the Strategy Name
         *
         * @param strategyName_ Strategy name
         */
        void SetStrategyName(std::string strategyName_) { entity->SetStrategyName(strategyName_); }

        /**
         * @brief Sets the robot's availability
         * @param choice The new availability of the robot
         */
        void SetAvailability(bool choice) { entity->SetAvailability(choice); }

        /**
         * @brief Sets the robot's position
         * @param pos_ The new position of the robot
         */
        void SetPosition(Vector3 pos_) { entity->SetPosition(pos_); }

        /**
         * @brief Sets the robot's direction
         * @param dir_ The new direction of the robot
         */
        void SetDirection(Vector3 dir_) { entity->SetDirection(dir_); }

        /**
         * @brief Sets the robot's destination
         * @param des_ The new destination of the robot
         */
        void SetDestination(Vector3 des_) { entity->SetDestination(des_); }

        /**
         * @brief Sets the robot's graph and the wallet's graph
         * @param graph The IGraph object to be used.
        */
       void SetGraph(const IGraph* graph) { this->graph = graph; entity.SetGraph(graph);}

        /**
         * @brief Rotates the robot
         * @param angle The angle by which the robot should be rotated
         */
        void Rotate(double angle) { entity->Rotate(angle); }

        /**
         * @brief Updates the entity's position in the physical system.
         * @param dt The time step of the update.
         * @param scheduler The list of all entities in the system.
         */
        void Update(double dt, std::vector<IEntity*> scheduler) { entity->Update(dt, scheduler); }

    private:
        int money;
        int capacity;
        Robot* entity;
};

#endif
