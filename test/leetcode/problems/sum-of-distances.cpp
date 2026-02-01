#include "leetcode/problems/sum-of-distances.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2615 {

class SumOfDistancesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SumOfDistancesSolution solution;
};

TEST_P(SumOfDistancesTest, Example1) {
  vector<int> nums = {1, 3, 1, 1, 2};
  vector<long long> expected = {5, 0, 3, 4, 0};
  EXPECT_EQ(expected, solution.distance(nums));
}

TEST_P(SumOfDistancesTest, Example2) {
  vector<int> nums = {0, 5, 3};
  vector<long long> expected = {0, 0, 0};
  EXPECT_EQ(expected, solution.distance(nums));
}

TEST_P(SumOfDistancesTest, SingleElement) {
  vector<int> nums = {42};
  vector<long long> expected = {0};
  EXPECT_EQ(expected, solution.distance(nums));
}

TEST_P(SumOfDistancesTest, AllSameElements) {
  vector<int> nums = {5, 5, 5, 5};
  // index 0: |0-1|+|0-2|+|0-3| = 1+2+3 = 6
  // index 1: |1-0|+|1-2|+|1-3| = 1+1+2 = 4
  // index 2: |2-0|+|2-1|+|2-3| = 2+1+1 = 4
  // index 3: |3-0|+|3-1|+|3-2| = 3+2+1 = 6
  vector<long long> expected = {6, 4, 4, 6};
  EXPECT_EQ(expected, solution.distance(nums));
}

TEST_P(SumOfDistancesTest, TwoPairs) {
  vector<int> nums = {1, 2, 1, 2};
  // index 0 (value 1): |0-2| = 2
  // index 1 (value 2): |1-3| = 2
  // index 2 (value 1): |2-0| = 2
  // index 3 (value 2): |3-1| = 2
  vector<long long> expected = {2, 2, 2, 2};
  EXPECT_EQ(expected, solution.distance(nums));
}

TEST_P(SumOfDistancesTest, LargeNumbers) {
  vector<int> nums = {1000000000, 1000000000, 1000000000};
  // index 0: |0-1|+|0-2| = 1+2 = 3
  // index 1: |1-0|+|1-2| = 1+1 = 2
  // index 2: |2-0|+|2-1| = 2+1 = 3
  vector<long long> expected = {3, 2, 3};
  EXPECT_EQ(expected, solution.distance(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SumOfDistancesTest,
    ::testing::ValuesIn(SumOfDistancesSolution().getStrategyNames()));

}  // namespace problem_2615
}  // namespace leetcode
