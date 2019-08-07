#ifndef SPRING_H_
#define SPRING_H_

#include <memory>
#include <vector>

#include "MassPoint.h"

/// @file Spring.h
/// @brief An Abstract Class that contains all general functions and members that are related to spring objects.
/// @author Jamie Slowgrove
/// @version 2.0
/// @date 24/01/19
/// Revision History:
/// Initial Version 24/01/19.
/// New Verison 03/08/19 for the Master's project.
class Spring
{
public:
  /**
  @brief Constructs the Spring object using the default spring constant (10.0f) and the default damping value (20.0f).
  */
  Spring();

  /**
  @brief Constructs the Spring object using the default damping value (20.0f).
  @param[in] _springConstant The constant for the object
  */
  Spring(float _springConstant);

  /**
  @brief Constructs the Spring object.
  @param[in] _springConstant The Spring constant of the Spring.
  @param[in] _restLength The damping value of the Spring.
  */
  Spring(float _springConstant, float _damping);

  /**
  @brief A destructor for the Spring object.
  */
  virtual ~Spring();

  /**
  @brief Gets the Spring constant of the Spring.
  @returns The Spring constant of the Spring.
  */
  float getSpringConstant();

  /**
  @brief Sets the Spring constant of the Spring.
  @param[in] _springConstant The Spring constant of the Spring.
  */
  void setSpringConstant(float _springConstant);

  /**
  @brief Gets the damping value of the Spring.
  @returns The damping value of the Spring.
  */
  float getDamping();

  /**
  @brief Sets the damping value of the Spring.
  @param[in] _damping The damping value of the Spring.
  */
  void setDamping(float _damping);

  /**
  @brief Gets the position of the point that point A is attached.
  @returns The position of the point that point A is attached.
  */
  glm::vec3 getPointAAttachedPos();

  /**
  @brief Sets the position of the point that point A is attached.
  @param[in] _pointAAttachedPos The position of the point that point A is attached.
  */
  void setPointAAttachedPos(glm::vec3 _pointAAttachedPos);

  /**
  @brief Gets the point A from the spring.
  @returns A shared pointer for the point A of the spring.
  */
  std::shared_ptr<MassPoint> getPointA();

  /**
  @brief Sets the point A for the spring.
  @param _particleA A shared pointer for the Point A of the spring.
  */
  void setPointA(std::shared_ptr<MassPoint> _pointA);

  /**
  @brief Gets the point B from the spring.
  @returns A shared pointer for the point B of the spring.
  */
  std::shared_ptr<MassPoint> getPointB();

  /**
  @brief Sets the point B for the spring.
  @param _particleB A shared pointer for the Point B of the spring.
  */
  void setPointB(std::shared_ptr<MassPoint> _pointB);

  /**
  @brief Update the Spring.
  */
  void update();

protected:
  ///The spring constant.
  float m_springConstant;
  ///The damping value of the spring.
  float m_damping;
  ///The position of the point that point A is attached.
  glm::vec3 m_pointAAttachedPos;
  ///The point A that is attached to the Spring.
  std::shared_ptr<MassPoint> m_pointA;
  ///The point B that is attached to the Spring.
  std::shared_ptr<MassPoint> m_pointB;
};

#endif // SPRING_H_

/*
update function (springforce -> dampingforce -> masspoint update)*/
