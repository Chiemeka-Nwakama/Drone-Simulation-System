#define _USE_MATH_DEFINES
#include "Bank.h"

#include <cmath>
#include <limits>

Bank::Bank(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  bankPositions.push_back(position); //pushes banks position to the vector in ientity that holds bank positions
}

Bank::~Bank() {}

void Bank::Update(double dt, std::vector<IEntity*> scheduler) {}
