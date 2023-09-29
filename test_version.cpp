//#define BOOST_TEST_MODULE test_version

#include "lib.h"

#include <gtest/gtest.h>

//#include <boost/test/unit_test.hpp>

/*BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_SUITE_END()
*/

TEST(test, ver)
{
// Arrange
    //int v = version();

// Act (empty for this test)

// Assert
    ASSERT_GT(version(), 0);
    //ASSERT_TRUE(v==0);
}