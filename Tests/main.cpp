#include <gtest/gtest.h>

#include "Logging.h"
#include "Utilities.h"

int main(int argc, char **argv)
{
  // Initalise google test library
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/*CUSTOM TEST FUNCTIONS*************************************************************/
void EXPECT_EQ_GLM_VEC3(glm::vec3 _actualVec3, glm::vec3 _expectedVec3)
{
  EXPECT_FLOAT_EQ(_actualVec3.x, _expectedVec3.x);
  EXPECT_FLOAT_EQ(_actualVec3.y, _expectedVec3.y);
  EXPECT_FLOAT_EQ(_actualVec3.z, _expectedVec3.z);
}

void EXPECT_EQ_GLM_VEC2(glm::vec2 _actualVec2, glm::vec2 _expectedVec2)
{
  EXPECT_FLOAT_EQ(_actualVec2.x, _expectedVec2.x);
  EXPECT_FLOAT_EQ(_actualVec2.y, _expectedVec2.y);
}

/*CUSTOM DEFS FUNCTIONS*************************************************************/
TEST(CustomDefs,NormaliseFloat)
{
  float max = 10;
  float min = 0;
  float num = 5;

  EXPECT_FLOAT_EQ(Utilities::normaliseFloat(num,max,min), 0.5f);
}
