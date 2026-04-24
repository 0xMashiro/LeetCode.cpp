#include "leetcode/problems/stamping-the-sequence.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_936 {

class StampingTheSequenceTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  StampingTheSequenceSolution solution;
};

TEST_P(StampingTheSequenceTest, Example1) {
  string stamp = "abc";
  string target = "ababc";
  vector<int> result = solution.movesToStamp(stamp, target);
  // 验证结果不为空
  EXPECT_FALSE(result.empty());
  // 验证操作序列能正确还原出 target
  string check(target.size(), '?');
  for (int pos : result) {
    for (int j = 0; j < (int)stamp.size(); ++j) {
      check[pos + j] = stamp[j];
    }
  }
  EXPECT_EQ(target, check);
}

TEST_P(StampingTheSequenceTest, Example2) {
  string stamp = "abca";
  string target = "aabcaca";
  vector<int> result = solution.movesToStamp(stamp, target);
  // 验证结果不为空
  EXPECT_FALSE(result.empty());
  // 验证操作序列能正确还原出 target
  string check(target.size(), '?');
  for (int pos : result) {
    for (int j = 0; j < (int)stamp.size(); ++j) {
      check[pos + j] = stamp[j];
    }
  }
  EXPECT_EQ(target, check);
}

TEST_P(StampingTheSequenceTest, ImpossibleCase) {
  // 无法完成的情况
  string stamp = "abc";
  string target = "abca";
  vector<int> result = solution.movesToStamp(stamp, target);
  EXPECT_TRUE(result.empty());
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, StampingTheSequenceTest,
    ::testing::ValuesIn(StampingTheSequenceSolution().getStrategyNames()));

}  // namespace problem_936
}  // namespace leetcode
