#include "NGLScene.h"
#include <iostream>
#include <ngl/Vec3.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <QColorDialog>
#include <ngl/SimpleIndexVAO.h>

NGLScene::NGLScene( QWidget *_parent ) : QOpenGLWidget( _parent ), m_projectRunning(false)
{

  // set this widget to have the initial keyboard focus
  setFocus();
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
	m_wireframe=false;
	m_rotation=0.0;
	m_scale=1.0;
	m_position=0.0;

	m_selectedObject=0;

  //set the number of milliseconds the frame timer should run at
  m_timerMilliseconds = 10;
}

NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
  m_vao->removeVAO();
}

// This virtual function is called once before the first call to paintGL() or resizeGL(),
//and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining display lists, etc.
void NGLScene::initializeGL()
{

  ngl::NGLInit::instance();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);
  /// create our camera
  ngl::Vec3 eye = ngl::Vec3(0.0f,0.0f,10.0f);
  ngl::Vec3 look(0,0,0);
  ngl::Vec3 up(0,1,0);

  m_view=ngl::lookAt(eye,look,up);
  m_project=ngl::perspective(45,float(1024/720),0.1f,300.0f);
  // now to load the shader and set the values
  // grab an instance of shader manager
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  // load a frag and vert shaders
  constexpr auto ColourShader="ColourShader";
  constexpr auto ColourVertex="ColourVertex";
  constexpr auto ColourFragment="ColourFragment";
  shader->createShaderProgram(ColourShader);

  shader->attachShader(ColourVertex,ngl::ShaderType::VERTEX);
  shader->attachShader(ColourFragment,ngl::ShaderType::FRAGMENT);

  std::string PWD = std::getenv("PWD");
  shader->loadShaderSource(ColourVertex, PWD + "/Masters_Project_Silk_Torch/shaders/ColourVertex.glsl");
  shader->loadShaderSource(ColourFragment, PWD + "/Masters_Project_Silk_Torch/shaders/ColourFragment.glsl");

  shader->compileShader(ColourVertex);
  shader->compileShader(ColourFragment);
  shader->attachShaderToProgram(ColourShader,ColourVertex);
  shader->attachShaderToProgram(ColourShader,ColourFragment);


  shader->linkProgramObject(ColourShader);
  (*shader)[ColourShader]->use();

  buildVAO();
  ngl::VAOFactory::listCreators();
}

//This virtual function is called whenever the widget has been resized.
// The new size is passed in width and height.
void NGLScene::resizeGL( int _w, int _h )
{
  m_project=ngl::perspective( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::buildVAO()
{
  // create a vao as a series of GL_TRIANGLES
  m_vao=ngl::VAOFactory::createVAO(ngl::simpleIndexVAO,GL_TRIANGLES);
  m_vao->bind();

  //set the vao data
  //TODO

 // now unbind
  m_vao->unbind();
}

//This virtual function is called whenever the widget needs to be painted.
// this is our main drawing routine
void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  // Rotation based on the mouse position for our global
  // transform
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create the rotation matrices
  rotX.rotateX(m_win.spinXFace);
  rotY.rotateY(m_win.spinYFace);
  // multiply the rotations
  m_mouseGlobalTX=rotY*rotX;
  // add the translations
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

  if(m_wireframe == true)
  {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  }

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["ColourShader"]->use();

  ngl::Mat4 MVP= m_project*m_view*m_mouseGlobalTX;
  shader->setUniform("MVP",MVP);

  //draw objects
  //TODO
}

void NGLScene::toggleWireframe(bool _mode	 )
{
    Logging::logI("Wireframe " + Logging::boolToString(_mode));
	m_wireframe=_mode;
	update();
}

void NGLScene::runProject()
{
  Logging::logI("Start Project");
  startTimer(m_timerMilliseconds);
  m_projectRunning = true;
  update();
}

void NGLScene::restartProject()
{
  Logging::logI("Restart Project");
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
    //calculate the dt from the frame timer
    float dt = 1.0f / (m_timerMilliseconds * 1000.0f);

    //timer event code
    // TODO

    // Update and redraw
    update();
}

void NGLScene::drawLines(std::vector<glm::vec3> & _lineVertAndColour, std::vector<GLshort> & _lineIndices)
{
    m_vao=ngl::VAOFactory::createVAO(ngl::simpleIndexVAO,GL_LINES);

    m_vao->bind();
    m_vao->setData(ngl::SimpleIndexVAO::VertexData(
                                                    _lineVertAndColour.size() * sizeof(glm::vec3),
                                                    _lineVertAndColour[0].x,
                                                    uint(_lineIndices.size()),
                                                    &_lineIndices[0],
                                                    GL_UNSIGNED_SHORT));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(glm::vec3) * 2,0);
    m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(glm::vec3) * 2,3);
    m_vao->setNumIndices(_lineVertAndColour.size());

    m_vao->draw();
    m_vao->unbind();
}
