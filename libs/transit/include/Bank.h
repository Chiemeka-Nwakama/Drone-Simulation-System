#ifndef Bank_H_
#define Bank_H_

#include "IEntity.h"

class Bank : public IEntity {
 public:
  /**
   * @brief Bank are created with a name
   * @param obj JSON object containing the bank's information
   */
  Bank(JsonObject& obj);

  /**
   * @brief Destroy the Bank object
   */
  ~Bank();

  /**
   * @brief Not needed for bank. Default implementation
   *
   */
  float GetSpeed() const { return 0; }

  /**
   * @brief Gets the position of the Bank
   * @return The position of the Bank
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Not needed for bank. Default implementation
   *
   */
  Vector3 GetDirection() const { return Vector3(); }

  /**
   * @brief Not needed for bank. Default implementation
   *
   */
  Vector3 GetDestination() const { return Vector3(); }

  /**
   * @brief Gets the details information of the drone
   * @return The details information of the drone
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

 private:
  JsonObject details;
  Vector3 position;
};
#endif
