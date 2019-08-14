#include "NGLScene.h"
#include <iostream>
#include <ngl/Vec3.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Texture.h>
#include <QColorDialog>
#include <ngl/SimpleIndexVAO.h>
#include <random>

#include "CustomDefs.h"

NGLScene::NGLScene( QWidget *_parent ) : QOpenGLWidget( _parent ), m_projectRunning(false), m_gridSize(10),
  m_massSpringObj(MassSpringObject(m_gridSize)), m_textured(true), m_timer(Timer()), m_dt(0.01f), m_frameRateTime(0.0f),
  m_frameRate(0), initRun(true)
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

  //start the timer
  m_timer.timerStart();
}

NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
  m_vao->removeVAO();
  // remove the texture
  glDeleteTextures(1,&m_textureName);
}

// This virtual function is called once before the first call to paintGL() or resizeGL(),
// and then once whenever the widget has been assigned a new QGLContext.
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
  initShader(shader, "ColourVertex", "ColourFragment", "ColourShader");
  initShader(shader, "TextureVertex", "TextureFragment", "TextureShader");

  // pick a random texture
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1,8);
  int textureNum = dis(gen);
  ngl::Texture texture("textures/texture" + std::to_string(textureNum) + ".png");
  m_textureName=texture.setTextureGL();

  // set the solid texture
  ngl::Texture solidTexture("textures/ratGrid.png");
  m_solidTextureName=solidTexture.setTextureGL();

  buildVAO();
  ngl::VAOFactory::listCreators();
}

// This virtual function is called whenever the widget has been resized.
// The new size is passed in width and height.
void NGLScene::resizeGL( int _w, int _h )
{
  m_project=ngl::perspective( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

void NGLScene::buildVAOData()
{
  for (unsigned int i = 0; i < u_int(m_massSpringObj.getVertices().size()); ++i)
  {
    m_vaoData.push_back(m_massSpringObj.getVertices()[ulong(i)].x);
    m_vaoData.push_back(m_massSpringObj.getVertices()[ulong(i)].y);
    m_vaoData.push_back(m_massSpringObj.getVertices()[ulong(i)].z);
    m_vaoData.push_back(m_massSpringObj.getUVs()[ulong(i)].x);
    m_vaoData.push_back(m_massSpringObj.getUVs()[ulong(i)].y);
  }
}

void NGLScene::buildIndices()
{
  for (auto index : m_massSpringObj.getIndices())
  {
    m_indices.push_back(GLshort(index));
  }
}

void NGLScene::buildVAO()
{
  // build the particle grid VAO
  buildVAOData();

  // build the indicies
  buildIndices();

  // create a vao as a series of GL_TRIANGLES
  m_vao=ngl::VAOFactory::createVAO(ngl::simpleIndexVAO,GL_TRIANGLES);
  m_vao->bind();

  //set the vao data
  setVAOData();

 // now unbind
  m_vao->unbind();
}

void NGLScene::initShader(ngl::ShaderLib* _shader, std::string _vertexShaderName, std::string _fragmentShaderName, std::string _shaderName)
{
  std::string PWD = std::getenv("PWD");

  _shader->createShaderProgram(_shaderName);

  _shader->attachShader(_vertexShaderName,ngl::ShaderType::VERTEX);
  _shader->attachShader(_fragmentShaderName,ngl::ShaderType::FRAGMENT);

  _shader->loadShaderSource(_vertexShaderName, PWD + "/Masters_Project_Silk_Torch/shaders/" + _vertexShaderName + ".glsl");
  _shader->loadShaderSource(_fragmentShaderName, PWD + "/Masters_Project_Silk_Torch/shaders/" + _fragmentShaderName + ".glsl");

  _shader->compileShader(_vertexShaderName);
  _shader->compileShader(_fragmentShaderName);
  _shader->attachShaderToProgram(_shaderName,_vertexShaderName);
  _shader->attachShaderToProgram(_shaderName,_fragmentShaderName);


  _shader->linkProgramObject(_shaderName);
  (*_shader)[_shaderName]->use();
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

  //enable transparancy
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if(m_wireframe == true)
  {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  }

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  (*shader)["TextureShader"]->use();

  ngl::Mat4 MVP= m_project*m_view*m_mouseGlobalTX;
  shader->setUniform("MVP",MVP);

  // bind the active texture before drawing
  if (m_textured)
  {
    glBindTexture(GL_TEXTURE_2D, m_textureName);
  }
  else
  {
    glBindTexture(GL_TEXTURE_2D, m_solidTextureName);
  }

  //draw objects
  m_vao=ngl::VAOFactory::createVAO(ngl::simpleIndexVAO,GL_TRIANGLES);
  m_vao->bind();

  setVAOData();

  m_vao->draw();
  m_vao->unbind();
}

void NGLScene::toggleWireframe(bool _mode	 )
{
  Logging::logI("Wireframe " + Logging::boolToString(_mode));
	m_wireframe=_mode;
  update();
}

void NGLScene::toggleTextured(bool _mode)
{
  Logging::logI("Textured " + Logging::boolToString(_mode));
  m_textured=_mode;
  //recreate the vertex and colour data using the updated cloth
  m_vaoData.resize(0);
  buildVAOData();
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
  //stop the timer and get dt
  m_dt = float(m_timer.timerFinish());

  //restart the timer
  m_timer.timerStart();

  //if the inital run reset the dt
  if (initRun)
  {
    initRun = false;
    m_dt = 0.01f;
  }

  //Logging::logI("dt: " + std::to_string(m_dt));

  //update the cloth
  m_massSpringObj.update(m_dt);

  //recreate the vertex and colour data using the updated cloth
  m_vaoData.resize(0);
  buildVAOData();

  // Update and redraw
  update();

  //update the frame rate
  m_frameRateTime += m_dt;
  if (m_frameRateTime > 1.0f)
  {
    m_frameRateTime -= 1.0f;
    Logging::logI("FPS: " + std::to_string(m_frameRate));
    m_frameRate = 0;
  }
  m_frameRate++;
}

void NGLScene::setVAOData()
{
  //set the data for the vao
  m_vao->setData(ngl::SimpleIndexVAO::VertexData(m_vaoData.size() * sizeof(float),
                                                   m_vaoData[0],
                                                   uint(m_indices.size()),
                                                   &m_indices[0],
                                                   GL_UNSIGNED_SHORT));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(float) * 5,0);
    m_vao->setVertexAttributePointer(2,2,GL_FLOAT,sizeof(float) * 5,3);
    m_vao->setNumIndices(m_indices.size());
}

void NGLScene::drawLines(std::vector<glm::vec3> & _lineVertAndColour, std::vector<GLshort> & _lineIndices)
{
  m_vao=ngl::VAOFactory::createVAO(ngl::simpleIndexVAO,GL_LINES);

  m_vao->bind();
  m_vao->setData(ngl::SimpleIndexVAO::VertexData(_lineVertAndColour.size() * sizeof(float),
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
