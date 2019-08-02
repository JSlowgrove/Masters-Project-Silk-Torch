#ifndef UTILITIES_H_
#define UTILITIES_H_

/// @file Utilities.h
/// @brief A namespace that contains utilities functions for use within the code.
/// @author Jamie Slowgrove
/// @version 1.0
/// @date 19/03/19
/// Revision History:
/// Initial Version 19/03/19.
namespace Utilities
{
  /**
  @brief Normalises the float bewteen the min and max number.
  @param[in] _mnum The number to be normalised.
  @param[in] _max The maxiumum value of the float.
  @param[in] _max The minimum value of the float.
  @returns The normalised float (between 0 and 1).
  */
  float normaliseFloat(float _num, float _max, float _min);
}

#endif // UTILITIES_H_
