
#include "leetcode/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2058 {

class FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsSolution solution;
};

// Example 1: [3,1] -> 无临界点
TEST_P(FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsTest, Example1) {
  ListNode* head = constructLinkedList({3, 1});
  vector<int> expected = {-1, -1};
  vector<int> result = solution.nodesBetweenCriticalPoints(head);
  EXPECT_EQ(expected, result);
}

// Example 2: [5,3,1,2,5,1,2] -> 临界点在第3,5,6位，输出 [1,3]
TEST_P(FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsTest, Example2) {
  ListNode* head = constructLinkedList({5, 3, 1, 2, 5, 1, 2});
  vector<int> expected = {1, 3};
  vector<int> result = solution.nodesBetweenCriticalPoints(head);
  EXPECT_EQ(expected, result);
}

// Example 3: [1,3,2,2,3,2,2,2,7] -> 临界点在第2,5位，输出 [3,3]
TEST_P(FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsTest, Example3) {
  ListNode* head = constructLinkedList({1, 3, 2, 2, 3, 2, 2, 2, 7});
  vector<int> expected = {3, 3};
  vector<int> result = solution.nodesBetweenCriticalPoints(head);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, 
    FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsTest,
    ::testing::ValuesIn(FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsSolution().getStrategyNames()));

}  // namespace problem_2058
}  // namespace leetcode
