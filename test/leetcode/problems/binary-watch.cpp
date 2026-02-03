#include "leetcode/problems/binary-watch.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_401 {

class BinaryWatchTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BinaryWatchSolution solution;
};

TEST_P(BinaryWatchTest, Example1) {
  int turnedOn = 1;
  vector<string> expected = {"0:01", "0:02", "0:04", "0:08", "0:16", "0:32",
                              "1:00", "2:00", "4:00", "8:00"};
  vector<string> result = solution.readBinaryWatch(turnedOn);
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(BinaryWatchTest, Example2) {
  int turnedOn = 9;
  vector<string> expected = {};
  vector<string> result = solution.readBinaryWatch(turnedOn);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BinaryWatchTest,
    ::testing::ValuesIn(BinaryWatchSolution().getStrategyNames()));

}  // namespace problem_401
}  // namespace leetcode
