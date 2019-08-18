#include "MassSpringObject.h"
#include "CustomDefs.h"
#include "Utilities.h"
#include "Logging.h"
#include "glm/gtc/matrix_transform.hpp"

MassSpringObject::MassSpringObject() : m_gridSize(10), m_impulseTime(0.0f), m_impulse(true), m_pos(glm::vec3(0.0f,0.0f,0.0f)),
  m_scale(glm::vec3(1.0f,1.0f,1.0f)), m_impulseOnTime(1.0f), m_impulseOffTime(5.0f), m_boyancy(10.0f), m_windForce(glm::vec3(0.0f,0.0f,-5.0f)),
  m_k(100.0f), m_damp(0.1f), m_restLength(1.0f), m_textureNum(0)
{
  initialiseMassSpringObject(10.0f);
}

MassSpringObject::MassSpringObject(unsigned int _gridSize) : m_gridSize(_gridSize), m_impulseTime(0.0f), m_impulse(true),
  m_pos(glm::vec3(0.0f,0.0f,0.0f)), m_scale(glm::vec3(1.0f,1.0f,1.0f)), m_impulseOnTime(1.0f), m_impulseOffTime(5.0f), m_boyancy(10.0f),
  m_windForce(glm::vec3(0.0f,0.0f,-5.0f)), m_k(100.0f), m_damp(0.1f), m_restLength(1.0f), m_textureNum(0)
{
  initialiseMassSpringObject(10.0f);
}

MassSpringObject::MassSpringObject(unsigned int _gridSize, float _mass) : m_gridSize(_gridSize), m_impulseTime(0.0f), m_impulse(true),
  m_pos(glm::vec3(0.0f,0.0f,0.0f)), m_scale(glm::vec3(1.0f,1.0f,1.0f)), m_impulseOnTime(1.0f), m_impulseOffTime(5.0f), m_boyancy(10.0f),
  m_windForce(glm::vec3(0.0f,0.0f,-5.0f)), m_k(100.0f), m_damp(0.1f), m_restLength(1.0f), m_textureNum(0)
{
  initialiseMassSpringObject(_mass);
}

void MassSpringObject::initialiseMassSpringObject(float _mass)
{
  // create the grid of particles
  generateGrid(_mass);

  // create the springs
  generateSprings();

  // generate the indicies
  generateIndices();

  // generate the vertices
  generateVertices();

  // generate the normals
  generateNormals();

  // generate the transformation matrix
  generateTransform();
}

MassSpringObject::~MassSpringObject()
{
}

unsigned int MassSpringObject::getGridSize()
{
  return m_gridSize;
}

void MassSpringObject::setGridSize(unsigned int _gridSize)
{
  m_gridSize = _gridSize;
}

std::shared_ptr<MassPoint> MassSpringObject::getMassPoint(unsigned int _pointIndex)
{
  return m_points[_pointIndex];
}

std::vector<GLshort> MassSpringObject::getIndices()
{
  return m_indices;
}

std::vector<glm::vec2> MassSpringObject::getUVs()
{
  return m_uvs;
}

std::vector<glm::vec3> MassSpringObject::getVertices()
{
  return m_vertices;
}

std::vector<glm::vec3> MassSpringObject::getNormals()
{
  return m_normals;
}

glm::vec3 MassSpringObject::getPos()
{
  return m_pos;
}

void MassSpringObject::setPos(glm::vec3 _pos)
{
  m_pos = _pos;
}

glm::vec3 MassSpringObject::getScale()
{
  return m_scale;
}

void MassSpringObject::setScale(glm::vec3 _scale)
{
  m_scale = _scale;
}

void MassSpringObject::update(float _dt)
{
  //update the impulse time
  m_impulseTime += _dt;

  //check if impluse needs to be turned on or off
  if (m_impulseTime > m_impulseOnTime && m_impulse)
  {
    //reset impulse time
    m_impulseTime -= m_impulseOnTime;
    m_impulse = false;
    //Logging::logI("IMPULSE");
  }
  else if (m_impulseTime > m_impulseOffTime && !m_impulse)
  {
    //reset impulse time
    m_impulseTime -= m_impulseOffTime;
    m_impulse = true;
    //Logging::logI("IMPULSE");
  }

  //apply the external forces to the points and reset the internal forces
  for (auto point : m_points)
  {
    if (m_impulse)
    {
      point->setExternalForces(m_windForce);
    }
    else
    {
      point->setExternalForces(glm::vec3(0.0f,0.0f,0.0f));
    }
    point->setExternalForces(glm::vec3(point->getExternalForces().x,m_boyancy,point->getExternalForces().z));
    point->setInternalForces(glm::vec3(0.0f,0.0f,0.0f));
  }

  //update the Springs
  for (auto spring : m_springs)
  {
    spring->update();
  }
  //update the MassPoints
  for (auto point : m_points)
  {
    point->update(_dt);
  }

  //update the vertices of the MassSpringObject
  updateVertices();

  // generate the transformation matrix
  generateTransform();
}

