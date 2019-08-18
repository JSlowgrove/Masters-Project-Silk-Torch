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
#include <ngl/Text.h>
#include <memory>

#include "glm/glm.hpp"
#include "Logging.h"
#include "WindowParams.h"
#include "MassSpringObject.h"
#include "Timer.h"


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

    /**
    @brief A slot to set the buoyancy of the MassSpringObjects.
    @param[in] _mode The value of buoyancy.
    */
    void setBuoyancy(double _buoyancy);

    /**
    @brief A slot to set the wind impulse on time.
    @param[in] _mode The value of the wind impulse on time.
    */
    void setWindImpulseOn(double _windImpulseOn);

    /**
    @brief A slot to set the wind impulse off time.
    @param[in] _mode The value of the wind impulse off time.
    */
    void setWindImpulseOff(double _windImpulseOff);

    /**
    @brief A slot to set the force of the wind in the X axis.
    @param[in] _x The value of the force of the wind in the X axis.
    */
    void setWindForceX(double _x);

    /**
    @brief A slot to set the force of the wind in the Y axis.
    @param[in] _y The value of the force of the wind in the Y axis.
    */
    void setWindForceY(double _y);

    /**
    @brief A slot to set the force of the wind in the Z axis.
    @param[in] _z The value of the force of the wind in the Z axis.
    */
    void setWindForceZ(double _z);

    /**
    @brief A slot to set the mass of the MassSpringObject MassPoints.
    @param[in] _z The value of the mass.
    */
    void setMass(double _mass);

    /**
    @brief A slot to set the spring constant of the MassPointObject Springs.
    @param[in] _z The value of the spring constant.
    */
    void setSpringConstant(double _springConstant);

    /**
    @brief A slot to set the damping force of the MassSpringObject.
    @param[in] _z The value of the damping force.
    */
    void setDamping(double _damping);

    /**
    @brief A slot to set the rest length of the MassPointObject Springs.
    @param[in] _z The value of the rest length.
    */
    void setRestLength(double _restLength);

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
  std::vector<std::shared_ptr<MassSpringObject>> m_massSpringObjects;
  ///The name of the texture
  GLuint m_textureName[9];
  ///A flag for if the texture shader should be used.
  bool m_textured;
  ///The Timer for delta time.
  Timer m_timer;
  ///The delta time.
  float m_dt;
  ///The time for the frame rate.
  float m_frameRateTime;
  ///The current frame rate.
  int m_frameRate;
  ///The current frame rate.
  int m_FPS;
  ///A flag for the initial run
  bool initRun;
  ///Frame rate text
  std::unique_ptr<ngl::Text> m_frameRateText;
  ///Number of mass spring objects
  int m_numMassSpringObjects;
  ///The scale of the mass spring objects
  float m_MSOScale;

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
  @param[in] _event The Qt Event structure.
  */
  void wheelEvent(QWheelEvent* _event) override;

  /**
  @brief A funciton to set the data to be used by the VAO.
  @param[in] _massSpringIndex The index of the mass spring.
  */
  void setVAOData(unsigned int _massSpringIndex);

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
  @brief The frame timer for the simulation.
  @param _event The QT timer event.
  */
  void timerEvent(QTimerEvent *_event) override;
};

#endif //NGLSCENE_H_
