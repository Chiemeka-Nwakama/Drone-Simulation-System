#ifndef DATA_COLLECTION_H_
#define DATA_COLLECTION_H_

#include "IEntity.h"
#include "Drone.h"
#include "Robot.h"
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
    std::map<Drone, double> totalDistTrav;
    std::map<Drone, int> totalMoney;
    std::map<Drone, int> totalDelTrips;
    std::map<Drone, int> totalBankTrips;
    std::map<Drone, int> moneyDeposited;
    std::map<Drone, double> totalDistToBank;
    std::map<Bank, int> numVisits;
    std::map<Robot, int> tripCost;

    protected:

    //DataCollection instance; changed
    //shouldn't be publicly accessable
    static DataCollection* instance;
    
    public:

    //added to the protected sector, prevents users from calling it directly
    /**
    * @brief Construct a new single* Data Collection object
    * 
    * 
    */
    DataCollection();

    //DataCollection* instance = nullptr;

    //singletons should not be copyable
    DataCollection(DataCollection &other) = delete;

    //singletons should not be assignable
    void operator=(const DataCollection &) = delete;

    /**
     * @brief DataCollection Deconstructor
     *  
    */
    ~DataCollection();

    //changed
    static DataCollection* getInstance(){
        if(instance == nullptr){
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
