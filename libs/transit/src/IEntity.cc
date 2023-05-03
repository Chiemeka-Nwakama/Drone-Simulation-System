
#include <vector>

#include "graph.h"
#include "math/vector3.h"
#include "util/json.h"
#include "IEntity.h"
using namespace routing;

std::vector<Vector3> IEntity::bankPositions{};

Vector3 IEntity::GetNearestBank() {
    int indexOfClosestBank = 0; // contain index of closest bank
    Vector3 entitysPos = this->GetPosition(); //gets this entity's position
    float distanceOfClosestBank = bankPositions.at(0).Distance(entitysPos);
    
    for(int i = 1; i < bankPositions.size(); i++) {
      float currDistance = bankPositions.at(i).Distance(entitysPos);
      // compares the next banks distance with the current banks
      if(currDistance < distanceOfClosestBank) {
        distanceOfClosestBank = currDistance;
        indexOfClosestBank = i;
      }
    }
    // returns the coordinates/position of the nearest bank to this entity
    return bankPositions.at(indexOfClosestBank);
  }