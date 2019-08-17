#ifndef MASSPOINT_H_
#define MASSPOINT_H_

#include "glm/glm.hpp"
#include <vector>
#include <algorithm>
#include <memory>

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
  @brief Gets the velocityaddSpringID of the MassPoint.
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
  @brief Calculates the internal forces of the MassPoint.
  */
  void calculateInternalForces();

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

  /**
  @brief Attaches a Spring to the MassPoint.
  @param[in] _id The id of the Spring.
  @param[in] _plane The plane of the Spring.
  @param[in] _springForce A pointer to the force of the spring.
  @param[in] _damping The damping value of the spring.
  */
  void addSpringInfo(unsigned int _id, char _type, char _plane,
                     std::shared_ptr<glm::vec3> _springForce,
                     float _damping);
  /**
  @brief Sets the damping of the attached springs.
  @param[in] _damping The new damping value.
  */
  void setDamping(float _damping);

private:
  ///A structure for the spring data
  struct SpringInfo
  {
    ///The id's of the attached springs.
    unsigned int m_id;
    ///The type of spring, either A or B based on where it attaches to the spring.
    char m_type;
    ///The plane of the spring, either V for vertical or H for horizontal.
    char m_plane;
    ///A pointer to the force of the spring.
    std::shared_ptr<glm::vec3> m_springForce;
    ///The damping value of the spring.
    float m_damping;
  };

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
  ///The colour of the MassPoint. This is mostly for testing.
  glm::vec3 m_colour;
  ///The information of the attached spring.
  std::vector<SpringInfo> m_springInfo;
};

#endif // MASSPOINT_H_
