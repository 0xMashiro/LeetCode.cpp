#include "leetcode/problems/di-string-match.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_942 {

class DiStringMatchTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DiStringMatchSolution solution;
};

// 验证生成的排列是否满足 s 的要求
bool validate(const vector<int>& perm, const string& s) {
  int n = s.length();
  if ((int)perm.size() != n + 1) return false;
  
  // 检查是否是 0~n 的排列
  vector<bool> used(n + 1, false);
  for (int x : perm) {
    if (x < 0 || x > n || used[x]) return false;
    used[x] = true;
  }
  
  // 检查是否满足 s 的要求
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'I' && perm[i] >= perm[i + 1]) return false;
    if (s[i] == 'D' && perm[i] <= perm[i + 1]) return false;
  }
  
  return true;
}

TEST_P(DiStringMatchTest, Example1) {
  string s = "IDID";
  vector<int> result = solution.diStringMatch(s);
  EXPECT_TRUE(validate(result, s));
}

TEST_P(DiStringMatchTest, Example2) {
  string s = "III";
  vector<int> result = solution.diStringMatch(s);
  EXPECT_TRUE(validate(result, s));
}

TEST_P(DiStringMatchTest, Example3) {
  string s = "DDI";
  vector<int> result = solution.diStringMatch(s);
  EXPECT_TRUE(validate(result, s));
}

TEST_P(DiStringMatchTest, SingleI) {
  string s = "I";
  vector<int> result = solution.diStringMatch(s);
  EXPECT_TRUE(validate(result, s));
}

TEST_P(DiStringMatchTest, SingleD) {
  string s = "D";
  vector<int> result = solution.diStringMatch(s);
  EXPECT_TRUE(validate(result, s));
}

TEST_P(DiStringMatchTest, AllD) {
  string s = "DDDD";
  vector<int> result = solution.diStringMatch(s);
  EXPECT_TRUE(validate(result, s));
}

TEST_P(DiStringMatchTest, AllI) {
  string s = "IIII";
  vector<int> result = solution.diStringMatch(s);
  EXPECT_TRUE(validate(result, s));
}

TEST_P(DiStringMatchTest, Alternate) {
  string s = "DIDIDI";
  vector<int> result = solution.diStringMatch(s);
  EXPECT_TRUE(validate(result, s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DiStringMatchTest,
    ::testing::ValuesIn(DiStringMatchSolution().getStrategyNames()));

}  // namespace problem_942
}  // namespace leetcode