void MassSpringObject::reset()
{
  //get the mass of the points
  float mass = m_points[0]->getMass();
  //empty the particle std::vector
  m_points.resize(0);
  //empty the springs
  m_springs.resize(0);
  //generate the points
  generateGrid(mass);
  //update the vertices with the reset particles
  updateVertices();
  //generate the springs
  generateSprings();
}

std::vector<std::shared_ptr<Spring> > MassSpringObject::getSprings()
{
  return m_springs;
}

void MassSpringObject::generateGrid(float _mass)
{
  /*
  Grid order example
  6-7-8
  | | |
  3-4-5
  | | |
  0-1-2
  */


  // create the grid of particles
  for (unsigned int y = 0; y < m_gridSize; ++y)
  {
    for (unsigned int x = 0; x < m_gridSize; ++x)
    {
      // Generate the postion of the point bewteen 0 and the gird size
      glm::vec3 newPos = glm::vec3(float(x),float(y), 0.0f);

      //store the point in the std::vector
      m_points.push_back(std::shared_ptr<MassPoint>(new MassPoint(_mass, newPos - (m_gridSize * 0.5f))));
    }
  }

  //lock bottom row
  for (unsigned int i = 0; i < m_gridSize; i++)
  {
    m_points[i]->lock();
    m_points[i]->setColour(glm::vec3(1.0f,0.0f,0.0f));
  }
}

void MassSpringObject::generateIndices()
{
  unsigned int i = 0;

  float uvOffset = (1.0f / (m_gridSize - 1));

  for (unsigned int y = 0; y < m_gridSize; y++)
  {
    for (unsigned int x = 0; x < m_gridSize; x++)
    {
      /*
      if the current position is not the the last row or the last column then create an indices for the triangle,
      this check is to stop infinite triangles
      */
      if (i < ((m_gridSize * m_gridSize) - m_gridSize) && x < m_gridSize - 1)
      {
        i = (y * m_gridSize) + x;
        // adds the first triangle of the current square
        m_indices.push_back(GLshort(i));
        m_indices.push_back(GLshort(i + m_gridSize));
        m_indices.push_back(GLshort(i + m_gridSize + 1));
        // adds the second triangle of the current square
        m_indices.push_back(GLshort(i));
        m_indices.push_back(GLshort(i + m_gridSize + 1));
        m_indices.push_back(GLshort(i + 1));
      }

      //generate the texture coordinates
      m_uvs.push_back(glm::vec2(float(x) * uvOffset,
                                float(y) * uvOffset));
      ++i;
    }
  }
}

void MassSpringObject::generateVertices()
{
  for (auto point : m_points)
  {
    m_vertices.push_back(point->getPos());
  }
}

void MassSpringObject::updateVertices()
{
  for (unsigned int i = 0; i < m_vertices.size(); ++i)
  {
    m_vertices[i] = m_points[i]->getPos();
  }
}

void MassSpringObject::generateSprings()
{
  for (unsigned int i = 0; i < m_points.size(); ++i)
  {
    //check if not on right side of the mass spring object
    if (i % m_gridSize != 0)
    {
      //hoizontal Spring
      std::shared_ptr<Spring> spring(new Spring(m_k, m_damp, m_restLength, i));
      spring->setPlane('H');
      spring->setPointA(m_points[i]);
      spring->setPointB(m_points[i - 1]);
      m_springs.push_back(spring);
    }

    //check if not on top side of the mass spring object
    if (i < m_points.size() - m_gridSize)
    {
      //vertical Spring
      std::shared_ptr<Spring> spring(new Spring(m_k, m_damp, m_restLength, i));
      spring->setPlane('V');
      spring->setPointA(m_points[i + m_gridSize]);
      spring->setPointB(m_points[i]);
      m_springs.push_back(spring);
    }
  }
}

