#include "leetcode/problems/minimum-cost-to-convert-string-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2977 {

class MinimumCostToConvertStringIiTest
    : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumCostToConvertStringIiSolution solution;
};

TEST_P(MinimumCostToConvertStringIiTest, Example1) {
  std::string source = "abcd";
  std::string target = "acbe";
  std::vector<std::string> original = {"a", "b", "c", "c", "e", "d"};
  std::vector<std::string> changed = {"b", "c", "b", "e", "b", "e"};
  std::vector<int> cost = {2, 5, 5, 1, 2, 20};
  long long expected = 28;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostToConvertStringIiTest, Example2) {
  std::string source = "abcdefgh";
  std::string target = "acdeeghh";
  std::vector<std::string> original = {"bcd", "fgh", "thh"};
  std::vector<std::string> changed = {"cde", "thh", "ghh"};
  std::vector<int> cost = {1, 3, 5};
  long long expected = 9;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostToConvertStringIiTest, Example3) {
  std::string source = "abcdefgh";
  std::string target = "addddddd";
  std::vector<std::string> original = {"bcd", "defgh"};
  std::vector<std::string> changed = {"ddd", "ddddd"};
  std::vector<int> cost = {100, 1578};
  long long expected = -1;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

// 额外测试：单个字符转换
TEST_P(MinimumCostToConvertStringIiTest, SingleChar) {
  std::string source = "a";
  std::string target = "b";
  std::vector<std::string> original = {"a"};
  std::vector<std::string> changed = {"b"};
  std::vector<int> cost = {5};
  long long expected = 5;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

// 额外测试：无法转换
TEST_P(MinimumCostToConvertStringIiTest, Impossible) {
  std::string source = "abc";
  std::string target = "def";
  std::vector<std::string> original = {"ab"};
  std::vector<std::string> changed = {"de"};
  std::vector<int> cost = {10};
  long long expected = -1;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

// 额外测试：source 等于 target
TEST_P(MinimumCostToConvertStringIiTest, SameString) {
  std::string source = "hello";
  std::string target = "hello";
  std::vector<std::string> original = {"he", "ll"};
  std::vector<std::string> changed = {"xx", "yy"};
  std::vector<int> cost = {1, 2};
  long long expected = 0;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumCostToConvertStringIiTest,
    ::testing::ValuesIn(MinimumCostToConvertStringIiSolution().getStrategyNames()));

}  // namespace problem_2977
}  // namespace leetcode