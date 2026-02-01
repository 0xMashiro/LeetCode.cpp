#include "leetcode/problems/sort-the-people.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2418 {

class SortThePeopleTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SortThePeopleSolution solution;
};

TEST_P(SortThePeopleTest, Example1) {
  vector<string> names = {"Mary", "John", "Emma"};
  vector<int> heights = {180, 165, 170};
  vector<string> expected = {"Mary", "Emma", "John"};
  EXPECT_EQ(expected, solution.sortPeople(names, heights));
}

TEST_P(SortThePeopleTest, Example2) {
  vector<string> names = {"Alice", "Bob", "Bob"};
  vector<int> heights = {155, 185, 150};
  vector<string> expected = {"Bob", "Alice", "Bob"};
  EXPECT_EQ(expected, solution.sortPeople(names, heights));
}

TEST_P(SortThePeopleTest, SingleElement) {
  vector<string> names = {"Alice"};
  vector<int> heights = {150};
  vector<string> expected = {"Alice"};
  EXPECT_EQ(expected, solution.sortPeople(names, heights));
}

TEST_P(SortThePeopleTest, TwoElements) {
  vector<string> names = {"Short", "Tall"};
  vector<int> heights = {150, 200};
  vector<string> expected = {"Tall", "Short"};
  EXPECT_EQ(expected, solution.sortPeople(names, heights));
}

TEST_P(SortThePeopleTest, ReverseOrder) {
  vector<string> names = {"A", "B", "C", "D"};
  vector<int> heights = {100, 200, 300, 400};
  vector<string> expected = {"D", "C", "B", "A"};
  EXPECT_EQ(expected, solution.sortPeople(names, heights));
}

TEST_P(SortThePeopleTest, AlreadySorted) {
  vector<string> names = {"Tall", "Medium", "Short"};
  vector<int> heights = {300, 200, 100};
  vector<string> expected = {"Tall", "Medium", "Short"};
  EXPECT_EQ(expected, solution.sortPeople(names, heights));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SortThePeopleTest,
    ::testing::ValuesIn(SortThePeopleSolution().getStrategyNames()));

}  // namespace problem_2418
}  // namespace leetcode
