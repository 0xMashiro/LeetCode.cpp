
#include "leetcode/problems/how-many-numbers-are-smaller-than-the-current-number.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1365 {

class HowManyNumbersAreSmallerThanTheCurrentNumberTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  HowManyNumbersAreSmallerThanTheCurrentNumberSolution solution;
};

TEST_P(HowManyNumbersAreSmallerThanTheCurrentNumberTest, Example1) {
  vector<int> nums = {8, 1, 2, 2, 3};
  vector<int> expected = {4, 0, 1, 1, 3};
  EXPECT_EQ(expected, solution.smallerNumbersThanCurrent(nums));
}

TEST_P(HowManyNumbersAreSmallerThanTheCurrentNumberTest, Example2) {
  vector<int> nums = {6, 5, 4, 8};
  vector<int> expected = {2, 1, 0, 3};
  EXPECT_EQ(expected, solution.smallerNumbersThanCurrent(nums));
}

TEST_P(HowManyNumbersAreSmallerThanTheCurrentNumberTest, Example3) {
  vector<int> nums = {7, 7, 7, 7};
  vector<int> expected = {0, 0, 0, 0};
  EXPECT_EQ(expected, solution.smallerNumbersThanCurrent(nums));
}

TEST_P(HowManyNumbersAreSmallerThanTheCurrentNumberTest, AllSameElements) {
  vector<int> nums = {5, 5, 5, 5, 5};
  vector<int> expected = {0, 0, 0, 0, 0};
  EXPECT_EQ(expected, solution.smallerNumbersThanCurrent(nums));
}

TEST_P(HowManyNumbersAreSmallerThanTheCurrentNumberTest, StrictlyIncreasing) {
  vector<int> nums = {0, 1, 2, 3, 4};
  vector<int> expected = {0, 1, 2, 3, 4};
  EXPECT_EQ(expected, solution.smallerNumbersThanCurrent(nums));
}

TEST_P(HowManyNumbersAreSmallerThanTheCurrentNumberTest, StrictlyDecreasing) {
  vector<int> nums = {4, 3, 2, 1, 0};
  vector<int> expected = {4, 3, 2, 1, 0};
  EXPECT_EQ(expected, solution.smallerNumbersThanCurrent(nums));
}

TEST_P(HowManyNumbersAreSmallerThanTheCurrentNumberTest, MinLength) {
  vector<int> nums = {0, 100};
  vector<int> expected = {0, 1};
  EXPECT_EQ(expected, solution.smallerNumbersThanCurrent(nums));
}

TEST_P(HowManyNumbersAreSmallerThanTheCurrentNumberTest, ContainsZero) {
  vector<int> nums = {0, 0, 0, 1};
  vector<int> expected = {0, 0, 0, 3};
  EXPECT_EQ(expected, solution.smallerNumbersThanCurrent(nums));
}

TEST_P(HowManyNumbersAreSmallerThanTheCurrentNumberTest, TwoElementsEqual) {
  vector<int> nums = {1, 1};
  vector<int> expected = {0, 0};
  EXPECT_EQ(expected, solution.smallerNumbersThanCurrent(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, HowManyNumbersAreSmallerThanTheCurrentNumberTest,
    ::testing::ValuesIn(HowManyNumbersAreSmallerThanTheCurrentNumberSolution().getStrategyNames()));

}  // namespace problem_1365
}  // namespace leetcode
