#include "leetcode/problems/display-the-first-three-rows.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2879 {

class DisplayTheFirstThreeRowsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DisplayTheFirstThreeRowsSolution solution;
};

TEST_P(DisplayTheFirstThreeRowsTest, Example1) {
  vector<Employee> employees = {
      {3, "Bob", "Operations", 48675},
      {90, "Alice", "Sales", 11096},
      {9, "Tatiana", "Engineering", 33805},
      {60, "Annabelle", "InformationTechnology", 37678},
      {49, "Jonathan", "HumanResources", 23793},
      {43, "Khaled", "Administration", 40454}
  };
  
  vector<Employee> expected = {
      {3, "Bob", "Operations", 48675},
      {90, "Alice", "Sales", 11096},
      {9, "Tatiana", "Engineering", 33805}
  };
  
  vector<Employee> result = solution.selectFirstThreeRows(employees);
  
  EXPECT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i].employee_id, result[i].employee_id);
    EXPECT_EQ(expected[i].name, result[i].name);
    EXPECT_EQ(expected[i].department, result[i].department);
    EXPECT_EQ(expected[i].salary, result[i].salary);
  }
}

TEST_P(DisplayTheFirstThreeRowsTest, LessThanThreeRows) {
  // 测试少于3行的情况
  vector<Employee> employees = {
      {1, "John", "IT", 50000},
      {2, "Jane", "HR", 60000}
  };
  
  vector<Employee> result = solution.selectFirstThreeRows(employees);
  
  EXPECT_EQ(2, result.size());
  EXPECT_EQ(1, result[0].employee_id);
  EXPECT_EQ(2, result[1].employee_id);
}

TEST_P(DisplayTheFirstThreeRowsTest, EmptyInput) {
  // 测试空输入
  vector<Employee> employees;
  
  vector<Employee> result = solution.selectFirstThreeRows(employees);
  
  EXPECT_TRUE(result.empty());
}

TEST_P(DisplayTheFirstThreeRowsTest, ExactlyThreeRows) {
  // 测试正好3行
  vector<Employee> employees = {
      {1, "A", "Dept1", 100},
      {2, "B", "Dept2", 200},
      {3, "C", "Dept3", 300}
  };
  
  vector<Employee> result = solution.selectFirstThreeRows(employees);
  
  EXPECT_EQ(3, result.size());
  EXPECT_EQ(1, result[0].employee_id);
  EXPECT_EQ(2, result[1].employee_id);
  EXPECT_EQ(3, result[2].employee_id);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DisplayTheFirstThreeRowsTest,
    ::testing::ValuesIn(DisplayTheFirstThreeRowsSolution().getStrategyNames()));

}  // namespace problem_2879
}  // namespace leetcode