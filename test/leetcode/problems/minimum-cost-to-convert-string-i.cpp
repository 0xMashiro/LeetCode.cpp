#include "leetcode/problems/minimum-cost-to-convert-string-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2976 {

class MinimumCostToConvertStringITest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumCostToConvertStringISolution solution;
};

TEST_P(MinimumCostToConvertStringITest, Example1) {
  string source = "abcd";
  string target = "acbe";
  vector<char> original = {'a', 'b', 'c', 'c', 'e', 'd'};
  vector<char> changed = {'b', 'c', 'b', 'e', 'b', 'e'};
  vector<int> cost = {2, 5, 5, 1, 2, 20};
  long long expected = 28;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostToConvertStringITest, Example2) {
  string source = "aaaa";
  string target = "bbbb";
  vector<char> original = {'a', 'c'};
  vector<char> changed = {'c', 'b'};
  vector<int> cost = {1, 2};
  long long expected = 12;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostToConvertStringITest, Example3) {
  string source = "abcd";
  string target = "abce";
  vector<char> original = {'a'};
  vector<char> changed = {'e'};
  vector<int> cost = {10000};
  long long expected = -1;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostToConvertStringITest, SameString) {
  string source = "hello";
  string target = "hello";
  vector<char> original = {'a', 'b'};
  vector<char> changed = {'b', 'c'};
  vector<int> cost = {1, 2};
  long long expected = 0;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostToConvertStringITest, DirectConversion) {
  string source = "abc";
  string target = "def";
  vector<char> original = {'a', 'b', 'c'};
  vector<char> changed = {'d', 'e', 'f'};
  vector<int> cost = {10, 20, 30};
  long long expected = 10 + 20 + 30;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostToConvertStringITest, IndirectConversion) {
  string source = "aa";
  string target = "bb";
  vector<char> original = {'a', 'c'};
  vector<char> changed = {'c', 'b'};
  vector<int> cost = {5, 7};
  // 转换路径：a -> c (5) + c -> b (7) = 12 per character
  long long expected = 24;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostToConvertStringITest, MultipleEdgesSamePair) {
  string source = "a";
  string target = "b";
  vector<char> original = {'a', 'a', 'a'};
  vector<char> changed = {'b', 'b', 'b'};
  vector<int> cost = {100, 10, 1};
  // 应该选择最小的成本 1
  long long expected = 1;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostToConvertStringITest, Unreachable) {
  string source = "a";
  string target = "b";
  vector<char> original = {'a', 'c'};
  vector<char> changed = {'c', 'd'};
  vector<int> cost = {1, 2};
  // 没有从 a 到 b 的路径
  long long expected = -1;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostToConvertStringITest, SelfLoop) {
  string source = "a";
  string target = "a";
  vector<char> original = {'a'};
  vector<char> changed = {'a'};
  vector<int> cost = {100};
  // 相同字符不需要转换，成本为 0
  long long expected = 0;
  long long result = solution.minimumCost(source, target, original, changed, cost);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumCostToConvertStringITest,
    ::testing::ValuesIn(MinimumCostToConvertStringISolution().getStrategyNames()));

}  // namespace problem_2976
}  // namespace leetcode