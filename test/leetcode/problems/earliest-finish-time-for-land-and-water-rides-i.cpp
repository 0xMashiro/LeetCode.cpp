#include "leetcode/problems/earliest-finish-time-for-land-and-water-rides-i.h"
#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3633 {

class EarliestFinishTimeForLandAndWaterRidesITest
    : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  EarliestFinishTimeForLandAndWaterRidesISolution solution;
};

TEST_P(EarliestFinishTimeForLandAndWaterRidesITest, Example1) {
  vector<int> landStartTime = {2, 8};
  vector<int> landDuration = {4, 1};
  vector<int> waterStartTime = {6};
  vector<int> waterDuration = {3};
  EXPECT_EQ(9, solution.earliestFinishTime(landStartTime, landDuration,
                                           waterStartTime, waterDuration));
}

TEST_P(EarliestFinishTimeForLandAndWaterRidesITest, Example2) {
  vector<int> landStartTime = {5};
  vector<int> landDuration = {3};
  vector<int> waterStartTime = {1};
  vector<int> waterDuration = {10};
  EXPECT_EQ(14, solution.earliestFinishTime(landStartTime, landDuration,
                                            waterStartTime, waterDuration));
}

TEST_P(EarliestFinishTimeForLandAndWaterRidesITest, SelfAuthoredSingleEach) {
  // 各一个项目，陆开早于水，水先更优
  vector<int> landStartTime = {10};
  vector<int> landDuration = {2};
  vector<int> waterStartTime = {1};
  vector<int> waterDuration = {5};
  // 水先: start=1, finish=6; 陆: start=max(6,10)=10, finish=12
  // 陆先: start=10, finish=12; 水: start=max(12,1)=12, finish=17
  // 最优 = 12
  EXPECT_EQ(12, solution.earliestFinishTime(landStartTime, landDuration,
                                           waterStartTime, waterDuration));
}

TEST_P(EarliestFinishTimeForLandAndWaterRidesITest, SelfAuthoredWaitNeeded) {
  // 陆先完成但水还没开，需等待
  vector<int> landStartTime = {1};
  vector<int> landDuration = {2};
  vector<int> waterStartTime = {10};
  vector<int> waterDuration = {5};
  // 陆先: start=1, finish=3; 水: start=max(3,10)=10, finish=15
  // 水先: start=10, finish=15; 陆: start=max(15,1)=15, finish=17
  // 最优 = 15
  EXPECT_EQ(15, solution.earliestFinishTime(landStartTime, landDuration,
                                           waterStartTime, waterDuration));
}

TEST_P(EarliestFinishTimeForLandAndWaterRidesITest, SelfAuthoredMultipleChoices) {
  // 多个选择，验证最优
  vector<int> landStartTime = {1, 3, 10};
  vector<int> landDuration = {5, 2, 1};
  vector<int> waterStartTime = {2, 4, 6};
  vector<int> waterDuration = {3, 7, 2};
  // land[1] (start=3,dur=2)→finish=5 → water[2] (start=6,dur=2): max(5,6)+2=8
  // water[2] (start=6,dur=2)→finish=8 → land[2] (start=10,dur=1): max(8,10)+1=11
  // land[0] (start=1,dur=5)→finish=6 → water[0] (start=2,dur=3): max(6,2)+3=9
  // water[0] (start=2,dur=3)→finish=5 → land[0] (start=1,dur=5): max(5,1)+5=10
  // ... let me compute more carefully
  // water[2] then land[2]: water start=6, finish=8; land start=max(8,10)=10, finish=11
  // land[2] then water[2]: land start=10, finish=11; water start=max(11,6)=11, finish=13
  // land[1] then water[2]: land start=3, finish=5; water start=max(5,6)=6, finish=8
  // water[0] then land[1]: water start=2, finish=5; land start=max(5,3)=5, finish=7
  // land[0] then water[2]: land start=1, finish=6; water start=max(6,6)=6, finish=8
  // Best seems to be 7 (water[0]→land[1])
  EXPECT_EQ(7, solution.earliestFinishTime(landStartTime, landDuration,
                                           waterStartTime, waterDuration));
}

TEST_P(EarliestFinishTimeForLandAndWaterRidesITest, SelfAuthoredNoWait) {
  // 两个项目时间完全不重叠，陆先 → 水正好开
  vector<int> landStartTime = {1};
  vector<int> landDuration = {3};
  vector<int> waterStartTime = {4};
  vector<int> waterDuration = {2};
  // 陆先: start=1, finish=4; 水: start=max(4,4)=4, finish=6
  // 水先: start=4, finish=6; 陆: start=max(6,1)=6, finish=9
  // 最优 = 6
  EXPECT_EQ(6, solution.earliestFinishTime(landStartTime, landDuration,
                                           waterStartTime, waterDuration));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, EarliestFinishTimeForLandAndWaterRidesITest,
    ::testing::ValuesIn(
        EarliestFinishTimeForLandAndWaterRidesISolution().getStrategyNames()));

}  // namespace problem_3633
}  // namespace leetcode
