#ifndef MASSSPRINGOBJECT_H_
#define MASSSPRINGOBJECT_H_

#include <vector>
#include <memory>
#include <ngl/SimpleVAO.h>
#include <ngl/VAOFactory.h>
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
  std::vector<GLshort> getIndices();

  /**
  @brief Gets the uv's of the MassSpringObject.
  @returns A std::vector of the uv's.
  */
  std::vector<glm::vec2> getUVs();

  /**
  @brief Gets the vertices of the MassSpringObject.
  @returns A std::vector of the Vertices.
  */
  std::vector<glm::vec3> getVertices();

  /**
  @brief Gets the normals of the MassSpringObject.
  @returns A std::vector of the normals.
  */
  std::vector<glm::vec3> getNormals();

  /**
  @brief Gets the position of the MassSpringObject.
  @returns The position of the MassSpringObject.
  */
  glm::vec3 getPos();

  /**
  @brief Sets the position of the MassSpringObject.
  @param[in] _pos The position of the MassSpringObject.
  */
  void setPos(glm::vec3 _pos);

  /**
  @brief Gets the scale of the MassSpringObject.
  @returns The scale of the MassSpringObject.
  */
  glm::vec3 getScale();

  /**
  @brief Sets the scale of the MassSpringObject.
  @param[in] _scale The scale of the MassSpringObject.
  */
  void setScale(glm::vec3 _scale);

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

  /**
  @brief A function to build the VAO data for the massSpringObject.
  */
  void buildVAOData();

  /**
  @brief A function to rebuild the VAO data for the massSpringObject.
  */
  void reBuildVAOData();

  /**
  @brief Gets the VAO data of the MassSpringObject.
  @returns A std::vector of floats for the VAO.
  */
  std::vector<float> getVAOData();

  /**
  @brief Sets the amount of time the wind impulse is on.
  @param[in] _impulseOnTime The amount of time the wind impulse is on.
  */
  void setImpulseOnTime(float _impulseOnTime);

  /**
  @brief Sets the amount of time the wind impulse is off.
  @param[in] _impulseOffTime The amount of time the wind impulse is off.
  */
  void setImpulseOffTime(float _impulseOffTime);

  /**
  @brief Sets the value of the boyancy of the MassSpringObject.
  @param[in] _boyancy The boyancy of the MassSpringObject.
  */
  void setBoyancy(float _boyancy);

  /**
  @brief Sets the wind force acting on the MassSpringObject.
  @param[in] _axis The axis to set.
  @param[in] _windForce The wind force acting on the MassSpringObject.
  */
  void setWindForce(char _axis, float _windForce);

  /**
  @brief Sets the mass of the MassPoints.
  @param[in] _mass The mass of the MassPoints.
  */
  void setMass(float _mass);

  /**
  @brief Sets the constant of the Springs.
  @param[in] _springConstant The spring constant.
  */
  void setSpringConstant(float _springConstant);

  /**
  @brief Sets the damping of the MassSpringObject.
  @param[in] _damping The damping of the MassSpringObject.
  */
  void setDamping(float _damping);

  /**
  @brief Sets the rest length of the Springs.
  @param[in] _restLength The spring rest length.
  */
  void setRestLength(float _restLength);

  /**
  @brief Gets the transformation matrix of the MassSpringObject.
  @returns The transformation matrix.
  */
  glm::mat4 getTransform();

  /**
  @brief Sets the texture number of the MassPointObject.
  @param[in] _textureNum The new texture num.
  */
  void setTextureNum(int _textureNum);

  /**
  @brief Gets the texture number of the MassPointObject.
  @returns The texture number of the MassPointObject.
  */
  int getTextureNum();

private:
  ///The array of pointers for the MassPoints.
  std::vector<std::shared_ptr<MassPoint>> m_points;
  ///The array of pointers for the Springs.
  std::vector<std::shared_ptr<Spring>> m_springs;
  ///The size of the grid of points
  unsigned int m_gridSize;
  ///The indices of the MassSpringObject.
  std::vector<GLshort> m_indices;
  ///The uv's of the MassSpringObject.
  std::vector<glm::vec2> m_uvs;
  ///The vertices of the MassSpringObject.
  std::vector<glm::vec3> m_vertices;
  ///The normals of the MassSpringObject.
  std::vector<glm::vec3> m_normals;
  ///The time since last wind impluse.
  float m_impulseTime;
  ///A boolean for if the impulse is active.
  bool m_impulse;
  ///The position of the MassSpringObject.
  glm::vec3 m_pos;
  ///The scale of the MassSpringObject.
  glm::vec3 m_scale;
  ///The std::vector of floats for the VAO.
  std::vector<float> m_vaoData;
  ///The amount of time the wind impulse is on.
  float m_impulseOnTime;
  ///The amount of time the wind impulse is off.
  float m_impulseOffTime;
  ///The boyancy of the MassSpringObject.
  float m_boyancy;
  ///The wind force.
  glm::vec3 m_windForce;
  ///The spring constant of the springs.
  float m_k;
  ///The damping of the MassSpringObject.
  float m_damp;
  ///The rest length of the springs.
  float m_restLength;
  ///The transformation matrix of the MassSpringObject.
  glm::mat4 m_transform;
  ///The texture num.
  int m_textureNum;

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
  @brief Generate the springs for the MassSpringObject.
  */
  void generateSprings();

  /**
  @brief Generate the normals for the MassSpringObject.
  */
  void generateNormals();

  /**
  @brief Generate the transformation matrix for the MassSpringObject.
  */
  void generateTransform();

  /**
  @brief A function to get a normal from 3 vectors.
  @param[in] _a Vector A.
  @param[in] _B Vector B.
  @param[in] _c Vector C.
  @returns A normal of the 3 vectors.
  */
  glm::vec3 getNormal(glm::vec3 _a, glm::vec3 _b, glm::vec3 _c);
};

#endif // MASSSPRINGOBJECT_H_
