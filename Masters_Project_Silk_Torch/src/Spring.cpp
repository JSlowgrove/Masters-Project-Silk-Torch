#include "Spring.h"
#include "Logging.h"
#include <cmath>

Spring::Spring(unsigned int _id) : m_springConstant(10.0f), m_damping(20.0f), m_id(_id),
  m_springForce(std::shared_ptr<glm::vec3>(new glm::vec3(0.0f,0.0f,0.0f))), m_restLength(1.0f)
{
}

Spring::Spring(float _springConstant, unsigned int _id) : m_springConstant(_springConstant), m_damping(20.0f),
  m_id(_id), m_springForce(std::shared_ptr<glm::vec3>(new glm::vec3(0.0f,0.0f,0.0f))), m_restLength(1.0f)
{
}

Spring::Spring(float _springConstant, float _damping, unsigned int _id) : m_springConstant(_springConstant),
  m_damping(_damping), m_id(_id), m_springForce(std::shared_ptr<glm::vec3>(new glm::vec3(0.0f,0.0f,0.0f))), m_restLength(1.0f)
{
}

Spring::Spring(float _springConstant, float _damping, float _restLength, unsigned int _id) : m_springConstant(_springConstant),
  m_damping(_damping), m_id(_id), m_springForce(std::shared_ptr<glm::vec3>(new glm::vec3(0.0f,0.0f,0.0f))), m_restLength(_restLength)
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

  //Logging::logI("setSpringConst");
}

float Spring::getDamping()
{
  return m_damping;
}

void Spring::setDamping(float _damping)
{
  m_damping = _damping;
  m_pointA->setDamping(_damping);
  m_pointB->setDamping(_damping);
}

unsigned int Spring::getId()
{
  return m_id;
}

void Spring::setId(unsigned int _id)
{
  m_id = _id;
}

char Spring::getPlane()
{
  return m_plane;
}

void Spring::setPlane(char _plane)
{
  m_plane = _plane;
}

std::shared_ptr<MassPoint> Spring::getPointA()
{
  return m_pointA;
}

void Spring::setPointA(std::shared_ptr<MassPoint> _pointA)
{
  m_pointA = _pointA;

  //add the spring to the point
  m_pointA->addSpringInfo(m_id, 'A', m_plane, m_springForce, m_damping);
}

std::shared_ptr<MassPoint> Spring::getPointB()
{
  return m_pointB;
}

void Spring::setPointB(std::shared_ptr<MassPoint> _pointB)
{
  m_pointB = _pointB;

  //add the spring to the point
  m_pointB->addSpringInfo(m_id, 'B', m_plane, m_springForce, m_damping);
}

std::shared_ptr<glm::vec3> Spring::getSpringForce()
{
  return m_springForce;
}

float Spring::getRestLength()
{
  return m_restLength;
}

void Spring::setRestLength(float _restLength)
{
  m_restLength = _restLength;

  //Logging::logI("setRestLength");
}


void Spring::update()
{
  //calculate the force of the spring
  float springLength = glm::distance(m_pointA->getPos(), m_pointB->getPos());
  float springForceMagnitude = -m_springConstant * (springLength - m_restLength);
  glm::vec3 springDirection = glm::normalize(m_pointB->getPos() - m_pointA->getPos());
  glm::vec3 springForce = springDirection * springForceMagnitude;
  m_springForce->x = springForce.x;
  m_springForce->y = springForce.y;
  m_springForce->z = springForce.z;
}
