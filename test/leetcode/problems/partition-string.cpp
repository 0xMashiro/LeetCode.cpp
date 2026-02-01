#include "leetcode/problems/partition-string.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3597 {

class PartitionStringTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PartitionStringSolution solution;
};

TEST_P(PartitionStringTest, Example1) {
  string s = "abbccccd";
  vector<string> expected = {"a", "b", "bc", "c", "cc", "d"};
  vector<string> result = solution.partitionString(s);
  EXPECT_EQ(expected, result);
}

TEST_P(PartitionStringTest, Example2) {
  string s = "aaaa";
  vector<string> expected = {"a", "aa"};
  vector<string> result = solution.partitionString(s);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PartitionStringTest,
    ::testing::ValuesIn(PartitionStringSolution().getStrategyNames()));

}  // namespace problem_3597
}  // namespace leetcode
