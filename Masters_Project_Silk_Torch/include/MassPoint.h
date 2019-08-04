#ifndef MASSPOINT_H_
#define MASSPOINT_H_

#include "glm/glm.hpp"

/// @file MassPoint.h
/// @brief A Class that contains all the functions and members for the point of mass.
/// @author Jamie Slowgrove
/// @version 1.0
/// @date 03/08/19
/// Revision History:
/// Initial Version 03/08/19.
class MassPoint
{
public:
  /**
  @brief Constructs the MassPoint. Default mass is 10.0f, default position is (0.0f,0.0f,0.0f) and default locked state is false.
  */
  MassPoint();

  /**
  @brief Constructs the MassPoint. Default locked state is false.
  @param[in] _mass The mass of the MassPoint.
  @param[in] _pos The position of the MassPoint.
  */
  MassPoint(float _mass, glm::vec3 _pos);

  /**
  @brief Constructs the MassPoint.
  @param[in] _mass The mass of the MassPoint.
  @param[in] _pos The position of the MassPoint.
  @param[in] _isLocked The locked state of the MassPoint.
  */
  MassPoint(float _mass, glm::vec3 _pos, bool _isLocked);

  /**
  @brief Destructs the MassPoint.
  */
  ~MassPoint();

  /**
  @brief Updates the MassPoint.
  @param[in] _dt The delta time.
  */
  void update(float _dt);

  /**
  @brief Sets the mass of the MassPoint.
  @param[in] _mass The new mass.
  */
  void setMass(float _mass);

  /**
  @brief Gets the mass of the MassPoint.
  @returns The mass of the MassPoint.
  */
  float getMass();

  /**
  @brief Sets the position of the MassPoint.
  @param[in] _pos The new position.
  */
  void setPos(glm::vec3 _pos);

  /**
  @brief Gets the position of the MassPoint.
  @returns The position of the MassPoint.
  */
  glm::vec3 getPos();

  /**
  @brief Sets the locked state of the MassPoint to true.
  */
  void lock();

  /**
  @brief Sets the locked state of the MassPoint to false.
  */
  void unlock();

  /**
  @brief Gets the locked state of the MassPoint.
  @returns The locked state of the MassPoint.
  */
  bool getIsLocked();


private:
  ///The mass of the MassPoint.
  float m_mass;
  ///The position of the MassPoint.
  glm::vec3 m_pos;
  ///A boolean for if the MassPoint is locked in place.
  bool m_isLocked;
};

#endif // MASSPOINT_H_
