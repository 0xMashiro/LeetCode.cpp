#include "leetcode/problems/construct-the-minimum-bitwise-array-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3314 {

class ConstructTheMinimumBitwiseArrayITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConstructTheMinimumBitwiseArrayISolution solution;
};

TEST_P(ConstructTheMinimumBitwiseArrayITest, Example1) {
  std::vector<int> nums = {2, 3, 5, 7};
  std::vector<int> expected = {-1, 1, 4, 3};
  std::vector<int> result = solution.minBitwiseArray(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(ConstructTheMinimumBitwiseArrayITest, Example2) {
  std::vector<int> nums = {11, 13, 31};
  std::vector<int> expected = {9, 12, 15};
  std::vector<int> result = solution.minBitwiseArray(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(ConstructTheMinimumBitwiseArrayITest, SingleElement) {
  std::vector<int> nums = {2};
  std::vector<int> expected = {-1};
  std::vector<int> result = solution.minBitwiseArray(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(ConstructTheMinimumBitwiseArrayITest, AllOnes) {
  std::vector<int> nums = {3, 7, 15};
  std::vector<int> expected = {1, 3, 7};  // 验证：1|2=3, 3|4=7, 7|8=15
  std::vector<int> result = solution.minBitwiseArray(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(ConstructTheMinimumBitwiseArrayITest, RandomPrimes) {
  // 测试一些随机素数（在1000以内）
  std::vector<int> nums = {5, 17, 19, 23, 29};
  // 手动计算预期结果
  // 为了确保测试通过，我们先使用暴力算法计算预期值
  std::vector<int> expected;
  for (int n : nums) {
    int x = -1;
    for (int candidate = 0; candidate < n; ++candidate) {
      if ((candidate | (candidate + 1)) == n) {
        x = candidate;
        break;
      }
    }
    expected.push_back(x);
  }
  std::vector<int> result = solution.minBitwiseArray(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(ConstructTheMinimumBitwiseArrayITest, EdgeCases) {
  // 测试边界情况
  std::vector<int> nums = {2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> expected;
  for (int n : nums) {
    int x = -1;
    for (int candidate = 0; candidate < n; ++candidate) {
      if ((candidate | (candidate + 1)) == n) {
        x = candidate;
        break;
      }
    }
    expected.push_back(x);
  }
  std::vector<int> result = solution.minBitwiseArray(nums);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConstructTheMinimumBitwiseArrayITest,
    ::testing::ValuesIn(ConstructTheMinimumBitwiseArrayISolution().getStrategyNames()));

}  // namespace problem_3314
}  // namespace leetcode