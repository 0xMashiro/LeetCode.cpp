#include "leetcode/problems/minimum-time-to-transport-all-individuals.h"
#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3594 {

class MinimumTimeToTransportAllIndividualsTest
    : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  MinimumTimeToTransportAllIndividualsSolution solution;
};

TEST_P(MinimumTimeToTransportAllIndividualsTest, Example1) {
    int n = 1, k = 1, m = 2;
    vector<int> time = {5};
    vector<double> mul = {1.0, 1.3};
    double expected = 5.0;
    double result = solution.minTime(n, k, m, time, mul);
    EXPECT_NEAR(expected, result, 1e-5);
}

TEST_P(MinimumTimeToTransportAllIndividualsTest, Example2) {
    int n = 3, k = 2, m = 3;
    vector<int> time = {2, 5, 8};
    vector<double> mul = {1.0, 1.5, 0.75};
    double expected = 14.5;
    double result = solution.minTime(n, k, m, time, mul);
    EXPECT_NEAR(expected, result, 1e-5);
}

TEST_P(MinimumTimeToTransportAllIndividualsTest, Example3) {
    int n = 2, k = 1, m = 2;
    vector<int> time = {10, 10};
    vector<double> mul = {2.0, 2.0};
    double expected = -1.0;
    double result = solution.minTime(n, k, m, time, mul);
    EXPECT_NEAR(expected, result, 1e-5);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumTimeToTransportAllIndividualsTest,
    ::testing::ValuesIn(
        MinimumTimeToTransportAllIndividualsSolution().getStrategyNames()));

}  // namespace problem_3594
}  // namespace leetcode
