
#include "leetcode/problems/queue-reconstruction-by-height.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_406 {

class QueueReconstructionByHeightTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  QueueReconstructionByHeightSolution solution;
};

TEST_P(QueueReconstructionByHeightTest, Example1) {
  vector<vector<int>> people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
  vector<vector<int>> expected = {{5,0},{7,0},{5,2},{6,1},{4,4},{7,1}};
  EXPECT_EQ(expected, solution.reconstructQueue(people));
}

TEST_P(QueueReconstructionByHeightTest, Example2) {
  vector<vector<int>> people = {{6,0},{5,0},{4,0},{3,2},{2,2},{1,4}};
  vector<vector<int>> expected = {{4,0},{5,0},{2,2},{3,2},{1,4},{6,0}};
  EXPECT_EQ(expected, solution.reconstructQueue(people));
}

TEST_P(QueueReconstructionByHeightTest, SinglePerson) {
  vector<vector<int>> people = {{1,0}};
  vector<vector<int>> expected = {{1,0}};
  EXPECT_EQ(expected, solution.reconstructQueue(people));
}

TEST_P(QueueReconstructionByHeightTest, TwoPeopleSameHeight) {
  vector<vector<int>> people = {{5,0},{5,1}};
  vector<vector<int>> expected = {{5,0},{5,1}};
  EXPECT_EQ(expected, solution.reconstructQueue(people));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, QueueReconstructionByHeightTest,
    ::testing::ValuesIn(QueueReconstructionByHeightSolution().getStrategyNames()));

}  // namespace problem_406
}  // namespace leetcode
