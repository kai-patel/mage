#include <gtest/gtest.h>

TEST(Hello, TestOne) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}
