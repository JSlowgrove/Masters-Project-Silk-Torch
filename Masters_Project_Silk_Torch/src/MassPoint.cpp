#include "MassPoint.h"
#include "Logging.h"

MassPoint::MassPoint() : m_mass(10.0f), m_pos(glm::vec3(0.0f,0.0f,0.0f)), m_vel(glm::vec3(0.0f,0.0f,0.0f)),
  m_internalForces(glm::vec3(0.0f,0.0f,0.0f)), m_externalForces(glm::vec3(0.0f,0.0f,0.0f)), m_isLocked(false),
  m_colour(glm::vec3(1.0f,1.0f,1.0f))
{
}

MassPoint::MassPoint(float _mass, glm::vec3 _pos) : m_mass(_mass), m_pos(_pos), m_vel(glm::vec3(0.0f,0.0f,0.0f)),
  m_internalForces(glm::vec3(0.0f,0.0f,0.0f)), m_externalForces(glm::vec3(0.0f,0.0f,0.0f)), m_isLocked(false),
  m_colour(glm::vec3(1.0f,1.0f,1.0f))
{
}

MassPoint::MassPoint(float _mass, glm::vec3 _pos, bool _isLocked) : m_mass(_mass), m_pos(_pos), m_vel(glm::vec3(0.0f,0.0f,0.0f)),
  m_internalForces(glm::vec3(0.0f,0.0f,0.0f)), m_externalForces(glm::vec3(0.0f,0.0f,0.0f)), m_isLocked(_isLocked),
  m_colour(glm::vec3(1.0f,1.0f,1.0f))
{
}

MassPoint::~MassPoint()
{

}

void MassPoint::update(float _dt)
{
  //only update if the MassPoint is unlocked
  if (!m_isLocked)
  {
    //calculate the net force on the point
    glm::vec3 netForces = m_internalForces + m_externalForces;

    //Logging::logGLMVec3(m_externalForces);
    //Logging::logGLMVec3(m_internalForces);
    //Logging::logGLMVec3(netForces);
    //Logging::logI(std::to_string(_dt));

    //calculate the acceleration of the point
    glm::vec3 acceleration = netForces/m_mass;

    //calculate the velocity of the point
    m_vel += (acceleration * _dt);

    //calculate the position of the point
    m_pos += (m_vel * _dt);
  }
}

void MassPoint::setMass(float _mass)
{
  m_mass = _mass;
}

float MassPoint::getMass()
{
  return  m_mass;
}

void MassPoint::setPos(glm::vec3 _pos)
{
  m_pos = _pos;
}

glm::vec3 MassPoint::getPos()
{
  return m_pos;
}

void MassPoint::setVel(glm::vec3 _vel)
{
  m_vel = _vel;
}

glm::vec3 MassPoint::getVel()
{
  return m_vel;
}

void MassPoint::updateVel(glm::vec3 _vel)
{
  m_vel += _vel;
}

void MassPoint::setInternalForces(glm::vec3 _internalForces)
{
  m_internalForces = _internalForces;
}

glm::vec3 MassPoint::getInternalForces()
{
  return m_internalForces;
}

void MassPoint::updateInternalForces(glm::vec3 _internalForces)
{
  m_internalForces += _internalForces;
}

void MassPoint::setExternalForces(glm::vec3 _externalForces)
{
  m_externalForces = _externalForces;
}

glm::vec3 MassPoint::getExternalForces()
{
  return m_externalForces;
}

void MassPoint::updateExternalForces(glm::vec3 _externalForces)
{
  m_externalForces += _externalForces;
}

void MassPoint::lock()
{
  m_isLocked = true;
}

void MassPoint::unlock()
{
  m_isLocked = false;
}

bool MassPoint::getIsLocked()
{
  return m_isLocked;
}

void MassPoint::setColour(glm::vec3 _colour)
{
  m_colour = _colour;
}

glm::vec3 MassPoint::getColour()
{
  return m_colour;
}
