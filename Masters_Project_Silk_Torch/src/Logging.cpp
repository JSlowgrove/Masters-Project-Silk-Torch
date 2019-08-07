#include "Logging.h"

#include <iostream>
#include <fstream>

namespace Logging
{
  void logI(std::string _message)
	{
    logI(_message, false);
	}

  void logE(std::string _message)
	{
    logE(_message, false);
	}

  void logGLMVec3(glm::vec3 _glmVec3)
	{
    logGLMVec3(_glmVec3, false);
	}

  void logI(std::string _message, bool _printToLog)
  {
    std::cout << "INFO: " << _message << '\n';
    if (_printToLog)
    {
      printToLogFile("INFO: " + _message);
    }
	}

  void logE(std::string _message, bool _printToLog)
	{
    std::cout << "ERROR: " << _message << '\n';
    if (_printToLog)
		{
      printToLogFile("ERROR: " + _message);
		}
  }

  void logGLMVec3(glm::vec3 _glmVec3, bool _printToLog)
	{
    std::string message = "GLM::VEC3: " + std::to_string(_glmVec3.x) + ", " + std::to_string(_glmVec3.y) + ", " + std::to_string(_glmVec3.z);
    std::cout << message << '\n';
    if (_printToLog)
		{
      printToLogFile(message);
		}
	}

  void printToLogFile(std::string _message)
	{
		//Open the file to have text appended to it
		std::ofstream file;
		file.open("log.txt", std::ios_base::app);

		if (file.is_open())
		{
			//Write the message to the file with a new line
      file << _message;
			file << "\n";

			//Close the file
			file.close();
		}
		else
		{
      logE("Unable to open log file", false);
		}
	}

  std::string boolToString(bool _booleanIn)
	{
    return _booleanIn ? "True" : "False";
  }

  void logGLMVec3(std::string _message, glm::vec3 _glmVec3, bool _printToLog)
  {
    std::string outMessage = _message + "GLM::VEC3: " + std::to_string(_glmVec3.x) + ", " + std::to_string(_glmVec3.y) + ", " + std::to_string(_glmVec3.z);
    std::cout << outMessage << '\n';
    if (_printToLog)
    {
      printToLogFile(outMessage);
    }
  }

}
