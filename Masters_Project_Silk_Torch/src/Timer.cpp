#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::timerStart()
{
  //set time stamp
  lastTime = std::chrono::steady_clock::now();
}

double Timer::timerFinish()
{
  //set the current time
  std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

  //calculate the time taken
  std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime);

  //get the time taken
  double timeTaken = duration.count();

  //convert into seconds
  timeTaken = timeTaken * 100.0;

  //return the time taken
  return timeTaken;
}
