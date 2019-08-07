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
    //calculate the internal forces
    calculateInternalForces();

    //calculate the net force on the point
    glm::vec3 netForces = m_internalForces + m_externalForces;

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

void MassPoint::calculateInternalForces()
{
  //loop through the springs attached to the mass point
  for (auto spring : m_springInfo)
  {
    //calculate the damping force of the spring
    glm::vec3 dampingForce = spring.m_damping * m_vel;

    switch (spring.m_plane)
    {
    case 'V':
      switch (spring.m_type)
      {
      case 'A':
          //if it is point a on the spring the the spring force is - and the damping force is +
          m_internalForces.x += -spring.m_springForce->x + dampingForce.x;
          m_internalForces.y += -spring.m_springForce->y + dampingForce.y;
          m_internalForces.z += -spring.m_springForce->z + dampingForce.z;
        break;

      case 'B':
          //if it is point a on the spring the the spring force is + and the damping force is -
          m_internalForces.x += spring.m_springForce->x - dampingForce.x;
          m_internalForces.y += spring.m_springForce->y - dampingForce.y;
          m_internalForces.z += spring.m_springForce->z - dampingForce.z;
        break;
      }
    break;

    case 'H':
      switch (spring.m_type)
      {
      case 'A':
          //if it is point a on the spring the the spring force is - and the damping force is +
          m_internalForces.x += -spring.m_springForce->x + dampingForce.x;
          m_internalForces.y += -spring.m_springForce->y + dampingForce.y;
          m_internalForces.z += -spring.m_springForce->z + dampingForce.z;
        break;

      case 'B':
          //if it is point a on the spring the the spring force is + and the damping force is -
          m_internalForces.x += spring.m_springForce->x - dampingForce.x;
          m_internalForces.y += spring.m_springForce->y - dampingForce.y;
          m_internalForces.z += spring.m_springForce->z - dampingForce.z;
        break;
      }
     break;

     default:
       Logging::logE("NO PLANE SET!");
      break;

    }
  }
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

void MassPoint::addSpringInfo(unsigned int _id, char _type, char _plane,
                              std::shared_ptr<glm::vec3> _springForce,
                              float _damping)
{
  SpringInfo springInfo;
  springInfo.m_id = _id;
  springInfo.m_type = _type;
  springInfo.m_plane = _plane;
  springInfo.m_springForce = _springForce;
  springInfo.m_damping = _damping;
  m_springInfo.push_back(springInfo);
}
