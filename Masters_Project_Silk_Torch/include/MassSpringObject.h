#ifndef MASSSPRINGOBJECT_H_
#define MASSSPRINGOBJECT_H_

#include <vector>
#include <memory>
#include "glm/glm.hpp"

#include "MassPoint.h"
#include "Spring.h"

/// @file MassSpringObject.h
/// @brief A Class that contains all the functions and members for the mass spring object.
/// @author Jamie Slowgrove
/// @version 1.0
/// @date 03/08/19
/// Revision History:
/// Initial Version 03/08/19.
class MassSpringObject
{
public:
  /**
  @brief Constructs the MassSpringObject using the default mass and grid size of the points.
  */
  MassSpringObject();

  /**
  @brief Constructs the MassSpringObject using the default mass of the points.
  @param[in] _gridSize The size of the grid of points.
  */
  MassSpringObject(unsigned int  _gridSize);

  /**
  @brief Constructs the MassSpringObject.
  @param[in] _gridSize The size of the grid of points.
  @param[in] _mass The Mass of the points.
  */
  MassSpringObject(unsigned int  _gridSize, float _mass);

  /**
  @brief Destructs the MassSpringObject.
  */
  ~MassSpringObject();

  /**
  @brief Gets the size of the grid.
  @returns The size of the grid.
  */
  unsigned int getGridSize();

  /**
  @brief Gets the grid soze of the MassSpringObject.
  @returns The grid size of the MassSpringObject.
  */
  void setGridSize(unsigned int _gridSize);

  /**
  @brief Gets a specific point in the grid.
  @param[in] _pointIndex The index value of the wanted point.
  @returns A shared pointer to the point.
  */
  std::shared_ptr<MassPoint> getMassPoint(unsigned int _pointIndex);

  /**
  @brief Gets the indices of the MassSpringObject.
  @returns A std::vector of the Indices.
  */
  std::vector<unsigned int> getIndices();

  /**
  @brief Gets the vertices of the MassSpringObject.
  @returns A std::vector of the Vertices.
  */
  std::vector<glm::vec3> getVertices();

  /**
  @brief Updates the MassSpringObject.
  @returns _dt The Delta Time.
  */
  void update(float _dt);

  /**
  @brief Resets the MassSpringObject.
  */
  void reset();

  /**
  @brief Gets the Springs of the MassSpringObject.
  @returns A std::vector of the Springs shared pointers.
  */
  std::vector<std::shared_ptr<Spring>> getSprings();

private:
  ///The array of pointers for the MassPoints.
  std::vector<std::shared_ptr<MassPoint>> m_points;
  ///The array of pointers for the Springs.
  std::vector<std::shared_ptr<Spring>> m_springs;
  ///The size of the grid of points
  unsigned int m_gridSize;
  ///The indices of the MassSpringObject.
  std::vector<unsigned int> m_indices;
  ///The vertices of the MassSpringObject.
  std::vector<glm::vec3> m_vertices;
  ///The time since last wind impluse
  float m_impulseTime;

  /**
  @brief Initialises the MassSpringObject.
  */
  void initialiseMassSpringObject(float _mass);

  /**
  @brief Generates the grid of points.
  @param[in] _mass The Mass of the points.
  */
  void generateGrid(float _mass);

  /**
  @brief Generates the indices of the MassSpringObject.
  */
  void generateIndices();

  /**
  @brief Generates the verticies of the MassSpringObject.
  */
  void generateVertices();

  /**
  @brief Updates the verticies of the MassSpringObject.
  */
  void updateVertices();

  /**
  @brief Generated the springs for the MassSpringObject.
  */
  void generateSprings();
};

#endif // MASSSPRINGOBJECT_H_
