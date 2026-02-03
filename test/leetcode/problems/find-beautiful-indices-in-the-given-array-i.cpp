#include "leetcode/problems/find-beautiful-indices-in-the-given-array-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3006 {

class FindBeautifulIndicesInTheGivenArrayITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindBeautifulIndicesInTheGivenArrayISolution solution;
};

TEST_P(FindBeautifulIndicesInTheGivenArrayITest, Example1) {
  string s = "isawsquirrelnearmysquirrelhouseohmy";
  string a = "my";
  string b = "squirrel";
  int k = 15;
  vector<int> expected = {16, 33};
  vector<int> result = solution.beautifulIndices(s, a, b, k);
  EXPECT_EQ(expected, result);
}

TEST_P(FindBeautifulIndicesInTheGivenArrayITest, Example2) {
  string s = "abcd";
  string a = "a";
  string b = "a";
  int k = 4;
  vector<int> expected = {0};
  vector<int> result = solution.beautifulIndices(s, a, b, k);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindBeautifulIndicesInTheGivenArrayITest,
    ::testing::ValuesIn(FindBeautifulIndicesInTheGivenArrayISolution().getStrategyNames()));

}  // namespace problem_3006
}  // namespace leetcode
