
#include "leetcode/problems/find-all-groups-of-farmland.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1992 {

class FindAllGroupsOfFarmlandTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindAllGroupsOfFarmlandSolution solution;
};

TEST_P(FindAllGroupsOfFarmlandTest, Example1) {
  vector<vector<int>> land = {{1,0,0},{0,1,1},{0,1,1}};
  vector<vector<int>> expected = {{0,0,0,0},{1,1,2,2}};
  vector<vector<int>> result = solution.findFarmland(land);
  // 由于顺序不重要，对结果进行排序后比较
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(FindAllGroupsOfFarmlandTest, Example2) {
  vector<vector<int>> land = {{1,1},{1,1}};
  vector<vector<int>> expected = {{0,0,1,1}};
  vector<vector<int>> result = solution.findFarmland(land);
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(FindAllGroupsOfFarmlandTest, Example3) {
  vector<vector<int>> land = {{0}};
  vector<vector<int>> expected = {};
  vector<vector<int>> result = solution.findFarmland(land);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindAllGroupsOfFarmlandTest,
    ::testing::ValuesIn(FindAllGroupsOfFarmlandSolution().getStrategyNames()));

}  // namespace problem_1992
}  // namespace leetcode
