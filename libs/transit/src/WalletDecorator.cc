#include "WalletDecorator.h"

#include "DataCollection.h"

WalletDecorator::WalletDecorator(IEntity* entity) { this->entity = entity; }

WalletDecorator::~WalletDecorator() { delete toBank; }

Vector3 WalletDecorator::GetNearestBank() {
  float minDis = std::numeric_limits<float>::max();
  IEntity* nearestEntity = nullptr;
  for (auto entity : entities) {
    // determine if the entity is a Bank
    JsonObject detailsTemp = entity->GetDetails();
    std::string typeTemp = detailsTemp["type"];
    std::string nameTemp = detailsTemp["name"];
    if (typeTemp.compare("bank") == 0) {
      float disToEntity = this->GetPosition().Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        std::cout << nameTemp << std::endl;
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }
  if (nearestEntity) {
    std::cout << "Found bank" << std::endl;

    DataCollection* dc = DataCollection::getInstance();
    dc->writeBankVisit(nearestEntity);

    return nearestEntity->GetPosition();
  }
  // if no banks are on the map
  return Vector3(0, 0, 0);
}
