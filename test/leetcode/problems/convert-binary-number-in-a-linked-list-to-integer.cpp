#include "leetcode/problems/convert-binary-number-in-a-linked-list-to-integer.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1290 {

class ConvertBinaryNumberInALinkedListToIntegerTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConvertBinaryNumberInALinkedListToIntegerSolution solution;
};

//! Example 1: head = [1,0,1] -> Output: 5 (101 in base 2 = 5 in base 10)
TEST_P(ConvertBinaryNumberInALinkedListToIntegerTest, Example1) {
  ListNode* head = constructLinkedList({1, 0, 1});
  EXPECT_EQ(5, solution.getDecimalValue(head));
  // Note: constructLinkedList allocates nodes, but we don't manually delete them
  // as per project guidelines (no manual delete for project data structures)
}

//! Example 2: head = [0] -> Output: 0
TEST_P(ConvertBinaryNumberInALinkedListToIntegerTest, Example2) {
  ListNode* head = constructLinkedList({0});
  EXPECT_EQ(0, solution.getDecimalValue(head));
}

//! Test case: Single node with value 1
TEST_P(ConvertBinaryNumberInALinkedListToIntegerTest, SingleNodeOne) {
  ListNode* head = constructLinkedList({1});
  EXPECT_EQ(1, solution.getDecimalValue(head));
}

//! Test case: All zeros [0,0,0] -> Output: 0
TEST_P(ConvertBinaryNumberInALinkedListToIntegerTest, AllZeros) {
  ListNode* head = constructLinkedList({0, 0, 0});
  EXPECT_EQ(0, solution.getDecimalValue(head));
}

//! Test case: All ones [1,1,1] -> Output: 7 (111 in base 2 = 7 in base 10)
TEST_P(ConvertBinaryNumberInALinkedListToIntegerTest, AllOnes) {
  ListNode* head = constructLinkedList({1, 1, 1});
  EXPECT_EQ(7, solution.getDecimalValue(head));
}

//! Test case: Maximum length (30 nodes) with alternating pattern
//! [1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0] 
//! = 0b101010101010101010101010101010 = 715827882
TEST_P(ConvertBinaryNumberInALinkedListToIntegerTest, MaxLengthAlternating) {
  std::vector<int> values(30);
  for (int i = 0; i < 30; ++i) {
    values[i] = (i % 2 == 0) ? 1 : 0;  // 1,0,1,0,...
  }
  ListNode* head = constructLinkedList(values);
  EXPECT_EQ(715827882, solution.getDecimalValue(head));
}

//! Test case: Maximum value [1,1,1,1,1,1,1,1,1,1] (10 ones) -> Output: 1023
TEST_P(ConvertBinaryNumberInALinkedListToIntegerTest, TenOnes) {
  ListNode* head = constructLinkedList({1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
  EXPECT_EQ(1023, solution.getDecimalValue(head));
}

//! Test case: Leading zeros [0,0,1,0,1] -> Output: 5 (00101 = 101 = 5)
TEST_P(ConvertBinaryNumberInALinkedListToIntegerTest, LeadingZeros) {
  ListNode* head = constructLinkedList({0, 0, 1, 0, 1});
  EXPECT_EQ(5, solution.getDecimalValue(head));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConvertBinaryNumberInALinkedListToIntegerTest,
    ::testing::ValuesIn(ConvertBinaryNumberInALinkedListToIntegerSolution().getStrategyNames()));

}  // namespace problem_1290
}  // namespace leetcode
