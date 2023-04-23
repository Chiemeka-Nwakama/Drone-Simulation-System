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
           return instance;
         }
  
};

#endif
