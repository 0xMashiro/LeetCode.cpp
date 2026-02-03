#include "leetcode/problems/maximum-area-rectangle-with-point-constraints-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3380 {

class MaximumAreaRectangleWithPointConstraintsITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumAreaRectangleWithPointConstraintsISolution solution;
};

TEST_P(MaximumAreaRectangleWithPointConstraintsITest, Example1) {
  vector<vector<int>> points = {{1, 1}, {1, 3}, {3, 1}, {3, 3}};
  EXPECT_EQ(4, solution.maxRectangleArea(points));
}

TEST_P(MaximumAreaRectangleWithPointConstraintsITest, Example2) {
  vector<vector<int>> points = {{1, 1}, {1, 3}, {3, 1}, {3, 3}, {2, 2}};
  EXPECT_EQ(-1, solution.maxRectangleArea(points));
}

TEST_P(MaximumAreaRectangleWithPointConstraintsITest, Example3) {
  vector<vector<int>> points = {{1, 1}, {1, 3}, {3, 1}, {3, 3}, {1, 2}, {3, 2}};
  EXPECT_EQ(2, solution.maxRectangleArea(points));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumAreaRectangleWithPointConstraintsITest,
    ::testing::ValuesIn(MaximumAreaRectangleWithPointConstraintsISolution().getStrategyNames()));

}  // namespace problem_3380
}  // namespace leetcode