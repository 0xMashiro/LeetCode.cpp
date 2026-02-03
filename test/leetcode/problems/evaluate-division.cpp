#include "leetcode/problems/evaluate-division.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_399 {

class EvaluateDivisionTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  EvaluateDivisionSolution solution;
};

TEST_P(EvaluateDivisionTest, Example1) {
  vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}};
  vector<double> values = {2.0, 3.0};
  vector<vector<string>> queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
  vector<double> expected = {6.00000, 0.50000, -1.00000, 1.00000, -1.00000};
  
  vector<double> result = solution.calcEquation(equations, values, queries);
  
  ASSERT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_DOUBLE_EQ(expected[i], result[i]) << "Mismatch at index " << i;
  }
}

TEST_P(EvaluateDivisionTest, Example2) {
  vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
  vector<double> values = {1.5, 2.5, 5.0};
  vector<vector<string>> queries = {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
  vector<double> expected = {3.75000, 0.40000, 5.00000, 0.20000};
  
  vector<double> result = solution.calcEquation(equations, values, queries);
  
  ASSERT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_DOUBLE_EQ(expected[i], result[i]) << "Mismatch at index " << i;
  }
}

TEST_P(EvaluateDivisionTest, Example3) {
  vector<vector<string>> equations = {{"a", "b"}};
  vector<double> values = {0.5};
  vector<vector<string>> queries = {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}};
  vector<double> expected = {0.50000, 2.00000, -1.00000, -1.00000};
  
  vector<double> result = solution.calcEquation(equations, values, queries);
  
  ASSERT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_DOUBLE_EQ(expected[i], result[i]) << "Mismatch at index " << i;
  }
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, EvaluateDivisionTest,
    ::testing::ValuesIn(EvaluateDivisionSolution().getStrategyNames()));

}  // namespace problem_399
}  // namespace leetcode
