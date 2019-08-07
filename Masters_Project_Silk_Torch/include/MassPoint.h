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
  @brief Sets the velocity of the MassPoint.
  @param[in] _vel The new velocity.
  */
  void setVel(glm::vec3 _vel);

  /**
  @brief Gets the velocity of the MassPoint.
  @returns The velocity of the MassPoint.
  */
  glm::vec3 getVel();

  /**
  @brief Updates the velocity of the MassPoint.
  @param[in] _vel The velocity to update the current velocity with.
  */
  void updateVel(glm::vec3 _vel);

  /**
  @brief Sets the internal forces of the MassPoint.
  @param[in] _vel The new internal forces.
  */
  void setInternalForces(glm::vec3 _internalForces);

  /**
  @brief Gets the internal forces of the MassPoint.
  @returns The internal forces of the MassPoint.
  */
  glm::vec3 getInternalForces();

  /**
  @brief Updates the internal forces of the MassPoint.
  @param[in] _vel The internal forces to update the current internal forces with.
  */
  void updateInternalForces(glm::vec3 _internalForces);

  /**
  @brief Sets the external forces of the MassPoint.
  @param[in] _vel The new external forces.
  */
  void setExternalForces(glm::vec3 _externalForces);

  /**
  @brief Gets the external forces of the MassPoint.
  @returns The external forces of the MassPoint.
  */
  glm::vec3 getExternalForces();

  /**
  @brief Updates the external forces of the MassPoint.
  @param[in] _vel The external forces to update the current external forces with.
  */
  void updateExternalForces(glm::vec3 _externalForces);

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

  /**
  @brief Sets the colour of the MassPoint.
  @param[in] _colour The new colour.
  */
  void setColour(glm::vec3 _colour);

  /**
  @brief Gets the colour of the MassPoint.
  @returns The colour of the MassPoint.
  */
  glm::vec3 getColour();


private:
  ///The mass of the MassPoint.
  float m_mass;
  ///The position of the MassPoint.
  glm::vec3 m_pos;
  ///The velocity of the MassPoint.
  glm::vec3 m_vel;
  ///The internal forces on the MassPoint.
  glm::vec3 m_internalForces;
  ///The external forces on the MassPoint.
  glm::vec3 m_externalForces;
  ///A boolean for if the MassPoint is locked in place.
  bool m_isLocked;
  ///The colour of the MassPoint. This is mostly for testing
  glm::vec3 m_colour;
};

#endif // MASSPOINT_H_
