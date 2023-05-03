#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"

#include "DataCollection.h"

Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};
  speed = obj["speed"];
  available = true;
  wallet = new DroneWallet(this);
}

Drone::~Drone() {
  // Delete dynamically allocated variables
  delete graph;
  delete nearestEntity;
  delete toRobot;
  delete toFinalDestination;
  delete wallet;
}

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : scheduler) {
    if (entity->GetAvailability()) {
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }

  if (nearestEntity) {
      // set availability to the nearest entity
    nearestEntity->SetAvailability(false);
    available = false;
    pickedUp = false;

    destination = nearestEntity->GetPosition();
    Vector3 finalDestination = nearestEntity->GetDestination();

    toRobot = new BeelineStrategy(position, destination);
    
    holdPos = GetPosition(); //changed holdPos into getnearestentity

    std::string strat = nearestEntity->GetStrategyName();
    if (strat == "astar")
      toFinalDestination =
        new JumpDecorator(new AstarStrategy(destination, finalDestination, graph));
    else if (strat == "dfs")
      toFinalDestination =
        new SpinDecorator(new JumpDecorator(new DfsStrategy(destination, finalDestination, graph)));
    else if (strat == "dijkstra")
      toFinalDestination =
        new JumpDecorator(new SpinDecorator(new DijkstraStrategy(destination, finalDestination, graph)));
    else
      toFinalDestination = new BeelineStrategy(destination, finalDestination);
  }
}

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
  if (available)
    GetNearestEntity(scheduler);
    

  if (toRobot) {
    toRobot->Move(this, dt);

    if (toRobot->IsCompleted()) {
      delete toRobot;
      toRobot = nullptr;
      pickedUp = true;
      
      //singleton data additions
      DataCollection* dc = DataCollection::getInstance();
      dc->writeDeliveryDist(this, (holdPos.Distance(GetPosition())));
      holdPos = GetPosition(); //holding the position of picking the drone up to record trip distance
      //std::cout << "holdPos after pickup: " << holdPos.Magnitude() << std::endl;
    }
  } else if (toFinalDestination) {
    toFinalDestination->Move(this, dt);

    if (nearestEntity && pickedUp) {
      nearestEntity->SetPosition(position);
      nearestEntity->SetDirection(direction);
    }

    if (toFinalDestination->IsCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;

      //csv testing
      DataCollection* dc = DataCollection::getInstance();
      float moneyTest = (holdPos.Distance(GetPosition())) * 0.01;
      dc->writeRobotMoneyGiven(nearestEntity, moneyTest);

      nearestEntity = nullptr;
      available = true;
      pickedUp = false;

      //singleton stuff
      //std::cout << "holdPos before finish write: " << holdPos.Magnitude() << std::endl;
      //std::cout << "getPosition() before finish write: " << GetPosition().Magnitude() << std::endl;
      //DataCollection* dc = DataCollection::getInstance();
      dc->writeDeliveryDist(this, (holdPos.Distance(GetPosition()))); //total distance drone has travelled, what is unit (m, km, etc.)?
      dc->writeNumDelTrip(this); //total amount of robot delivery trips completed
      dc->calcDelDistPerTrip(this); //calculating delivery distance per trip
      dc->writeToCSV(); //placeholder for testing. a button will be made later

    }
  }
}

void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if (goUp) {
    position.y += height;
    jumpHeight += height;
    if (jumpHeight > 5) {
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if (jumpHeight < 0) {
      goUp = true;
    }
  }
}
