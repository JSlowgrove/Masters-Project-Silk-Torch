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
  m_textured(true), m_timer(Timer()), m_dt(0.01f), m_frameRateTime(0.0f), m_frameRate(0), m_FPS(0), initRun(true)
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

  //generate the MassSpringObjects
  generateMassSpringObjects(1);

  //set the number of milliseconds the frame timer should run at
  m_timerMilliseconds = 1;

  //start the dt timer
  m_timer.timerStart();
}

NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
  m_vao->removeVAO();
  // remove the texture
  for (int i = 0; i < 9; i++)
  {
    glDeleteTextures(1,&m_textureName[i]);
  }
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
  initShader(shader, "TextureVertex", "TextureFragment", "TextureShader");

  // load the flame textures
  for (int i = 1; i <= 8; i++)
  {
    ngl::Texture texture("textures/texture" + std::to_string(i) + ".png");
    m_textureName[i]=texture.setTextureGL();
  }

  // set the solid texture
  ngl::Texture texture("textures/ratGrid.png");
  m_textureName[8]=texture.setTextureGL();

  buildVAO();
  ngl::VAOFactory::listCreators();

  // initalise the frame rate text
  m_frameRateText.reset(new  ngl::Text(QFont("Arial",18)));
  m_frameRateText->setScreenSize(this->size().width(),this->size().height());
  m_frameRateText->setColour(1.0,1.0,0.0);
}

// This virtual function is called whenever the widget has been resized.
// The new size is passed in width and height.
void NGLScene::resizeGL( int _w, int _h )
{
  m_project=ngl::perspective( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

void NGLScene::buildVAO()
{
  // build the particle grid VAO
  for (unsigned int i = 0; i < m_massSpringObjects.size(); ++i)
  {
    m_massSpringObjects[i]->buildVAOData();

    // create a vao as a series of GL_TRIANGLES
    m_vao=ngl::VAOFactory::createVAO(ngl::simpleIndexVAO,GL_TRIANGLES);
    m_vao->bind();

    // set the vao data
    setVAOData(i);

    // now unbind
    m_vao->unbind();
  }
}

void NGLScene::generateMassSpringObjects(int _numOfObjects)
{
  //the number of mass spring objects.
  //has to be a perfect square
  //e.g 1,4,9,16,25,36,49,64,81,100,121,144...
  m_numMassSpringObjects = (_numOfObjects + 1) * (_numOfObjects + 1);
  //calculate the square root of the number of mass spring objects
  float sqrtNum = std::sqrt(float(m_numMassSpringObjects));
  //calculate the scale of the massSpringObjects
  m_MSOScale = 1.0f/sqrtNum;

  //generate the mass spring objects
  for (int i = 0; i < m_numMassSpringObjects; i++)
  {
    //initalise the initial mass spring object
    m_massSpringObjects.push_back(std::shared_ptr<MassSpringObject>(new MassSpringObject(m_gridSize)));
    m_massSpringObjects.back()->setScale(glm::vec3(m_MSOScale, m_MSOScale, m_MSOScale));

    // pick a random texture
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,7);
    int textureNum = dis(gen);
    m_massSpringObjects.back()->setTextureNum(textureNum);
  }

  if (m_numMassSpringObjects > 1)
  {
    //move the mass spring objects
    unsigned long i = 0;
    float gapWidth = (m_gridSize-1.0f) * m_MSOScale;
    float coordTranslation = gapWidth * (sqrtNum * 0.5f) - (gapWidth*0.5f);
    for (float y = 0; y < sqrtNum; y++)
    {
      float currentY = gapWidth * y;
      for (float x = 0; x < sqrtNum; x++)
      {
        float currentX = gapWidth * x;
        m_massSpringObjects[i]->setPos(glm::vec3(currentX - coordTranslation,currentY - coordTranslation,0.0f));
        i++;
      }
    }
  }
}

void NGLScene::initShader(ngl::ShaderLib* _shader, std::string _vertexShaderName, std::string _fragmentShaderName, std::string _shaderName)
{
  //std::string PWD = std::getenv("PWD");

  _shader->createShaderProgram(_shaderName);

  _shader->attachShader(_vertexShaderName,ngl::ShaderType::VERTEX);
  _shader->attachShader(_fragmentShaderName,ngl::ShaderType::FRAGMENT);

  _shader->loadShaderSource(_vertexShaderName, "shaders/" + _vertexShaderName + ".glsl");
  _shader->loadShaderSource(_fragmentShaderName, "shaders/" + _fragmentShaderName + ".glsl");

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

  //draw objects

  //mass spring
  for (unsigned int i = 0; i < m_massSpringObjects.size(); ++i)
  {
    // bind the active texture before drawing
    if (m_textured)
    {
      glBindTexture(GL_TEXTURE_2D, m_textureName[m_massSpringObjects[i]->getTextureNum()]);
    }
    else
    {
      glBindTexture(GL_TEXTURE_2D, m_textureName[8]);
    }

    m_vao=ngl::VAOFactory::createVAO(ngl::simpleIndexVAO,GL_TRIANGLES);
    m_vao->bind();

    setVAOData(i);

    ngl::Mat4 transform = m_massSpringObjects[i]->getTransform();
    shader->setUniform("transform",transform);

    m_vao->draw();
    m_vao->unbind();
  }

  //draw text
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  m_frameRateText->renderText(10,10,"FPS: " + QString::number(m_FPS));
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
  //recreate the vao data
  for (auto springObjects : m_massSpringObjects)
  {
    springObjects->reBuildVAOData();
  }
  update();
}

void NGLScene::runProject()
{
  if (!m_projectRunning)
  {
    Logging::logI("Start Project");
    startTimer(m_timerMilliseconds);
    m_projectRunning = true;
    update();
  }
  else
  {
    Logging::logI("Project already running!");
  }
}

void NGLScene::restartProject()
{
  Logging::logI("Restart Project");
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->reset();
  }
  update();
}

