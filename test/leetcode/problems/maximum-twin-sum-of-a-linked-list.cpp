#include "leetcode/problems/maximum-twin-sum-of-a-linked-list.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2130 {

class MaximumTwinSumOfALinkedListTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumTwinSumOfALinkedListSolution solution;
};

TEST_P(MaximumTwinSumOfALinkedListTest, Example1) {
  ListNode* head = constructLinkedList({5, 4, 2, 1});
  EXPECT_EQ(solution.pairSum(head), 6);
}

TEST_P(MaximumTwinSumOfALinkedListTest, Example2) {
  ListNode* head = constructLinkedList({4, 2, 2, 3});
  EXPECT_EQ(solution.pairSum(head), 7);
}

TEST_P(MaximumTwinSumOfALinkedListTest, Example3) {
  ListNode* head = constructLinkedList({1, 100000});
  EXPECT_EQ(solution.pairSum(head), 100001);
}

TEST_P(MaximumTwinSumOfALinkedListTest, SelfAuthoredAllSameValues) {
  ListNode* head = constructLinkedList({7, 7, 7, 7});
  EXPECT_EQ(solution.pairSum(head), 14);
}

TEST_P(MaximumTwinSumOfALinkedListTest, SelfAuthoredIncreasingValues) {
  ListNode* head = constructLinkedList({1, 2, 3, 4, 5, 6});
  // pairs: (1,6)=7, (2,5)=7, (3,4)=7 -> max=7
  EXPECT_EQ(solution.pairSum(head), 7);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumTwinSumOfALinkedListTest,
    ::testing::ValuesIn(MaximumTwinSumOfALinkedListSolution().getStrategyNames()));

}  // namespace problem_2130
}  // namespace leetcode
