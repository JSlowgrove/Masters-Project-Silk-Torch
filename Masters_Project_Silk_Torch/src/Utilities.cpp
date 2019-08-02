#include "Utilities.h"

namespace Utilities
{
  float normaliseFloat(float _num, float _max, float _min)
  {
    return (_num - _min) / (_max - _min);
  }
}
