#include "leetcode/problems/find-all-lonely-numbers-in-the-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2150 {

class FindAllLonelyNumbersInTheArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindAllLonelyNumbersInTheArraySolution solution;
};

TEST_P(FindAllLonelyNumbersInTheArrayTest, Example1) {
  vector<int> nums = {10, 6, 5, 8};
  vector<int> expected = {10, 8};
  vector<int> result = solution.findLonely(nums);
  // 由于顺序不限，排序后比较
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(FindAllLonelyNumbersInTheArrayTest, Example2) {
  vector<int> nums = {1, 3, 5, 3};
  vector<int> expected = {1, 5};
  vector<int> result = solution.findLonely(nums);
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindAllLonelyNumbersInTheArrayTest,
    ::testing::ValuesIn(FindAllLonelyNumbersInTheArraySolution().getStrategyNames()));

}  // namespace problem_2150
}  // namespace leetcode
