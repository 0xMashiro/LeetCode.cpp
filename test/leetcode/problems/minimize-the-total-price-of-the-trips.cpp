
#include "leetcode/problems/minimize-the-total-price-of-the-trips.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2646 {

class MinimizeTheTotalPriceOfTheTripsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimizeTheTotalPriceOfTheTripsSolution solution;
};

TEST_P(MinimizeTheTotalPriceOfTheTripsTest, Example1) {
  int n = 4;
  vector<vector<int>> edges = {{0,1},{1,2},{1,3}};
  vector<int> price = {2,2,10,6};
  vector<vector<int>> trips = {{0,3},{2,1},{2,3}};
  EXPECT_EQ(23, solution.minimumTotalPrice(n, edges, price, trips));
}

TEST_P(MinimizeTheTotalPriceOfTheTripsTest, Example2) {
  int n = 2;
  vector<vector<int>> edges = {{0,1}};
  vector<int> price = {2,2};
  vector<vector<int>> trips = {{0,0}};
  EXPECT_EQ(1, solution.minimumTotalPrice(n, edges, price, trips));
}

TEST_P(MinimizeTheTotalPriceOfTheTripsTest, SingleNodeTrip) {
  int n = 3;
  vector<vector<int>> edges = {{0,1},{1,2}};
  vector<int> price = {4,4,4};
  vector<vector<int>> trips = {{1,1}};
  // 只经过节点1，减半后是2
  EXPECT_EQ(2, solution.minimumTotalPrice(n, edges, price, trips));
}

TEST_P(MinimizeTheTotalPriceOfTheTripsTest, AllNodesSamePrice) {
  int n = 3;
  vector<vector<int>> edges = {{0,1},{1,2}};
  vector<int> price = {10,10,10};
  vector<vector<int>> trips = {{0,2}};
  // 路径 0->1->2，可以选择节点0和2减半，或者只选节点1减半
  // 选0和2: 5 + 10 + 5 = 20
  // 选1: 10 + 5 + 10 = 25
  // 最优是 20
  EXPECT_EQ(20, solution.minimumTotalPrice(n, edges, price, trips));
}

TEST_P(MinimizeTheTotalPriceOfTheTripsTest, MultipleTripsSamePath) {
  int n = 3;
  vector<vector<int>> edges = {{0,1},{1,2}};
  vector<int> price = {4,4,4};
  vector<vector<int>> trips = {{0,2},{0,2},{0,2}};
  // 每个节点被经过3次
  // 0: 3*4=12, 减半后 3*2=6
  // 1: 3*4=12, 减半后 3*2=6
  // 2: 3*4=12, 减半后 3*2=6
  // 选0和2: 6+12+6=24 或 选1: 12+6+12=30，最优24
  EXPECT_EQ(24, solution.minimumTotalPrice(n, edges, price, trips));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimizeTheTotalPriceOfTheTripsTest,
    ::testing::ValuesIn(MinimizeTheTotalPriceOfTheTripsSolution().getStrategyNames()));

}  // namespace problem_2646
}  // namespace leetcode
