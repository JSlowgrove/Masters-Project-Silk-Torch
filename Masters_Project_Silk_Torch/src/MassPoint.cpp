#include "MassPoint.h"

MassPoint::MassPoint() : m_mass(10.0f), m_pos(glm::vec3(0.0f,0.0f,0.0f)), m_isLocked(false)
{
}

MassPoint::MassPoint(float _mass, glm::vec3 _pos) : m_mass(_mass), m_pos(_pos), m_isLocked(false)
{
}

MassPoint::MassPoint(float _mass, glm::vec3 _pos, bool _isLocked) : m_mass(_mass), m_pos(_pos), m_isLocked(_isLocked)
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
