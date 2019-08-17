#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_gl=new  NGLScene(this);

  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,5,1);
  connect(m_ui->m_wireframe,SIGNAL(toggled(bool)),m_gl,SLOT(toggleWireframe(bool)));
  connect(m_ui->m_textured,SIGNAL(toggled(bool)),m_gl,SLOT(toggleTextured(bool)));
  connect(m_ui->m_runProject,SIGNAL(clicked()),m_gl,SLOT(runProject()));
  connect(m_ui->m_restartProject,SIGNAL(clicked()),m_gl,SLOT(restartProject()));
  //set external forces
  connect(m_ui->m_buoyancy,SIGNAL(valueChanged(double)),m_gl,SLOT(setBuoyancy(double)));
  connect(m_ui->m_windImpulseOn,SIGNAL(valueChanged(double)),m_gl,SLOT(setWindImpulseOn(double)));
  connect(m_ui->m_windImpulseOff,SIGNAL(valueChanged(double)),m_gl,SLOT(setWindImpulseOff(double)));
  connect(m_ui->m_windForceX,SIGNAL(valueChanged(double)),m_gl,SLOT(setWindForceX(double)));
  connect(m_ui->m_windForceY,SIGNAL(valueChanged(double)),m_gl,SLOT(setWindForceY(double)));
  connect(m_ui->m_windForceZ,SIGNAL(valueChanged(double)),m_gl,SLOT(setWindForceZ(double)));
  //set internal forces
  connect(m_ui->m_mass,SIGNAL(valueChanged(double)),m_gl,SLOT(setMass(double)));
  connect(m_ui->m_springConstant,SIGNAL(valueChanged(double)),m_gl,SLOT(setSpringConstant(double)));
  connect(m_ui->m_damping,SIGNAL(valueChanged(double)),m_gl,SLOT(setDamping(double)));
  connect(m_ui->m_restLength,SIGNAL(valueChanged(double)),m_gl,SLOT(setRestLength(double)));
}

MainWindow::~MainWindow()
{
  delete m_ui;
}
