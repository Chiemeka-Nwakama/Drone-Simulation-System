#include "SimulationModel.h"

#include "DroneFactory.h"
#include "RobotFactory.h"
#include "HumanFactory.h"
#include "HelicopterFactory.h"
#include "BankFactory.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new HumanFactory());
  AddFactory(new HelicopterFactory());
  AddFactory(new BankFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (int i = 0; i < entities.size(); i++) {
    delete entities[i];
  }
  for (int i = 0; i < scheduler.size(); i++) {
    delete scheduler[i];
  }
  delete graph;
  delete compFactory;
}

void SimulationModel::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  myNewEntity->SetGraph(graph);

  // Call AddEntity to add it to the view
  controller.AddEntity(*myNewEntity);
  entities.push_back(myNewEntity);
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    // make vector of all names including banks
    std::vector<std::string> bankNames;
    bankNames.push_back("bank1"); 
    bankNames.push_back("bank2");
    bankNames.push_back("bank3");
    bankNames.push_back("back4");
    bool validName = (nameTemp.compare(name) == 0);
    // if first call, check bank names as well
    if (this->start){
      for (int i = 0; i < bankNames.size(); i++){
        if (validName) break;
        validName = nameTemp.compare(bankNames.at(i));
      }
    }
    std::string typeTemp = detailsTemp["type"];
    // robot no longer needs to be available to be added to the scheduler
    if (validName && (typeTemp.compare("robot") == 0 || typeTemp.compare("bank") == 0)) {
      std::cout << typeTemp << std::endl;
      std::string strategyName = details["search"];
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      entity->SetStrategyName(strategyName);
      scheduler.push_back(entity);
      if (!this->start){ // if this is the first call, make sure that the banks are added
        break;
      }
    }
  }
  controller.SendEventToView("TripScheduled", details);
  std::cout << "Okay to here" << std::endl;
  // if this was the first call, set start to false
  if (this->start) {
    this->start = false;
  }
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    entities[i]->Update(dt, scheduler);
    controller.UpdateEntity(*entities[i]);
  }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
