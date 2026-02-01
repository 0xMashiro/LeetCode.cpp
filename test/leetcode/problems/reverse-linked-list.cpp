#include "leetcode/problems/reverse-linked-list.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_206 {

class ReverseLinkedListTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ReverseLinkedListSolution solution;
};

TEST_P(ReverseLinkedListTest, Example1) {
  // Input: head = [1,2,3,4,5], Output: [5,4,3,2,1]
  auto head = constructLinkedList({1, 2, 3, 4, 5});
  auto result = solution.reverseList(head);
  EXPECT_EQ(traverse(result), std::vector<int>({5, 4, 3, 2, 1}));
}

TEST_P(ReverseLinkedListTest, Example2) {
  // Input: head = [1,2], Output: [2,1]
  auto head = constructLinkedList({1, 2});
  auto result = solution.reverseList(head);
  EXPECT_EQ(traverse(result), std::vector<int>({2, 1}));
}

TEST_P(ReverseLinkedListTest, Example3) {
  // Input: head = [], Output: []
  auto head = constructLinkedList({});
  auto result = solution.reverseList(head);
  EXPECT_EQ(traverse(result), std::vector<int>({}));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ReverseLinkedListTest,
    ::testing::ValuesIn(ReverseLinkedListSolution().getStrategyNames()));

}  // namespace problem_206
}  // namespace leetcode
