#include "leetcode/problems/prime-subtraction-operation.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2601 {

class PrimeSubtractionOperationTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PrimeSubtractionOperationSolution solution;
};

TEST_P(PrimeSubtractionOperationTest, Example1) {
  vector<int> nums = {4, 9, 6, 10};
  EXPECT_TRUE(solution.primeSubOperation(nums));
}

TEST_P(PrimeSubtractionOperationTest, Example2) {
  vector<int> nums = {6, 8, 11, 12};
  EXPECT_TRUE(solution.primeSubOperation(nums));
}

TEST_P(PrimeSubtractionOperationTest, Example3) {
  vector<int> nums = {5, 8, 3};
  EXPECT_FALSE(solution.primeSubOperation(nums));
}

TEST_P(PrimeSubtractionOperationTest, SingleElement) {
  vector<int> nums = {1};
  EXPECT_TRUE(solution.primeSubOperation(nums));
}

TEST_P(PrimeSubtractionOperationTest, TwoElementsIncreasing) {
  vector<int> nums = {1, 2};
  EXPECT_TRUE(solution.primeSubOperation(nums));
}

TEST_P(PrimeSubtractionOperationTest, TwoElementsCannotFix) {
  // [1, 1]: 第一个1不能减任何质数(需要p<1)，保持1
  // 第二个1必须>1，但nums[1]=1无法变成>1（最大能减的质数是0，不存在）
  vector<int> nums = {1, 1};
  EXPECT_FALSE(solution.primeSubOperation(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PrimeSubtractionOperationTest,
    ::testing::ValuesIn(PrimeSubtractionOperationSolution().getStrategyNames()));

}  // namespace problem_2601
}  // namespace leetcode
