#include "leetcode/problems/count-good-numbers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1922 {

class CountGoodNumbersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountGoodNumbersSolution solution;
};

// 示例 1：n = 1
// 只有一个位置（索引 0，偶数位置），可选 {0, 2, 4, 6, 8} = 5 种
TEST_P(CountGoodNumbersTest, Example1) {
  long long n = 1;
  int expected = 5;
  EXPECT_EQ(expected, solution.countGoodNumbers(n));
}

// 示例 2：n = 4
// 偶数位置（索引 0, 2）：2 个位置，每个 5 种选择 → 5^2 = 25
// 奇数位置（索引 1, 3）：2 个位置，每个 4 种选择 → 4^2 = 16
// 总数 = 25 × 16 = 400
TEST_P(CountGoodNumbersTest, Example2) {
  long long n = 4;
  int expected = 400;
  EXPECT_EQ(expected, solution.countGoodNumbers(n));
}

// 示例 3：n = 50
TEST_P(CountGoodNumbersTest, Example3) {
  long long n = 50;
  int expected = 564908303;
  EXPECT_EQ(expected, solution.countGoodNumbers(n));
}

// 边界测试：n = 2
// 偶数位置（索引 0）：1 个位置 → 5
// 奇数位置（索引 1）：1 个位置 → 4
// 总数 = 5 × 4 = 20
TEST_P(CountGoodNumbersTest, NEquals2) {
  long long n = 2;
  int expected = 20;
  EXPECT_EQ(expected, solution.countGoodNumbers(n));
}

// 边界测试：n = 3
// 偶数位置（索引 0, 2）：2 个位置 → 5^2 = 25
// 奇数位置（索引 1）：1 个位置 → 4
// 总数 = 25 × 4 = 100
TEST_P(CountGoodNumbersTest, NEquals3) {
  long long n = 3;
  int expected = 100;
  EXPECT_EQ(expected, solution.countGoodNumbers(n));
}

// 大数测试：n = 10^15（测试快速幂的性能）
TEST_P(CountGoodNumbersTest, LargeN) {
  long long n = 1000000000000000LL;  // 10^15
  // 验证不会超时即可，不检查具体值
  int result = solution.countGoodNumbers(n);
  // 验证结果在有效范围内
  EXPECT_GE(result, 0);
  EXPECT_LT(result, 1000000007);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountGoodNumbersTest,
    ::testing::ValuesIn(CountGoodNumbersSolution().getStrategyNames()));

}  // namespace problem_1922
}  // namespace leetcode
