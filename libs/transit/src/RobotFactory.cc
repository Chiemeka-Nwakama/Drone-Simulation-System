#include "RobotFactory.h"

IEntity* RobotFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("robot") == 0) {
    RobotWallet *rw = new RobotWallet(new Robot(entity))
    std::cout << "Robot Created with starting funds of $" << rw->GetMoney() << std::endl;
    return rw;
  }
  return nullptr;
}
