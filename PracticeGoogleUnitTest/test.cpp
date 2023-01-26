#include "pch.h"
#include "gtest/gtest.h"

namespace test {
  int test() { std::cout << "test"; return 1; }
  namespace datastructure{
    TEST(TestCaseName, TestName) {
    EXPECT_EQ(test(), 1);
    EXPECT_TRUE(true);
    }
  }
}