#ifndef DRONE_WALLET_H_
#define DRONE_WALLET_H_

#include "WalletDecorator.h"
#include "Drone.h"

// Drone-specific function, implemented inherited, point to just drone, update
// logic

/**
 * @brief This class inherits from the WalletDecorator class and constitutes
 * the wallets that will be used by the Drones (Drone simulation drivers).
 * Drone wallets can deposit money into banks or receive payments.
 */
class DroneWallet : public WalletDecorator {
 public:
  /**
   * @brief Construct a new DroneWallet object
   *
   * @param entity_ the entity associated with this wallet
   */
  DroneWallet(Drone* entity_);

  /**
   * @brief Destructor for the DroneWallet class
   */
  ~DroneWallet();

  /**
   * @brief Virtual method for adding money to wallet
   *
   * @param amount how much money to add to wallet
   */
  void Add(int amount) { money += amount; }

  /**
   * @brief Virtual method for removing money from wallet -
   * paying or depositing
   *
   * @param amount how much money to remove from wallet
   */
  void Remove(int amount) { money -= amount; }

  /**
   * @brief How much money the entity can carry
   *
   * @return The maximum capacity of the wallet
   */
  int GetCapacity() { return capacity; }

  /**
   * @brief method for returning the amount of money in the wallet
   *
   * @return Amount of money in wallet
   */
  int GetMoney() { return money; }

  /**
   * @brief Gets the speed of the drone
   * @return The speed of the drone
   */
  float GetSpeed() const { return entity->GetSpeed(); }

  /**
   * @brief Gets the position of the drone
   * @return The position of the drone
   */
  Vector3 GetPosition() const { return entity->GetPosition(); }

  /**
   * @brief Gets the direction of the drone
   * @return The direction of the drone
   */
  Vector3 GetDirection() const { return entity->GetDirection(); }

  /**
   * @brief Gets the destination of the drone
   * @return The destination of the drone
   */
  Vector3 GetDestination() const { return entity->GetDestination(); }

  /**
   * @brief Gets the color of the drone
   * @return The color of the drone
   */
  std::string GetColor() const { return entity->GetColor(); }

  /**
   * @brief Gets the details information of the drone
   * @return The details information of the drone
   */
  JsonObject GetDetails() const { return entity->GetDetails(); }

  /**
   * @brief Gets the availability of the drone
   * @return The availability of the drone
   */
  bool GetAvailability() const { return entity->GetAvailability(); }

  /**
   * @brief Gets the nearest entity in the scheduler
   * @param scheduler Vector containing all the entities in the system
   */
  void GetNearestEntity(std::vector<IEntity*> scheduler) { entity->GetNearestEntity(scheduler); }

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the position of the drone
   * @param pos_ The new position of the drone
   */
  void SetPosition(Vector3 pos_) { entity->SetPosition(pos_); }

  /**
   * @brief Sets the direction of the drone
   * @param dir_ The new direction of the drone
   */
  void SetDirection(Vector3 dir_) { entity->SetDirection(dir_); }

  /**
   * @brief Sets the destination of the drone
   * @param des_ The new destination of the drone
   */
  void SetDestination(Vector3 des_) { entity->SetDestination(des_); }

  /**
   * @brief Sets the color of the drone
   * @param col_ The new color of the drone
   */
  void SetColor(std::string col_) { entity->SetColor(col_); }

  /**
   * @brief Sets the robot's graph and the wallet's graph
   * @param graph The IGraph object to be used.
  */
  void SetGraph(const IGraph* graph) { this->graph = graph; entity.SetGraph(graph)}

  /**
   * @brief Rotates the drone
   * @param angle The angle by which the drone should be rotated
   */
  void Rotate(double angle) { entity->Rotate(angle); }

  /**
   * @brief Makes the drone jump
   * @param height The height at which the drone should jump
   */
  void Jump(double height) { entity->Jump(height); }

 private:
  int money;
  int capacity;
  Drone* entity;
};

#endif
