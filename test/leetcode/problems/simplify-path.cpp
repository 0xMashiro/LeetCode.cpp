#include "leetcode/problems/simplify-path.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_71 {

class SimplifyPathTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SimplifyPathSolution solution;
};

TEST_P(SimplifyPathTest, Example1) {
  string path = "/home/";
  string expected = "/home";
  EXPECT_EQ(expected, solution.simplifyPath(path));
}

TEST_P(SimplifyPathTest, Example2) {
  string path = "/home//foo/";
  string expected = "/home/foo";
  EXPECT_EQ(expected, solution.simplifyPath(path));
}

TEST_P(SimplifyPathTest, Example3) {
  string path = "/home/user/Documents/../Pictures";
  string expected = "/home/user/Pictures";
  EXPECT_EQ(expected, solution.simplifyPath(path));
}

TEST_P(SimplifyPathTest, Example4) {
  string path = "/../";
  string expected = "/";
  EXPECT_EQ(expected, solution.simplifyPath(path));
}

TEST_P(SimplifyPathTest, Example5) {
  string path = "/.../a/../b/c/../d/./";
  string expected = "/.../b/d";
  EXPECT_EQ(expected, solution.simplifyPath(path));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SimplifyPathTest,
    ::testing::ValuesIn(SimplifyPathSolution().getStrategyNames()));

}  // namespace problem_71
}  // namespace leetcode
