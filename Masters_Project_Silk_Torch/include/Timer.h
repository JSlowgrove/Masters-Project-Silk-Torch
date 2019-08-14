#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>

/// @file Timer.h
/// @brief Contains details and functions for use with testing performance.
/// @author Jamie Slowgrove
/// @version 1.0
/// @date 14/08/19
/// Revision History:
/// Initial Version 14/08/19.
class Timer
{
public:
	/**
  @brief Constructs the Timer object.
	*/
  Timer();

	/**
  @brief Destructs the Timer object.
	*/
  ~Timer();

	/**
  @brief A function to start the timer. This is to be called when the timer is to be started.
	*/
  void timerStart();

	/**
  @brief A function to get the results of the timer.
  @returns The time taken in seconds.
	*/
  double timerFinish();

private:
  /// The last time stamp.
  std::chrono::steady_clock::time_point lastTime;
};

#endif //TIMER_H_
