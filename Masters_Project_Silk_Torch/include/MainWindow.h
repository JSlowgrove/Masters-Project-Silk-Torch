#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include "NGLScene.h"

/// @file MainWindow.h
/// @brief The class that contains the required functions and data for the QtWindow.
/// @author Jonathan Macey (Modified by Jamie Slowgrove)
/// @version 3.0
/// @date 24/01/19
/// Revision History:
/// Initial Version 10/10/10 (Binary day ;-0 )
/// Modified Verison 24/01/19 for use with ASE assignment.
/// Modified Verison 29/01/19 for continuation of code after ASE assignment.
/// Extracted Verison 19/03/19 from ASE assignment to use as template NGL project.

 /**
 @brief The namespace for the UI.
 */
namespace Ui
{
  ///A forward declaration of the MainWindow class.
  class MainWindow;
}

 /**
 @brief The main window class for the Qt program. This inherits QMainWindow.
 */
class MainWindow : public QMainWindow
{
  ///Required for Qt UI
  Q_OBJECT

public:
  /**
  @brief An explicit constructor of the MainWindow class.
  @param[in] parent A pointer to the parent QWidget.
  */
  explicit MainWindow(QWidget *parent = 0);

  /**
  @brief Destructs the MainWindow object.
  */
  ~MainWindow();

private:
  ///The pointer for the Qt UI.
  Ui::MainWindow *m_ui;
  ///The openGL widget.
  NGLScene *m_gl;
};

#endif // MAINWINDOW_H_
