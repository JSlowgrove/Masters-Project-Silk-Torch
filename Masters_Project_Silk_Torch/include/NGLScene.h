#ifndef NGLSCENE_H_
#define NGLSCENE_H_

#include <ngl/Transformation.h>
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <QEvent>
#include <QResizeEvent>
#include <QOpenGLWidget>
#include <ngl/SimpleVAO.h>
#include <ngl/VAOFactory.h>
#include <ngl/ShaderLib.h>
#include <memory>

#include "glm/glm.hpp"
#include "Logging.h"
#include "WindowParams.h"
#include "MassSpringObject.h"


/// @file NGLScene.h
/// @brief The class that contains the main GLWindow widget, plus all the drawing elements.
/// @author Jonathan Macey (Modified by Jamie Slowgrove)
/// @version 3.0
/// @date 24/01/19
/// Revision History:
/// Initial Version 10/10/10 (Binary day ;-0 )
/// Modified Verison 24/01/19 for use with ASE assignment.
/// Modified Verison 29/01/19 for continuation of code after ASE assignment.
/// Extracted Verison 19/03/19 from ASE assignment to use as template NGL project.
/// Modified Version 03/08/19 for the Master's Project.
class NGLScene : public QOpenGLWidget
{
  ///Required for Qt Signals/slots
  Q_OBJECT

public:

  /**
  @brief The Constructor for NLGScene (GLWindow)
  @param[in] _parent The parent window to create the GL context in.
  */
  NGLScene(QWidget *_parent);

  /**
  @brief Destructs the NLGScene.
  */
  ~NGLScene() override;

  ///The slots for use with the Qt UI
  public slots :

    /**
    @brief A slot to toggle wireframe mode.
    @param[in] _mode The mode passed from the toggle button.
    */
    void toggleWireframe(bool _mode);    

    /**
    @brief A slot to toggle if textured.
    @param[in] _mode The mode passed from the toggle button.
    */
    void toggleTextured(bool _mode);

    /**
    @brief A slot to run the project.
    */
    void runProject();

    /**
    @brief A slot to restart the project.
    */
    void restartProject();

protected:
  ///The model position.
  ngl::Vec3 m_modelPos;
  ///The view for the camera.
  ngl::Mat4 m_view;
  ///The projection for the camera.
  ngl::Mat4 m_project;
  ///The windows params (e.g. mouse, rotations, etc.)
  WinParams m_win;

private:
  ///The state of the wireframe mode.
  bool m_wireframe;
  /// The rotation data.
  ngl::Vec3 m_rotation;
  /// The scale data.
  ngl::Vec3 m_scale;
  /// The position data.
  ngl::Vec3 m_position;
  ///The object to draw.
  int m_selectedObject;
  ///The std::vector of floats for the VAO.
  std::vector<float> m_vaoData;
  ///The std::vector of indices for the VAO
  std::vector<GLshort> m_indices;
  ///The number of millisseconds for the project timer.
  int m_timerMilliseconds;
  ///The global mouse transformations.
  ngl::Mat4 m_mouseGlobalTX;
  ///A unique pointer for the VAO.
  std::unique_ptr<ngl::AbstractVAO> m_vao;
  ///Boolean for if the project is running
  bool m_projectRunning;
  ///The size of the massSpringObj grid
  unsigned int m_gridSize;
  ///The mass spring object
  MassSpringObject m_massSpringObj;
  ///The name of the texture
  GLuint m_textureName;
  ///A flag for if the texture shader should be used.
  bool m_textured;

protected:
  /**
  @brief This is called when the window is created. It is used to initalise GL.
  */
  void initializeGL() override;

  /**
  @brief This is called whenever the window is re-sized.
  @param[in] _w the width of the resized window.
  @param[in] _h the height of the resized window.
  */
  void resizeGL(int _w , int _h) override;

  /**
  @brief The main gl drawing routine which is called whenever the window needs to be re-drawn.
  */
  void paintGL() override;

private:
  /**
  @brief This method is called every time the mouse is moved.
  @param _event The Qt Event structure.
  */
  void mouseMoveEvent (QMouseEvent* _event) override;

  /**
  @brief tThis method is called everytime the mouse button is pressed and is inherited from QObject and overridden here.
  @param _event The Qt Event structure.
  */
  void mousePressEvent (QMouseEvent* _event) override;

  /**
  @brief This method is called everytime the mouse button is released and is inherited from QObject and overridden here.
  @param _event The Qt Event structure.
  */
  void mouseReleaseEvent (QMouseEvent *_event) override;

  /**
  @brief This method is called every time the mouse wheel is moved.
  @param _event The Qt Event structure.
  */
  void wheelEvent(QWheelEvent* _event) override;

  /**
  @brief A function to build the point grid VAO data for the mass spring mesh.
  */
  void buildVAOData();

  /**
  @brief A function to build the indices for the mass spring mesh.
  */
  void buildIndices();

  /**
  @brief A funciton to set the data to be used by the VAO.
  */
  void setVAOData();

  /**
  @brief A function to build the VAO.
  */
  void buildVAO();

  /**
  @brief A function to initalise a shader.
  @param[in] _shader The shader to initalise.
  @param[in] _vertexShaderName The name of the vertex shader to initalise.
  @param[in] _fragmentShaderName The name of the fragment shader to initalise.
  @param[in] _shaderName The name of the shader to initalise.
  */
  void initShader(ngl::ShaderLib* _shader, std::string _vertexShaderName, std::string _fragmentShaderName, std::string _shaderName);

  /**
  @brief A function to draw lines based on the vertices and indices passed in.
  @param[in] _lineVertAndColour A reference to the array of vertices and colours to draw.
  @param[in] _lineIndices A reference to the array of incides to use to draw the lines.
  */
  void drawLines(std::vector<glm::vec3> & _lineVertAndColour, std::vector<GLshort> & _lineIndices);

  /**
  @brief The frame timer for the simulation.
  @param _event The QT timer event.
  */
  void timerEvent(QTimerEvent *_event) override;
};

#endif //NGLSCENE_H_
