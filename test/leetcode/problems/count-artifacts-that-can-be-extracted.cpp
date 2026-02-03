#include "leetcode/problems/count-artifacts-that-can-be-extracted.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2201 {

class CountArtifactsThatCanBeExtractedTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountArtifactsThatCanBeExtractedSolution solution;
};

TEST_P(CountArtifactsThatCanBeExtractedTest, Example1) {
  int n = 2;
  vector<vector<int>> artifacts = {{0, 0, 0, 0}, {0, 1, 1, 1}};
  vector<vector<int>> dig = {{0, 0}, {0, 1}};
  int expected = 1;
  EXPECT_EQ(expected, solution.digArtifacts(n, artifacts, dig));
}

TEST_P(CountArtifactsThatCanBeExtractedTest, Example2) {
  int n = 2;
  vector<vector<int>> artifacts = {{0, 0, 0, 0}, {0, 1, 1, 1}};
  vector<vector<int>> dig = {{0, 0}, {0, 1}, {1, 1}};
  int expected = 2;
  EXPECT_EQ(expected, solution.digArtifacts(n, artifacts, dig));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountArtifactsThatCanBeExtractedTest,
    ::testing::ValuesIn(CountArtifactsThatCanBeExtractedSolution().getStrategyNames()));

}  // namespace problem_2201
}  // namespace leetcode
