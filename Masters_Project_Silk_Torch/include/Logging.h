#ifndef LOGGING_H_
#define LOGGING_H_

#include <string>
#include "glm/glm.hpp"

/// @file Logging.h
/// @brief A namespace that contains logging functions for use within the code.
/// @author Jamie Slowgrove
/// @version 2.0
/// @date 24/01/19
/// Revision History:
/// Initial Version 24/01/19.
/// Modified Verison 29/01/19 for continuation of code after ASE assignment.
/// Extracted Verison 19/03/19 from ASE assignment to use as template NGL project.
/// Modified Version 03/08/19 for the Master's Project.
namespace Logging
{
	/**
  @brief Logs the information message, this does not print the message to the log file by default.
  @param[in] _message The message.
	*/
  void logI(std::string _message);

	/**
  @brief Logs the error message, this does not print the message to the log file by default.
  @param[in] _message The message.
	*/
  void logE(std::string _message);

	/**
  @brief Logs the glm::vec3, this does not printt the glm::vec3 to the log file by default.
  @param[in] _glmVec3 The glm::vec3 to log.
	*/
  void logGLMVec3(glm::vec3 _glmVec3);

	/**
	@brief Logs the information message.
  @param[in] _message The message.
  @param[in] _printToLog A boolean for whether to print to the log.
	*/
  void logI(std::string _message, bool _printToLog);

	/**
	@brief Logs the error message.
  @param[in] _message The message.
  @param[in] _printToLog A boolean for whether to print to the log.
	*/
  void logE(std::string _message, bool _printToLog);

	/**
  @brief Logs the glm::vec3.
  @param[in] _glmVec3 The glm::vec3 to log.
  @param[in] _printToLog A boolean for whether to print to the log.
	*/
  void logGLMVec3(glm::vec3 _glmVec3, bool _printToLog);

  /**
  @brief Logs a message and a glm::vec3.
  @param[in] _message The message.
  @param[in] _glmVec3 The glm::vec3 to log.
  @param[in] _printToLog A boolean for whether to print to the log.
  */
  void logGLMVec3(std::string _message, glm::vec3 _glmVec3, bool _printToLog);

	/**
	@brief Prints the message out into the log file.
  @param[in] _message The message.
	*/
  void printToLogFile(std::string _message);

	/**
	@brief Converts a boolean to a string.
  @param[in] _booleanIn The boolean to be converted.
	@returns The boolean as a string.
	*/
  std::string boolToString(bool _booleanIn);
}

#endif // LOGGING_H_