void NGLScene::setBuoyancy(double _buoyancy)
{
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->setBoyancy(float(_buoyancy));
  }
  update();
}

void NGLScene::setWindImpulseOn(double _windImpulseOn)
{
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->setImpulseOnTime(float(_windImpulseOn));
  }
  update();
}

void NGLScene::setWindImpulseOff(double _windImpulseOff)
{
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->setImpulseOffTime(float(_windImpulseOff));
  }
  update();
}

void NGLScene::setWindForceX(double _x)
{
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->setWindForce('x',float(_x));
  }
  update();
}

void NGLScene::setWindForceY(double _y)
{
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->setWindForce('y',float(_y));
  }
  update();
}

void NGLScene::setWindForceZ(double _z)
{
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->setWindForce('z',float(_z));
  }
  update();
}

void NGLScene::setMass(double _mass)
{
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->setMass(float(_mass));
  }
}

void NGLScene::setSpringConstant(double _springConstant)
{
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->setSpringConstant(float(_springConstant));
  }
}

void NGLScene::setDamping(double _damping)
{
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->setDamping(float(_damping));
  }
}

void NGLScene::setRestLength(double _restLength)
{
  for(auto massSpringObj : m_massSpringObjects)
  {
    massSpringObj->setRestLength(float(_restLength));
  }
}

void NGLScene::setNumOfObject(int _numOfObjects)
{
  //empty the MassSpringObjects vector
  m_massSpringObjects.resize(0);

  //generate the MassSpringObjects
  generateMassSpringObjects(_numOfObjects);

  //recreate the vao data
  for (auto springObjects : m_massSpringObjects)
  {
    //update the mass spring point
    springObjects->update(m_dt);
    springObjects->reBuildVAOData();
  }
  update();
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

  //mass spring
  for (auto springObjects : m_massSpringObjects)
  {
    //update the mass spring point
    springObjects->update(m_dt);

    //recreate the vao data
    springObjects->reBuildVAOData();
  }

  // Update and redraw
  update();

  //update the frame rate
  m_frameRateTime += m_dt;
  if (m_frameRateTime > 1.0f)
  {
    m_frameRateTime -= 1.0f;
    m_FPS = m_frameRate;
    m_frameRate = 0;
  }
  m_frameRate++;
}

void NGLScene::setVAOData(unsigned int _massSpringIndex)
{
  //set the data for the vao
  m_vao->setData(ngl::SimpleIndexVAO::VertexData(m_massSpringObjects[_massSpringIndex]->getVAOData().size() * sizeof(float),
                                                   m_massSpringObjects[_massSpringIndex]->getVAOData()[0],
                                                   uint(m_massSpringObjects[_massSpringIndex]->getIndices().size()),
                                                   &m_massSpringObjects[_massSpringIndex]->getIndices()[0],
                                                   GL_UNSIGNED_SHORT));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(float) * 5,0);
    m_vao->setVertexAttributePointer(2,2,GL_FLOAT,sizeof(float) * 5,3);
    m_vao->setNumIndices(m_massSpringObjects[_massSpringIndex]->getIndices().size());
}
