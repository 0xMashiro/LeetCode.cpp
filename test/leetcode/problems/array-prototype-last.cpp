#include "leetcode/problems/array-prototype-last.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2619 {

class ArrayPrototypeLastTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ArrayPrototypeLastSolution solution;
};

TEST_P(ArrayPrototypeLastTest, Example1) {
  // Input: nums = [null, {}, 3] (模拟为 [0, 0, 3])
  // Output: 3
  vector<int> nums = {0, 0, 3};
  EXPECT_EQ(3, solution.last(nums));
}

TEST_P(ArrayPrototypeLastTest, Example2) {
  // Input: nums = []
  // Output: -1
  vector<int> nums = {};
  EXPECT_EQ(-1, solution.last(nums));
}

TEST_P(ArrayPrototypeLastTest, EmptyArray) {
  vector<int> nums;
  EXPECT_EQ(-1, solution.last(nums));
}

TEST_P(ArrayPrototypeLastTest, SingleElement) {
  vector<int> nums = {42};
  EXPECT_EQ(42, solution.last(nums));
}

TEST_P(ArrayPrototypeLastTest, TwoElements) {
  vector<int> nums = {1, 2};
  EXPECT_EQ(2, solution.last(nums));
}

TEST_P(ArrayPrototypeLastTest, NegativeNumbers) {
  vector<int> nums = {-1, -2, -3};
  EXPECT_EQ(-3, solution.last(nums));
}

TEST_P(ArrayPrototypeLastTest, LargeNumbers) {
  vector<int> nums = {1000, 2000, 3000};
  EXPECT_EQ(3000, solution.last(nums));
}

TEST_P(ArrayPrototypeLastTest, Zero) {
  vector<int> nums = {0};
  EXPECT_EQ(0, solution.last(nums));
}

TEST_P(ArrayPrototypeLastTest, MaxSize) {
  // 测试最大约束 1000
  vector<int> nums(1000, 5);
  EXPECT_EQ(5, solution.last(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ArrayPrototypeLastTest,
    ::testing::ValuesIn(ArrayPrototypeLastSolution().getStrategyNames()));

}  // namespace problem_2619
}  // namespace leetcode
