#include "leetcode/problems/sort-integers-by-the-number-of-1-bits.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1356 {

class SortIntegersByTheNumberOf1BitsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SortIntegersByTheNumberOf1BitsSolution solution;
};

TEST_P(SortIntegersByTheNumberOf1BitsTest, Example1) {
  vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> expected = {0, 1, 2, 4, 8, 3, 5, 6, 7};
  vector<int> result = solution.sortByBits(arr);
  EXPECT_EQ(expected, result);
}

TEST_P(SortIntegersByTheNumberOf1BitsTest, Example2) {
  vector<int> arr = {1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};
  vector<int> expected = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
  vector<int> result = solution.sortByBits(arr);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SortIntegersByTheNumberOf1BitsTest,
    ::testing::ValuesIn(SortIntegersByTheNumberOf1BitsSolution().getStrategyNames()));

}  // namespace problem_1356
}  // namespace leetcode
