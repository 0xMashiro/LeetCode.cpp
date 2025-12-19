#include "leetcode/utils/queue.h"

#include "gtest/gtest.h"

namespace leetcode {
TEST(LeetCodeUtils, QueuePushAndPop) {
  MyQueue queue;
  queue.push(1);
  queue.push(2);
  EXPECT_EQ(1, queue.pop());
  EXPECT_EQ(2, queue.pop());
  EXPECT_TRUE(queue.empty());
}

TEST(LeetCodeUtils, QueuePushAndPeek) {
  MyQueue queue;
  queue.push(1);
  queue.push(2);
  EXPECT_EQ(1, queue.peek());
  EXPECT_EQ(1, queue.peek());
}

TEST(LeetCodeUtils, QueueCase1) {
  MyQueue queue;
  queue.push(1);
  queue.push(2);
  EXPECT_FALSE(queue.empty());
  EXPECT_EQ(1, queue.peek());
  queue.pop();
  EXPECT_FALSE(queue.empty());
}
}  // namespace leetcode