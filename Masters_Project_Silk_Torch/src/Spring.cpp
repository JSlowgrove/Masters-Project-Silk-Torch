#include "Spring.h"
#include "Logging.h"

Spring::Spring() : m_springConstant(10.0f), m_damping(20.0f)
{
}

Spring::Spring(float _springConstant) : m_springConstant(_springConstant), m_damping(20.0f)
{
}

Spring::Spring(float _springConstant, float _damping) : m_springConstant(_springConstant), m_damping(_damping)
{
}

Spring::~Spring()
{
}

float Spring::getSpringConstant()
{
  return m_springConstant;
}

void Spring::setSpringConstant(float _springConstant)
{
  m_springConstant = _springConstant;
}

float Spring::getDamping()
{
  return m_damping;
}

void Spring::setDamping(float _damping)
{
  m_damping = _damping;
}

glm::vec3 Spring::getPointAAttachedPos()
{
  return m_pointAAttachedPos;
}

void Spring::setPointAAttachedPos(glm::vec3 _pointAAttachedPos)
{
  m_pointAAttachedPos = _pointAAttachedPos;
}

std::shared_ptr<MassPoint> Spring::getPointA()
{
  return m_pointA;
}

void Spring::setPointA(std::shared_ptr<MassPoint> _pointA)
{
  m_pointA = _pointA;
}

std::shared_ptr<MassPoint> Spring::getPointB()
{
  return m_pointB;
}

void Spring::setPointB(std::shared_ptr<MassPoint> _pointB)
{
  m_pointB = _pointB;
}

void Spring::update()
{
  //calculated spring force of point A
  glm::vec3 springForceA = -m_springConstant * (m_pointA->getPos() - m_pointAAttachedPos);
  //calculated spring force of point B
  glm::vec3 springForceB = -m_springConstant * (m_pointB->getPos() - m_pointA->getPos());

  //calculate damping force of point A
  glm::vec3 dampingForcePointA = m_damping * m_pointA->getVel();
  //calculate damping force of point B
  glm::vec3 dampingForcePointB = m_damping * m_pointB->getVel();

  //update the internal force of the points
  m_pointA->updateInternalForces(springForceA - dampingForcePointA -springForceB + dampingForcePointB);
  m_pointB->updateInternalForces(springForceB - dampingForcePointB);
}
