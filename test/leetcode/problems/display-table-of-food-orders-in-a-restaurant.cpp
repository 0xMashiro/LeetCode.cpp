#include "leetcode/problems/display-table-of-food-orders-in-a-restaurant.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1418 {

class DisplayTableOfFoodOrdersInARestaurantTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DisplayTableOfFoodOrdersInARestaurantSolution solution;
};

TEST_P(DisplayTableOfFoodOrdersInARestaurantTest, Example1) {
  vector<vector<string>> orders = {
    {"David", "3", "Ceviche"},
    {"Corina", "10", "Beef Burrito"},
    {"David", "3", "Fried Chicken"},
    {"Carla", "5", "Water"},
    {"Carla", "5", "Ceviche"},
    {"Rous", "3", "Ceviche"}
  };
  vector<vector<string>> expected = {
    {"Table", "Beef Burrito", "Ceviche", "Fried Chicken", "Water"},
    {"3", "0", "2", "1", "0"},
    {"5", "0", "1", "0", "1"},
    {"10", "1", "0", "0", "0"}
  };
  EXPECT_EQ(expected, solution.displayTable(orders));
}

TEST_P(DisplayTableOfFoodOrdersInARestaurantTest, Example2) {
  vector<vector<string>> orders = {
    {"James", "12", "Fried Chicken"},
    {"Ratesh", "12", "Fried Chicken"},
    {"Amadeus", "12", "Fried Chicken"},
    {"Adam", "1", "Canadian Waffles"},
    {"Brianna", "1", "Canadian Waffles"}
  };
  vector<vector<string>> expected = {
    {"Table", "Canadian Waffles", "Fried Chicken"},
    {"1", "2", "0"},
    {"12", "0", "3"}
  };
  EXPECT_EQ(expected, solution.displayTable(orders));
}

TEST_P(DisplayTableOfFoodOrdersInARestaurantTest, Example3) {
  vector<vector<string>> orders = {
    {"Laura", "2", "Bean Burrito"},
    {"Jhon", "2", "Beef Burrito"},
    {"Melissa", "2", "Soda"}
  };
  vector<vector<string>> expected = {
    {"Table", "Bean Burrito", "Beef Burrito", "Soda"},
    {"2", "1", "1", "1"}
  };
  EXPECT_EQ(expected, solution.displayTable(orders));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DisplayTableOfFoodOrdersInARestaurantTest,
    ::testing::ValuesIn(DisplayTableOfFoodOrdersInARestaurantSolution().getStrategyNames()));

}  // namespace problem_1418
}  // namespace leetcode
