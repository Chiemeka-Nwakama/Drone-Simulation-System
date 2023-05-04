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
 * This class collects data regarding the drone, tips, banks, and other simulation entities
 * 
*/
class DataCollection {
    private:

    //map variables added below
    //is money int or double?
    static DataCollection* instance;
    static std::ofstream myfile; //the csv file for the data collection class


    protected:

    //DataCollection instance; changed
    //shouldn't be publicly accessable
    
    
    public:

    // std::map<Drone, double> totalDistTrav;
    // std::map<Drone, int> totalMoney;
    // std::map<Drone, int> totalDelTrips;
    // std::map<Drone, int> totalBankTrips;
    // std::map<Drone, int> moneyDeposited;
    // std::map<Drone, double> totalDistToBank;
    // std::map<Bank, int> numVisits;
    // std::map<Robot, int> tripCost;

    //added to the protected sector, prevents users from calling it directly
    /**
    * @brief Construct a new single* Data Collection object
    * 
    * 
    */
    DataCollection(){
      
        
    }

    //DataCollection* instance = nullptr;

    //singletons should not be copyable
    DataCollection(DataCollection &other) = delete;

    //singletons should not be assignable
    void operator=(const DataCollection &data) = delete;

    /**
     * @brief DataCollection Deconstructor
     *  
    */
    ~DataCollection();

    

    //changed
    static DataCollection* getInstance(){
        if (instance == nullptr){
           //creates a data csv file
            //std::cout << "no instance yet, making one now" << std::endl;
            instance = new DataCollection();
        }
        //std::cout << "instance made, returning details" << std::endl;
        return instance;
    }

    //function placeholders, will add doxygen later
    //writing functions
    //is money int or double?
    void writeDeliveryDist(IEntity* dr, float dist);
  
    void writeDroneTotalMoney(IEntity* dr, int money);
    void writeRobotMoneyGiven(IEntity* rb, float money);
    void writeNumDelTrip(IEntity* dr);
    void writeNumBankTrip(IEntity* dr);
    void writeMoneyDeposited(IEntity* dr, int money);
    void writeBankVisit(IEntity* bk);
    // void writeTripCose(Robot, int);

    //analysis functions
    //is money int or double?
    double calcDelDistPerTrip(IEntity* dr);
    int calcMoneyPerTrip();
    int calcPopularBank();
    int calcMoneyPerDeposit();

    //CSV function
    void writeToCSV();

    // bool operator<(const Drone& other1, const Drone& other2){
    //     return true;
    // }
  
};

#endif
