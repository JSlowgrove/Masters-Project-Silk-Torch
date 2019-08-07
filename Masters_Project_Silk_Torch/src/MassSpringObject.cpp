#include "MassSpringObject.h"
#include "CustomDefs.h"
#include "Utilities.h"
#include "Logging.h"

MassSpringObject::MassSpringObject() : m_gridSize(10)
{
  initialiseMassSpringObject(10.0f);
}

MassSpringObject::MassSpringObject(unsigned int _gridSize) : m_gridSize(_gridSize)
{
  initialiseMassSpringObject(10.0f);
}

MassSpringObject::MassSpringObject(unsigned int _gridSize, float _mass) : m_gridSize(_gridSize)
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

std::vector<unsigned int> MassSpringObject::getIndices()
{
  return m_indices;
}

std::vector<glm::vec3> MassSpringObject::getVertices()
{
  return m_vertices;
}

void MassSpringObject::update(float _dt)
{
  //apply the external forces to the points and reset the internal forces
  for (auto point : m_points)
  {
    point->setExternalForces(glm::vec3(0.0f,GRAVITY,0.0f));
    point->setInternalForces(glm::vec3(0.0f,0.0f,0.0f));
  }

  //update the Springs
  for (auto spring : m_springs)
  {
    spring->update();
  }

  /*Logging::logGLMVec3("Updated Spring Force: ", glm::vec3(m_springs[2]->getSpringForce()->x,
                      m_springs[2]->getSpringForce()->y, m_springs[2]->getSpringForce()->z), true);*/

  //update the MassPoints
  for (auto point : m_points)
  {
    point->update(_dt * 100.0f);
  }

  //update the vertices of the MassSpringObject
  updateVertices();
}

void MassSpringObject::reset()
{
  //get the mass of the points
  float mass = m_points[0]->getMass();
  //empty the particle std::vector
  m_points.resize(0);
  //empty the springs
  m_springs.resize(0);
  //generate the particles
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

  //lock the top two corners
  //m_points[(m_gridSize * m_gridSize)-1]->lock();
  //m_points[(m_gridSize * m_gridSize)-(m_gridSize)]->lock();

  //tmp lock top row
  for (unsigned int i = 1; i <= m_gridSize; ++i)
  {
    m_points[(m_gridSize * m_gridSize)-i]->lock();
    m_points[(m_gridSize * m_gridSize)-i]->setColour(glm::vec3(1.0f,0.0f,0.0f));
  }
  //TESTING
  /*for (unsigned long i = 0; i < m_points.size(); ++i)
  {
    //right column
    if (i % m_gridSize == m_gridSize - 1)
    {
      Logging::logI("grid " + std::to_string(i));

      m_points[i]->setColour(glm::vec3(1.0f,0.0f,0.0f));
    }

    //bottom row
    if (i >= m_gridSize)
    {
      m_points[i]->setColour(glm::vec3(0.0f,0.0f,1.0f));
    }
  }*/
}

void MassSpringObject::generateIndices()
{
  unsigned int i = 0;
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
        m_indices.push_back(i);
        m_indices.push_back(i + m_gridSize);
        m_indices.push_back(i + m_gridSize + 1);
        // adds the second triangle of the current square
        m_indices.push_back(i);
        m_indices.push_back(i + m_gridSize + 1);
        m_indices.push_back(i + 1);
      }
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
  float k = 100.0f;
  float damp = 10.0f;
  for (unsigned int i = 0; i < m_points.size(); ++i)
  {
    //check if not on right side of the mass spring object
    if (i % m_gridSize != 0)
    {
      //hoizontal Spring
      std::shared_ptr<Spring> spring(new Spring(k, damp, i));
      spring->setPlane('H');
      spring->setPointA(m_points[i]);
      spring->setPointB(m_points[i - 1]);
      m_springs.push_back(spring);
    }

    //check if not on top side of the mass spring object
    if (i < m_points.size() - m_gridSize)
    {
      //vertical Spring
      std::shared_ptr<Spring> spring(new Spring(k, damp, i));
      spring->setPlane('V');
      spring->setPointA(m_points[i + m_gridSize]);
      spring->setPointB(m_points[i]);
      m_springs.push_back(spring);
    }
  }
}
