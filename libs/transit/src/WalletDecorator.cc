#include "WalletDecorator.h"

WalletDecorator::WalletDecorator(IEntity* entity) {
    this->entity = entity;
}

WalletDecorator::~WalletDecorator() { delete toBank; }

Vector3 WalletDecorator::GetNearestBank(std::vector<IEntity*> scheduler) {
    std::cout << "In function" << std::endl;
  float minDis = std::numeric_limits<float>::max();
  IEntity* nearestEntity = nullptr;
  for (auto entity : scheduler) {
    // determine if the entity is a Bank
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    if (nameTemp.compare("bank") == 0) {
      float disToEntity = this->GetPosition().Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }
  if (nearestEntity){
    std::cout << "Found bank" << std::endl;
    return nearestEntity->GetPosition();
  }
  // if no banks are on the map
  return Vector3(0,0,0);
}