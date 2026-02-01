#include "leetcode/problems/mice-and-cheese.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2611 {

class MiceAndCheeseTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MiceAndCheeseSolution solution;
};

// 示例 1: reward1 = [1,1,3,4], reward2 = [4,4,1,1], k = 2, 输出: 15
TEST_P(MiceAndCheeseTest, Example1) {
  vector<int> reward1 = {1, 1, 3, 4};
  vector<int> reward2 = {4, 4, 1, 1};
  int k = 2;
  EXPECT_EQ(15, solution.miceAndCheese(reward1, reward2, k));
}

// 示例 2: reward1 = [1,1], reward2 = [1,1], k = 2, 输出: 2
TEST_P(MiceAndCheeseTest, Example2) {
  vector<int> reward1 = {1, 1};
  vector<int> reward2 = {1, 1};
  int k = 2;
  EXPECT_EQ(2, solution.miceAndCheese(reward1, reward2, k));
}

// 边界: k = 0，第一只老鼠不吃任何奶酪
TEST_P(MiceAndCheeseTest, KIsZero) {
  vector<int> reward1 = {5, 5, 5};
  vector<int> reward2 = {1, 2, 3};
  int k = 0;
  EXPECT_EQ(6, solution.miceAndCheese(reward1, reward2, k));  // 1+2+3=6
}

// 边界: k = n，第一只老鼠吃所有奶酪
TEST_P(MiceAndCheeseTest, KIsN) {
  vector<int> reward1 = {5, 5, 5};
  vector<int> reward2 = {1, 2, 3};
  int k = 3;
  EXPECT_EQ(15, solution.miceAndCheese(reward1, reward2, k));  // 5+5+5=15
}

// 边界: n = 1, k = 0
TEST_P(MiceAndCheeseTest, SingleElementK0) {
  vector<int> reward1 = {10};
  vector<int> reward2 = {5};
  int k = 0;
  EXPECT_EQ(5, solution.miceAndCheese(reward1, reward2, k));
}

// 边界: n = 1, k = 1
TEST_P(MiceAndCheeseTest, SingleElementK1) {
  vector<int> reward1 = {10};
  vector<int> reward2 = {5};
  int k = 1;
  EXPECT_EQ(10, solution.miceAndCheese(reward1, reward2, k));
}

// 测试: reward1 远大于 reward2
TEST_P(MiceAndCheeseTest, Reward1MuchLarger) {
  vector<int> reward1 = {100, 100, 100};
  vector<int> reward2 = {1, 1, 1};
  int k = 2;
  // 选两个 reward1 最大的(都是100)，一个 reward2
  EXPECT_EQ(201, solution.miceAndCheese(reward1, reward2, k));  // 100+100+1=201
}

// 测试: reward2 远大于 reward1
TEST_P(MiceAndCheeseTest, Reward2MuchLarger) {
  vector<int> reward1 = {1, 1, 1};
  vector<int> reward2 = {100, 100, 100};
  int k = 2;
  // 即使 reward2 大，但必须选 k=2 个 reward1
  EXPECT_EQ(102, solution.miceAndCheese(reward1, reward2, k));  // 1+1+100=102
}

// 测试: 相同差值的情况
TEST_P(MiceAndCheeseTest, SameDiff) {
  vector<int> reward1 = {5, 5, 5};
  vector<int> reward2 = {3, 3, 3};
  int k = 2;
  // 任意选2个 reward1 和 1个 reward2
  EXPECT_EQ(13, solution.miceAndCheese(reward1, reward2, k));  // 5+5+3=13
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MiceAndCheeseTest,
    ::testing::ValuesIn(MiceAndCheeseSolution().getStrategyNames()));

}  // namespace problem_2611
}  // namespace leetcode
