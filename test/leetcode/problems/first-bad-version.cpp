#include "leetcode/problems/first-bad-version.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_278 {

class FirstBadVersionTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FirstBadVersionSolution solution;
};

TEST_P(FirstBadVersionTest, Example1) {
  // n = 5, bad = 4
  int n = 5;
  int bad = 4;
  isBadVersion_api = [bad](int version) { return version >= bad; };
  EXPECT_EQ(solution.firstBadVersion(n), 4);
}

TEST_P(FirstBadVersionTest, Example2) {
  // n = 1, bad = 1
  int n = 1;
  int bad = 1;
  isBadVersion_api = [bad](int version) { return version >= bad; };
  EXPECT_EQ(solution.firstBadVersion(n), 1);
}

TEST_P(FirstBadVersionTest, AllBadVersions) {
  // n = 10, bad = 1（所有版本都是坏的）
  int n = 10;
  int bad = 1;
  isBadVersion_api = [bad](int version) { return version >= bad; };
  EXPECT_EQ(solution.firstBadVersion(n), 1);
}

TEST_P(FirstBadVersionTest, OnlyLastBad) {
  // n = 10, bad = 10（只有最后一个版本是坏的）
  int n = 10;
  int bad = 10;
  isBadVersion_api = [bad](int version) { return version >= bad; };
  EXPECT_EQ(solution.firstBadVersion(n), 10);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FirstBadVersionTest,
    ::testing::ValuesIn(FirstBadVersionSolution().getStrategyNames()));

}  // namespace problem_278
}  // namespace leetcode
