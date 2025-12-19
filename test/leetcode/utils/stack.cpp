#include "leetcode/utils/stack.h"

#include "gtest/gtest.h"

namespace leetcode {
TEST(LeetCodeUtils, StackPushAndPop) {
  MyStack stack;
  stack.push(1);
  stack.push(2);
  EXPECT_EQ(2, stack.pop());
  EXPECT_FALSE(stack.empty());
  EXPECT_EQ(1, stack.pop());
  EXPECT_TRUE(stack.empty());
}

TEST(LeetCodeUtils, StackCase1) {
  MyStack stack;
  stack.push(1);
  stack.push(2);
  EXPECT_EQ(2, stack.top());
  EXPECT_EQ(2, stack.pop());
  EXPECT_EQ(1, stack.pop());
  EXPECT_TRUE(stack.empty());
}
}  // namespace leetcode