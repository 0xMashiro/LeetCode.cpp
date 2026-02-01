#include "leetcode/problems/find-closest-person.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3516 {

class FindClosestPersonTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindClosestPersonSolution solution;
};

// 示例 1：Person 1 更近
TEST_P(FindClosestPersonTest, Example1) {
  int x = 2, y = 7, z = 4;
  EXPECT_EQ(1, solution.findClosest(x, y, z));
}

// 示例 2：Person 2 更近
TEST_P(FindClosestPersonTest, Example2) {
  int x = 2, y = 5, z = 6;
  EXPECT_EQ(2, solution.findClosest(x, y, z));
}

// 示例 3：同时到达
TEST_P(FindClosestPersonTest, Example3) {
  int x = 1, y = 5, z = 3;
  EXPECT_EQ(0, solution.findClosest(x, y, z));
}

// 边界：x, y, z 相同
TEST_P(FindClosestPersonTest, AllSamePosition) {
  int x = 5, y = 5, z = 5;
  EXPECT_EQ(0, solution.findClosest(x, y, z));
}

// 边界：Person 1 在 Person 3 位置
TEST_P(FindClosestPersonTest, Person1AtPerson3) {
  int x = 3, y = 7, z = 3;
  EXPECT_EQ(1, solution.findClosest(x, y, z));
}

// 边界：Person 2 在 Person 3 位置
TEST_P(FindClosestPersonTest, Person2AtPerson3) {
  int x = 1, y = 5, z = 5;
  EXPECT_EQ(2, solution.findClosest(x, y, z));
}

// 边界：Person 1 和 Person 2 在同一位置（距离 Person 3 不同）
TEST_P(FindClosestPersonTest, Person1And2SamePosition) {
  int x = 2, y = 2, z = 5;
  EXPECT_EQ(0, solution.findClosest(x, y, z));
}

// 边界：最大值测试
TEST_P(FindClosestPersonTest, MaxValues) {
  int x = 100, y = 1, z = 50;
  EXPECT_EQ(2, solution.findClosest(x, y, z));  // |100-50|=50 > |1-50|=49
}

// 边界：最小值测试
TEST_P(FindClosestPersonTest, MinValues) {
  int x = 1, y = 100, z = 50;
  EXPECT_EQ(1, solution.findClosest(x, y, z));  // |1-50|=49 < |100-50|=50
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindClosestPersonTest,
    ::testing::ValuesIn(FindClosestPersonSolution().getStrategyNames()));

}  // namespace problem_3516
}  // namespace leetcode
