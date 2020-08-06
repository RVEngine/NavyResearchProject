#include <gtest/gtest.h>
#include "Quantico_GetDataUnitTest.h"

/*
* GEARS NOTES:
* This file contains an example of using the Google C++ Testing Framework (Google Test).
* Below you will find a sample Test Fixture class and a sample Test Case function.
*
* The Text Fixture class can be used when multiple tests need to operate on similar data.
* Use the Text Fixture to initialize and clean up any data needed by the Test Cases.
*
* The Test Case function is a simple example of how to check for an expected value.
* This Test Case should be replaced with Test Cases relevant to your source code.
*
* Also feel free to add additional cpp files to the Unit Test project that define
* more Test Fixtures and Test Cases. Google Test will find them and run them.
*
* See the Google Test Documentation for more information:
* https://github.com/google/googletest/blob/master/googletest/docs/V1_6_Documentation.md
*
* REMINDER:
* The Unit Test project can utilize any functions or types defined in the static library.
*/

namespace gears
{
namespace test
{
class Quantico_GetDataTestFixture : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
    //GEARS NOTE: Use the SetUp function to prepare the data needed for each test.
  }

  virtual void TearDown()
  {
    //GEARS NOTE: Use the TearDown function to clean up any resources allocated
    //by the SetUp function.
  }
};

TEST_F(Quantico_GetDataTestFixture, PassTest)
{
  //Test things...
  int test_value = 0;

  //Confirm tested things...
  EXPECT_EQ(0, test_value); //This is going to pass.
}

}; // end test
}; // end gears
