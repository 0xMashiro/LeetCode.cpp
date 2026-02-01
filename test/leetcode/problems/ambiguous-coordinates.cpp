#include "leetcode/problems/ambiguous-coordinates.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_816 {

class AmbiguousCoordinatesTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  AmbiguousCoordinatesSolution solution;
};

TEST_P(AmbiguousCoordinatesTest, Example1) {
  string s = "(123)";
  vector<string> result = solution.ambiguousCoordinates(s);
  vector<string> expected = {"(1, 2.3)", "(1, 23)", "(1.2, 3)", "(12, 3)"};
  // 排序后比较，因为顺序可能不同
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(AmbiguousCoordinatesTest, Example2) {
  string s = "(0123)";
  vector<string> result = solution.ambiguousCoordinates(s);
  vector<string> expected = {"(0, 1.23)", "(0, 12.3)", "(0, 123)", "(0.1, 2.3)", "(0.1, 23)", "(0.12, 3)"};
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(AmbiguousCoordinatesTest, Example3) {
  string s = "(00011)";
  vector<string> result = solution.ambiguousCoordinates(s);
  vector<string> expected = {"(0, 0.011)", "(0.001, 1)"};
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, AmbiguousCoordinatesTest,
    ::testing::ValuesIn(AmbiguousCoordinatesSolution().getStrategyNames()));

}  // namespace problem_816
}  // namespace leetcode