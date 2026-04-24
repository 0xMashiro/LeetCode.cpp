#include "leetcode/problems/handling-sum-queries-after-update.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2569 {

class HandlingSumQueriesAfterUpdateTest
    : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  HandlingSumQueriesAfterUpdateSolution solution;
};

TEST_P(HandlingSumQueriesAfterUpdateTest, Example1) {
  vector<int> nums1 = {1, 0, 1};
  vector<int> nums2 = {0, 0, 0};
  vector<vector<int>> queries = {{1, 1, 1}, {2, 1, 0}, {3, 0, 0}};
  vector<long long> expected = {3};
  vector<long long> result = solution.handleQuery(nums1, nums2, queries);
  EXPECT_EQ(expected, result);
}

TEST_P(HandlingSumQueriesAfterUpdateTest, Example2) {
  vector<int> nums1 = {1};
  vector<int> nums2 = {5};
  vector<vector<int>> queries = {{2, 0, 0}, {3, 0, 0}};
  vector<long long> expected = {5};
  vector<long long> result = solution.handleQuery(nums1, nums2, queries);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, HandlingSumQueriesAfterUpdateTest,
    ::testing::ValuesIn(
        HandlingSumQueriesAfterUpdateSolution().getStrategyNames()));

}  // namespace problem_2569
}  // namespace leetcode
