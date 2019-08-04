#include "MassSpringObject.h"
#include "CustomDefs.h"
#include "Utilities.h"

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
  //update the MassPoints
  for (auto point : m_points)
  {
    point->update(_dt);
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
    //TODO
}
