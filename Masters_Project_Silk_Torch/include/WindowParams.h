#ifndef WINDOWPARAMS_H_
#define WINDOWPARAMS_H_

/// @file NGLScene.h
/// @brief Contains the variables for use with the Window.
/// @author Jonathan Macey (Modified by Jamie Slowgrove)
/// @version 3.0
/// @date 24/01/19
/// Revision History:
/// Initial Version 10/10/10 (Binary day ;-0 )
/// Modified Verison 24/01/19 for use with ASE assignment.
/// Modified Verison 29/01/19 for continuation of code after ASE assignment.
/// Extracted Verison 19/03/19 from ASE assignment to use as template NGL project.
/// Modified Version 03/08/19 for the Master's Project.

/**
  @brief A structure containing variables for use with the Window.
 */
struct WinParams
{
  ///Used to store the x rotation mouse value.
  int spinXFace = 0;
  ///Used to store the y rotation mouse value.
  int spinYFace = 0;
  ///Flag to indicate if the mouse button is pressed when dragging.
  bool rotate = false;
  ///Flag to indicate if the Right mouse button is pressed when dragging.
  bool translate = false;
  ///The previous x mouse value.
  int origX = 0;
  ///The previous y mouse value.
  int origY = 0;
  ///The previous x mouse value for Position changes.
  int origXPos = 0;
  ///The previous y mouse value for Position changes.
  int origYPos = 0;
  ///The window width.
  int width = 1024;
  ///The window height.
  int height = 720;
};

///The increment for x/y translation with mouse movement.
constexpr float INCREMENT = 0.01f;
///The increment for the wheel zoom.
constexpr float ZOOM = 0.1f;

#endif //WINDOWPARAMS_H_