void MassSpringObject::buildVAOData()
{
  for (unsigned int i = 0; i < u_int(m_vertices.size()); ++i)
  {
    m_vaoData.push_back(m_vertices[ulong(i)].x);
    m_vaoData.push_back(m_vertices[ulong(i)].y);
    m_vaoData.push_back(m_vertices[ulong(i)].z);
    m_vaoData.push_back(m_uvs[ulong(i)].x);
    m_vaoData.push_back(m_uvs[ulong(i)].y);
  }
}

void MassSpringObject::reBuildVAOData()
{
  m_vaoData.resize(0);
  buildVAOData();
}

std::vector<float> MassSpringObject::getVAOData()
{
  return m_vaoData;
}

void MassSpringObject::setImpulseOnTime(float _impulseOnTime)
{
  m_impulseOnTime = _impulseOnTime;
}

void MassSpringObject::setImpulseOffTime(float _impulseOffTime)
{
  m_impulseOffTime = _impulseOffTime;
}

void MassSpringObject::setBoyancy(float _boyancy)
{
  m_boyancy = _boyancy;
}

void MassSpringObject::setWindForce(char _axis, float _windForce)
{
  switch(_axis)
  {
    case 'x':
      m_windForce.x = _windForce;
      break;
    case 'y':
      m_windForce.y = _windForce;
      break;
    case 'z':
      m_windForce.z = _windForce;
      break;
  }
}

void MassSpringObject::setMass(float _mass)
{
  for (auto massPoint : m_points)
  {
    massPoint->setMass(_mass);
  }
}

void MassSpringObject::setSpringConstant(float _springConstant)
{
  m_k = _springConstant;
  for (auto spring : m_springs)
  {
    spring->setSpringConstant(_springConstant);
  }
}

void MassSpringObject::setDamping(float _damping)
{
  m_damp = _damping;
  for (auto spring : m_springs)
  {
    spring->setDamping(_damping);
  }
}

void MassSpringObject::setRestLength(float _restLength)
{
  m_restLength = _restLength;
  for (auto spring : m_springs)
  {
    spring->setRestLength(_restLength);
  }
}

glm::mat4 MassSpringObject::getTransform()
{
  return m_transform;
}

void MassSpringObject::setTextureNum(int _textureNum)
{
  m_textureNum = _textureNum;
}

int MassSpringObject::getTextureNum()
{
  return m_textureNum;
}

void MassSpringObject::generateNormals()
{
  //create the normals for all of the triangles
  for (unsigned int i = 0; i < m_gridSize * m_gridSize; i++)
  {
    if (i >= (m_gridSize*m_gridSize) - m_gridSize - 1) //quick hack to get normal array size to match vertices array
    {
      m_normals.push_back(m_vertices[i]);
    }
    else if ((i % 2) == 0)//work out if the current index is a multiple of two and switch between the needed normal type to get accordingly
    {
      glm::vec3 norm = getNormal(m_vertices[i], m_vertices[i + 1], m_vertices[i + m_gridSize]);
      m_normals.push_back(norm);
    }
    else
    {
      glm::vec3 norm = getNormal(m_vertices[i + m_gridSize], m_vertices[i + 1], m_vertices[i + m_gridSize + 1]);
      m_normals.push_back(norm);
    }
  }
}

void MassSpringObject::generateTransform()
{
  //translate an identity matrix
  m_transform = glm::translate(glm::mat4(1.0f), m_pos);

  //scale the matrix
  m_transform = glm::scale(m_transform, m_scale);
}

glm::vec3 MassSpringObject::getNormal(glm::vec3 _a, glm::vec3 _b, glm::vec3 _c)
{
  //a function to work out the normals for the map

  //*******************************
  //***	C **************************
  //***	  |\ ***********************
  //***	^ | \ **********************
  //***	| |  \ *********************
  //***	  ----- ********************
  //***	A -----> B *****************
  //********************************

  glm::vec3 ab = _b - _a; //up
  glm::vec3 ac = _c - _a; //right

  glm::vec3 normals;
  normals.x = (ac.y*ab.z) - (ac.z*ab.y);//work out the x of the normal
  normals.y = -((ab.z*ac.x) - (ab.x*ac.z));//work out the y of the normal
  normals.z = (ac.x*ab.y) - (ac.y*ab.x);//work out the z of the normal

  //the factor that I need to divide by to work out the normal
  float factor = float(sqrt(double((normals.x * normals.x) + (normals.y * normals.y) + (normals.z * normals.z))));

  //works out the normals
  normals.x = normals.x / factor;
  normals.y = normals.y / factor;
  normals.z = normals.z / factor;

  return normals;// returns the normal
}
