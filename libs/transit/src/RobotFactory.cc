#include "RobotFactory.h"

IEntity* RobotFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("robot") == 0) {
    std::cout << "Robot Created right here whoohoo" << std::endl;
    Robot *test = new Robot(entity);
    std::cout << "testing for segfault here?" << std::endl;
    return new RobotWallet(new Robot(entity));
  }
  return nullptr;
}
