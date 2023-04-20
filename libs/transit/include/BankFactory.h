#ifndef Bank_FACTORY_H_
#define Bank_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "Bank.h"

/**
 *@brief Bank Factory to produce Bank class.
 **/
class BankFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for HelicopterFactory class.
   **/
  virtual ~BankFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
