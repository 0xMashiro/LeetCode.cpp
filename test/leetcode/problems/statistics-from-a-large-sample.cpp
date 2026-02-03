#include "leetcode/problems/statistics-from-a-large-sample.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1093 {

class StatisticsFromALargeSampleTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  
  StatisticsFromALargeSampleSolution solution;
};

TEST_P(StatisticsFromALargeSampleTest, Example1) {
  // count[0]=0, count[1]=1, count[2]=3, count[3]=4, 其余为0
  // 样本为 [1,2,2,2,3,3,3,3]
  // min=1, max=3, mean=19/8=2.375, median=(2+3)/2=2.5, mode=3
  vector<int> count(256, 0);
  count[1] = 1;
  count[2] = 3;
  count[3] = 4;
  
  vector<double> result = solution.sampleStats(count);
  
  EXPECT_DOUBLE_EQ(1.00000, result[0]);  // minimum
  EXPECT_DOUBLE_EQ(3.00000, result[1]);  // maximum
  EXPECT_DOUBLE_EQ(2.37500, result[2]);  // mean
  EXPECT_DOUBLE_EQ(2.50000, result[3]);  // median
  EXPECT_DOUBLE_EQ(3.00000, result[4]);  // mode
}

TEST_P(StatisticsFromALargeSampleTest, Example2) {
  // count[1]=4, count[2]=3, count[3]=2, count[4]=2, 其余为0
  // 样本为 [1,1,1,1,2,2,2,3,3,4,4]
  // min=1, max=4, mean=24/11=2.18182..., median=2, mode=1
  vector<int> count(256, 0);
  count[1] = 4;
  count[2] = 3;
  count[3] = 2;
  count[4] = 2;
  
  vector<double> result = solution.sampleStats(count);
  
  EXPECT_DOUBLE_EQ(1.00000, result[0]);  // minimum
  EXPECT_DOUBLE_EQ(4.00000, result[1]);  // maximum
  EXPECT_NEAR(2.18182, result[2], 0.00001);  // mean
  EXPECT_DOUBLE_EQ(2.00000, result[3]);  // median
  EXPECT_DOUBLE_EQ(1.00000, result[4]);  // mode
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, StatisticsFromALargeSampleTest,
    ::testing::ValuesIn(StatisticsFromALargeSampleSolution().getStrategyNames()));

}  // namespace problem_1093
}  // namespace leetcode
