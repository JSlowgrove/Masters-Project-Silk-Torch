#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_gl=new  NGLScene(this);

  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,5,1);
  connect(m_ui->m_wireframe,SIGNAL(toggled(bool)),m_gl,SLOT(toggleWireframe(bool)));
  connect(m_ui->m_runProject,SIGNAL(clicked()),m_gl,SLOT(runProject()));
  connect(m_ui->m_restartProject,SIGNAL(clicked()),m_gl,SLOT(restartProject()));
}

MainWindow::~MainWindow()
{
  delete m_ui;
}
