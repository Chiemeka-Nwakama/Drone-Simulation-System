#ifndef DATA_COLLECTION_H_
#define DATA_COLLECTION_H_

#include "IEntity.h"
#include <iostream>
#include <fstream>
#include "DataCollection.h"

#include "Robot.h"
#include "Drone.h"
#include "Bank.h"


/**
 * @brief This class is the singleton Data Collection class
 * This class collects and analyzes data regarding the drone, tips, banks, and other simulation entities.
 * 
*/
class DataCollection {
    private:

    static DataCollection* instance;
    static std::ofstream myfile; //the csv file for the data collection class
    
    public:
    /**
    * @brief Construct a new single* Data Collection object
    * 
    */
    DataCollection(){
      
        
    }

    /**
    * @brief Deletes the copy constuctor for the singleton object, ensuring there is only one
    * 
    */
    DataCollection(DataCollection &other) = delete;

    /**
    * @brief Deletes the assignment constuctor for the singleton object, ensuring there is only one
    * 
    */
    void operator=(const DataCollection &data) = delete;

    /**
     * @brief DataCollection Deconstructor
     *  
    */
    ~DataCollection();

    /**
     * @brief Everytime data collection needs to occur, the instance needs to be referenced in order to use writing and analysis functions.
     * @return An instance of the data collection object.
    */
    static DataCollection* getInstance(){
        if (instance == nullptr){
            instance = new DataCollection();
        }
        return instance;
    }

    //writing functions
    /**
     * @brief Records the distance of the drone
    */
    void writeDeliveryDist(IEntity* dr, float dist);

    /**
     * @brief Records the money of the drone
    */
    void writeDroneTotalMoney(IEntity* dr, int money);

    /**
     * @brief Records the trip cost of each robot
    */
    void writeRobotMoneyGiven(IEntity* rb, float money);

    /**
     * @brief Records the number of delivery trips of the drone
    */
    void writeNumDelTrip(IEntity* dr);

    /**
     * @brief Records the number of bank trips of the drone
    */
    void writeNumBankTrip(IEntity* dr);

    /**
     * @brief Records the money deposited into the bank of the drone
    */
    void writeMoneyDeposited(IEntity* dr, int money);

    /**
     * @brief Records the number of visits in each bank
    */
    void writeBankVisit(IEntity* bk);

    //analysis functions
    /**
     * @brief Calculates the distance per trips of the drone
     * @return The distance per trip value
    */
    double calcDelDistPerTrip(IEntity* dr);

    /**
     * @brief Calculates the money per trips of the drone
     * @return The money per trip value
    */
    int calcMoneyPerTrip();

    /**
     * @brief Calculates the most popular bank
     * @return The integer value of the bank (Bank 1, 2, 3, or 4)
    */
    int calcPopularBank();

    /**
     * @brief Calculates the money per deposit of the drone
     * @return The money per deposit value
    */
    int calcMoneyPerDeposit();

    /**
     * @brief Publishes all of the taken data and calculations onto the csv
    */
    void writeToCSV();
  
};

#endif
