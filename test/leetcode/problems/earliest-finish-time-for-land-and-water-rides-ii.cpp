#include "leetcode/problems/earliest-finish-time-for-land-and-water-rides-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3635 {

class EarliestFinishTimeForLandAndWaterRidesIiTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  EarliestFinishTimeForLandAndWaterRidesIiSolution solution;
};

TEST_P(EarliestFinishTimeForLandAndWaterRidesIiTest, Example1) {
  vector<int> landStartTime = {2, 8};
  vector<int> landDuration = {4, 1};
  vector<int> waterStartTime = {6};
  vector<int> waterDuration = {3};
  EXPECT_EQ(9, solution.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration));
}

TEST_P(EarliestFinishTimeForLandAndWaterRidesIiTest, Example2) {
  vector<int> landStartTime = {5};
  vector<int> landDuration = {3};
  vector<int> waterStartTime = {1};
  vector<int> waterDuration = {10};
  EXPECT_EQ(14, solution.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration));
}

TEST_P(EarliestFinishTimeForLandAndWaterRidesIiTest, SelfAuthoredSingleEach) {
  vector<int> landStartTime = {10};
  vector<int> landDuration = {5};
  vector<int> waterStartTime = {3};
  vector<int> waterDuration = {4};
  // Land first: start land at 10, finish 15. Water start = max(15, 3) = 15, finish = 15+4 = 19
  // Water first: start water at 3, finish 7. Land start = max(7, 10) = 10, finish = 10+5 = 15
  // Earliest = 15
  EXPECT_EQ(15, solution.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration));
}

TEST_P(EarliestFinishTimeForLandAndWaterRidesIiTest, SelfAuthoredStartLater) {
  vector<int> landStartTime = {100};
  vector<int> landDuration = {1};
  vector<int> waterStartTime = {50};
  vector<int> waterDuration = {10};
  // Land first: start land at 100, finish 101. Water start = max(101, 50) = 101, finish = 101+10 = 111
  // Water first: start water at 50, finish 60. Land start = max(60, 100) = 100, finish = 100+1 = 101
  // Earliest = 101
  EXPECT_EQ(101, solution.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration));
}

TEST_P(EarliestFinishTimeForLandAndWaterRidesIiTest, SelfAuthoredWaterTakesLong) {
  vector<int> landStartTime = {1, 5};
  vector<int> landDuration = {2, 3};
  vector<int> waterStartTime = {1};
  vector<int> waterDuration = {100};
  // Water takes very long, best is land first
  // Land 0: start land at 1, finish 3. Water start = max(3, 1) = 3, finish = 3+100 = 103
  // Land 1: start land at 5, finish 8. Water start = max(8, 1) = 8, finish = 8+100 = 108
  // Water first: start water at 1, finish 101. Land start = max(101, 1) = 101, finish = 101+2 = 103 or 101+3 = 104
  // Earliest = min(103, 108, 103, 104) = 103
  EXPECT_EQ(103, solution.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration));
}

TEST_P(EarliestFinishTimeForLandAndWaterRidesIiTest, SelfAuthoredLandTakesLong) {
  vector<int> landStartTime = {1};
  vector<int> landDuration = {100};
  vector<int> waterStartTime = {1, 10};
  vector<int> waterDuration = {2, 5};
  // Land takes very long, best is water first
  // Water first with j=0: start water at 1, finish 3. Land start = max(3, 1) = 3, finish = 3+100 = 103
  // Water first with j=1: start water at 10, finish 15. Land start = max(15, 1) = 15, finish = 15+100 = 115
  // Land first: start land at 1, finish 101. Water start = max(101, 1) = 101, finish = 101+2 = 103 or 101+5 = 106
  // Earliest = min(103, 115, 103, 106) = 103
  EXPECT_EQ(103, solution.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, EarliestFinishTimeForLandAndWaterRidesIiTest,
    ::testing::ValuesIn(EarliestFinishTimeForLandAndWaterRidesIiSolution().getStrategyNames()));

}  // namespace problem_3635
}  // namespace leetcode
