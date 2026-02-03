#include "leetcode/problems/camelcase-matching.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1023 {

class CamelcaseMatchingTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CamelcaseMatchingSolution solution;
};

TEST_P(CamelcaseMatchingTest, Example1) {
  vector<string> queries = {"FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"};
  string pattern = "FB";
  vector<bool> expected = {true, false, true, true, false};
  vector<bool> result = solution.camelMatch(queries, pattern);
  EXPECT_EQ(expected, result);
}

TEST_P(CamelcaseMatchingTest, Example2) {
  vector<string> queries = {"FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"};
  string pattern = "FoBa";
  vector<bool> expected = {true, false, true, false, false};
  vector<bool> result = solution.camelMatch(queries, pattern);
  EXPECT_EQ(expected, result);
}

TEST_P(CamelcaseMatchingTest, Example3) {
  vector<string> queries = {"FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"};
  string pattern = "FoBaT";
  vector<bool> expected = {false, true, false, false, false};
  vector<bool> result = solution.camelMatch(queries, pattern);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CamelcaseMatchingTest,
    ::testing::ValuesIn(CamelcaseMatchingSolution().getStrategyNames()));

}  // namespace problem_1023
}  // namespace leetcode
