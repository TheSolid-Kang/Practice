#include "pch.h"
#include "gtest/gtest.h"

int test() { std::cout << "test"; return 1; }
TEST(TestCaseName, TestName) {
  EXPECT_EQ(test(), 1);
  EXPECT_TRUE(true);
  system("cls");
}
