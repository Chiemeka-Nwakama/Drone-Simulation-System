#ifndef DATA_COLLECTION_H_
#define DATA_COLLECTION_H_

#include "IEntity.h"

/**
 * @brief This class is the singleton Data Collection class
 * This class collects data regarding the drone, tips, banks, and other simulation entities
 * 
*/
class DataCollection {
    private:
    DataCollection instance;
    //map variables added below
    //is money int or double?
    map<Drone, double> totalDistTrav;
    map<Drone, int> totalMoney;
    map<Drone, int> totalDelTrips;
    map<Drone, int> totalBankTrips;
    map<Drone, int> moneyDeposited;
    map<Drone, double> totalDistToBank;
    map<Bank, int> numVisits;
    map<Robot, int> tripCost;
    
    public:
        /**
         * @brief Construct a new single* Data Collection object
         * 
         * 
        */
        DataCollection();

        /**
         * @brief DataCollection Deconstructor
         *  
        */
         ~DataCollection();
         DataCollection getInstance(){
            if(instance == null){
                instance = new DataCollection();
            }
           return instance;
         }

        //function placeholders, will add doxygen later
        //writing functions
        //is money int or double?
        void writeDeliveryDist(Drone, double);
        void writeDroneMoney(Drone, int);
        void writeNumDelTrip(Drone);
        void writeNumBankTrip(Drone);
        void writeMoneyDeposited(Drone, int);
        void writeBankVisit(Bank);
        void writeTripCose(Robot, int);
        void writeDistToBank(Drone, double);

        //analysis functions
        //is money int or double?
        double calcDistPerTrip();
        int calcMoneyPerTrip();
        int calcPopularBank();
        double calcMoneyPerDeposit();
        double calcDistToBank();

        //CSV function
        void writeToCSV();
  
};

#endif
