
#include "leetcode/problems/get-the-size-of-a-dataframe.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2878 {

class GetTheSizeOfADataframeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  GetTheSizeOfADataframeSolution solution;
};

TEST_P(GetTheSizeOfADataframeTest, Example1) {
  // 示例 1: 10 行 5 列的 DataFrame
  vector<vector<string>> data = {
    {"846", "Mason", "21", "Forward", "RealMadrid"},
    {"749", "Riley", "30", "Winger", "Barcelona"},
    {"155", "Bob", "28", "Striker", "ManchesterUnited"},
    {"583", "Isabella", "32", "Goalkeeper", "Liverpool"},
    {"388", "Zachary", "24", "Midfielder", "BayernMunich"},
    {"883", "Ava", "23", "Defender", "Chelsea"},
    {"355", "Violet", "18", "Striker", "Juventus"},
    {"247", "Thomas", "27", "Striker", "ParisSaint-Germain"},
    {"761", "Jack", "33", "Midfielder", "ManchesterCity"},
    {"642", "Charlie", "36", "Center-back", "Arsenal"}
  };
  vector<string> columns = {"player_id", "name", "age", "position", "team"};
  DataFrame players(data, columns);
  
  vector<int> expected = {10, 5};
  vector<int> result = solution.getDataFrameSize(players);
  EXPECT_EQ(expected, result);
}

TEST_P(GetTheSizeOfADataframeTest, EmptyDataFrame) {
  // 边界: 空 DataFrame
  vector<vector<string>> data;
  vector<string> columns = {"col1", "col2"};
  DataFrame players(data, columns);
  
  vector<int> expected = {0, 2};
  vector<int> result = solution.getDataFrameSize(players);
  EXPECT_EQ(expected, result);
}

TEST_P(GetTheSizeOfADataframeTest, SingleRow) {
  // 边界: 单行 DataFrame
  vector<vector<string>> data = {{"1", "Alice", "25"}};
  vector<string> columns = {"id", "name", "age"};
  DataFrame players(data, columns);
  
  vector<int> expected = {1, 3};
  vector<int> result = solution.getDataFrameSize(players);
  EXPECT_EQ(expected, result);
}

TEST_P(GetTheSizeOfADataframeTest, SingleColumn) {
  // 边界: 单列 DataFrame
  vector<vector<string>> data = {{"a"}, {"b"}, {"c"}};
  vector<string> columns = {"value"};
  DataFrame players(data, columns);
  
  vector<int> expected = {3, 1};
  vector<int> result = solution.getDataFrameSize(players);
  EXPECT_EQ(expected, result);
}

TEST_P(GetTheSizeOfADataframeTest, OneByOne) {
  // 边界: 1x1 DataFrame
  vector<vector<string>> data = {{"only"}};
  vector<string> columns = {"col"};
  DataFrame players(data, columns);
  
  vector<int> expected = {1, 1};
  vector<int> result = solution.getDataFrameSize(players);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, GetTheSizeOfADataframeTest,
    ::testing::ValuesIn(GetTheSizeOfADataframeSolution().getStrategyNames()));

}  // namespace problem_2878
}  // namespace leetcode
