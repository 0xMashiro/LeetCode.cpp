#include "leetcode/problems/russian-doll-envelopes.h"

#include "gtest/gtest.h"

#include <vector>

namespace leetcode {
namespace problem_354 {

class RussianDollEnvelopesTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RussianDollEnvelopesSolution solution;
};

TEST_P(RussianDollEnvelopesTest, Example1) {
  vector<vector<int>> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
  EXPECT_EQ(3, solution.maxEnvelopes(envelopes));
}

TEST_P(RussianDollEnvelopesTest, Example2) {
  vector<vector<int>> envelopes = {{1, 1}, {1, 1}, {1, 1}};
  EXPECT_EQ(1, solution.maxEnvelopes(envelopes));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RussianDollEnvelopesTest,
    ::testing::ValuesIn(RussianDollEnvelopesSolution().getStrategyNames()));

}  // namespace problem_354
}  // namespace leetcode
