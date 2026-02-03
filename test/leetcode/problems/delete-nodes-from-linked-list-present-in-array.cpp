
#include "leetcode/problems/delete-nodes-from-linked-list-present-in-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3217 {

class DeleteNodesFromLinkedListPresentInArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DeleteNodesFromLinkedListPresentInArraySolution solution;
};

TEST_P(DeleteNodesFromLinkedListPresentInArrayTest, Example1) {
  vector<int> nums = {1, 2, 3};
  ListNode* head = constructLinkedList({1, 2, 3, 4, 5});
  vector<int> expected = {4, 5};
  ListNode* result = solution.modifiedList(nums, head);
  EXPECT_EQ(expected, traverse(result));
}

TEST_P(DeleteNodesFromLinkedListPresentInArrayTest, Example2) {
  vector<int> nums = {1};
  ListNode* head = constructLinkedList({1, 2, 1, 2, 1, 2});
  vector<int> expected = {2, 2, 2};
  ListNode* result = solution.modifiedList(nums, head);
  EXPECT_EQ(expected, traverse(result));
}

TEST_P(DeleteNodesFromLinkedListPresentInArrayTest, Example3) {
  vector<int> nums = {5};
  ListNode* head = constructLinkedList({1, 2, 3, 4});
  vector<int> expected = {1, 2, 3, 4};
  ListNode* result = solution.modifiedList(nums, head);
  EXPECT_EQ(expected, traverse(result));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DeleteNodesFromLinkedListPresentInArrayTest,
    ::testing::ValuesIn(DeleteNodesFromLinkedListPresentInArraySolution().getStrategyNames()));

}  // namespace problem_3217
}  // namespace leetcode
