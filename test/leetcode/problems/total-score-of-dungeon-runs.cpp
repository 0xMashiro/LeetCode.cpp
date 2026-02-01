#include "leetcode/problems/total-score-of-dungeon-runs.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3771 {

class TotalScoreOfDungeonRunsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TotalScoreOfDungeonRunsSolution solution;
};

TEST_P(TotalScoreOfDungeonRunsTest, Example1) {
  int hp = 11;
  vector<int> damage = {3, 6, 7};
  vector<int> requirement = {4, 2, 5};
  EXPECT_EQ(3, solution.totalScore(hp, damage, requirement));
}

TEST_P(TotalScoreOfDungeonRunsTest, Example2) {
  int hp = 2;
  vector<int> damage = {10000, 1};
  vector<int> requirement = {1, 1};
  EXPECT_EQ(1, solution.totalScore(hp, damage, requirement));
}

TEST_P(TotalScoreOfDungeonRunsTest, SingleRoom) {
  // 只有一个房间
  int hp = 10;
  vector<int> damage = {5};
  vector<int> requirement = {5};
  // prefix[0]=0, prefix[1]=5
  // k=1: need = 5 + 5 - 10 = 0, prefix[0]=0 >= 0, 贡献 1
  EXPECT_EQ(1, solution.totalScore(hp, damage, requirement));
}

TEST_P(TotalScoreOfDungeonRunsTest, SingleRoomNoPoint) {
  // 只有一个房间，但无法满足要求
  int hp = 10;
  vector<int> damage = {6};
  vector<int> requirement = {5};
  // prefix[0]=0, prefix[1]=6
  // k=1: need = 6 + 5 - 10 = 1, prefix[0]=0 < 1, 贡献 0
  EXPECT_EQ(0, solution.totalScore(hp, damage, requirement));
}

TEST_P(TotalScoreOfDungeonRunsTest, AllZeroDamage) {
  // damage 为 1（最小值），requirement 很小
  int hp = 100;
  vector<int> damage = {1, 1, 1, 1, 1};
  vector<int> requirement = {1, 1, 1, 1, 1};
  // 从任意位置开始，只要剩余血量 >= 1 就能得分
  // 计算: 对于房间 k，need = k + 1 - 100 = k - 99
  // prefix[0..k-1] = 0,1,2,...,k-1
  // 满足 >= k-99 的个数：
  // k=1: need=-98, 0>=-98, 1个
  // k=2: need=-97, 0,1 都>=-97, 2个
  // ...
  // k=5: need=-94, 0,1,2,3,4 都>=-94, 5个
  // 总和 = 1+2+3+4+5 = 15
  EXPECT_EQ(15, solution.totalScore(hp, damage, requirement));
}

TEST_P(TotalScoreOfDungeonRunsTest, LargeHp) {
  // hp 很大，可以完成所有房间
  int hp = 1000000000;
  vector<int> damage = {1, 2, 3};
  vector<int> requirement = {100, 200, 300};
  // 从任意位置开始都能完成所有房间
  // score(1)=3, score(2)=2, score(3)=1, 总和=6
  EXPECT_EQ(6, solution.totalScore(hp, damage, requirement));
}

TEST_P(TotalScoreOfDungeonRunsTest, SmallHp) {
  // hp 很小，无法获得任何分数
  int hp = 1;
  vector<int> damage = {2, 2, 2};
  vector<int> requirement = {1, 1, 1};
  // 进入第一个房间就死，无法获得任何分数
  EXPECT_EQ(0, solution.totalScore(hp, damage, requirement));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TotalScoreOfDungeonRunsTest,
    ::testing::ValuesIn(TotalScoreOfDungeonRunsSolution().getStrategyNames()));

}  // namespace problem_3771
}  // namespace leetcode
