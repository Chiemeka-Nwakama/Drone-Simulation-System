#include "BankFactory.h"

IEntity* BankFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("bank") == 0) {
    std::cout << "Bank Created" << std::endl;
    return new Bank(entity);
  }
  return nullptr;
}
