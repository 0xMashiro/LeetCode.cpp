#include "leetcode/problems/analyze-organization-hierarchy.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3482 {

class AnalyzeOrganizationHierarchyTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  AnalyzeOrganizationHierarchySolution solution;
};

TEST_P(AnalyzeOrganizationHierarchyTest, Example1) {
  // 题目示例
  vector<Employee> employees = {
    {1, "Alice", nullopt, 12000, "Executive"},
    {2, "Bob", 1, 10000, "Sales"},
    {3, "Charlie", 1, 10000, "Engineering"},
    {4, "David", 2, 7500, "Sales"},
    {5, "Eva", 2, 7500, "Sales"},
    {6, "Frank", 3, 9000, "Engineering"},
    {7, "Grace", 3, 8500, "Engineering"},
    {8, "Hank", 4, 6000, "Sales"},
    {9, "Ivy", 6, 7000, "Engineering"},
    {10, "Judy", 6, 7000, "Engineering"}
  };
  
  vector<ResultRow> expected = {
    {1, "Alice", 1, 9, 84500},
    {3, "Charlie", 2, 4, 41500},
    {2, "Bob", 2, 3, 31000},
    {6, "Frank", 3, 2, 23000},
    {4, "David", 3, 1, 13500},
    {7, "Grace", 3, 0, 8500},
    {5, "Eva", 3, 0, 7500},
    {9, "Ivy", 4, 0, 7000},
    {10, "Judy", 4, 0, 7000},
    {8, "Hank", 4, 0, 6000}
  };
  
  vector<ResultRow> result = solution.analyzeOrganizationHierarchy(employees);
  EXPECT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i].employee_id, result[i].employee_id);
    EXPECT_EQ(expected[i].employee_name, result[i].employee_name);
    EXPECT_EQ(expected[i].level, result[i].level);
    EXPECT_EQ(expected[i].team_size, result[i].team_size);
    EXPECT_EQ(expected[i].budget, result[i].budget);
  }
}

TEST_P(AnalyzeOrganizationHierarchyTest, SingleCEO) {
  // 边界：只有 CEO 一个人
  vector<Employee> employees = {
    {1, "Alice", nullopt, 12000, "Executive"}
  };
  
  vector<ResultRow> expected = {
    {1, "Alice", 1, 0, 12000}
  };
  
  vector<ResultRow> result = solution.analyzeOrganizationHierarchy(employees);
  EXPECT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i].employee_id, result[i].employee_id);
    EXPECT_EQ(expected[i].level, result[i].level);
    EXPECT_EQ(expected[i].team_size, result[i].team_size);
    EXPECT_EQ(expected[i].budget, result[i].budget);
  }
}

TEST_P(AnalyzeOrganizationHierarchyTest, TwoLevels) {
  // 边界：两层结构
  vector<Employee> employees = {
    {1, "Alice", nullopt, 10000, "Executive"},
    {2, "Bob", 1, 5000, "Sales"},
    {3, "Charlie", 1, 6000, "Engineering"}
  };
  
  vector<ResultRow> result = solution.analyzeOrganizationHierarchy(employees);
  
  // Alice: level 1, team_size 2, budget 21000
  // Charlie: level 2, team_size 0, budget 6000 (higher salary than Bob)
  // Bob: level 2, team_size 0, budget 5000
  EXPECT_EQ(3, result.size());
  
  // 按 level 升序，budget 降序
  EXPECT_EQ(1, result[0].employee_id);  // Alice
  EXPECT_EQ(3, result[1].employee_id);  // Charlie (higher budget)
  EXPECT_EQ(2, result[2].employee_id);  // Bob
  
  EXPECT_EQ(1, result[0].level);
  EXPECT_EQ(2, result[1].level);
  EXPECT_EQ(2, result[2].level);
  
  EXPECT_EQ(2, result[0].team_size);
  EXPECT_EQ(0, result[1].team_size);
  EXPECT_EQ(0, result[2].team_size);
  
  EXPECT_EQ(21000, result[0].budget);
  EXPECT_EQ(6000, result[1].budget);
  EXPECT_EQ(5000, result[2].budget);
}

TEST_P(AnalyzeOrganizationHierarchyTest, ChainStructure) {
  // 边界：链式结构
  vector<Employee> employees = {
    {1, "A", nullopt, 1000, "D1"},
    {2, "B", 1, 900, "D2"},
    {3, "C", 2, 800, "D3"},
    {4, "D", 3, 700, "D4"}
  };
  
  vector<ResultRow> result = solution.analyzeOrganizationHierarchy(employees);
  
  EXPECT_EQ(4, result.size());
  
  // 验证层级
  EXPECT_EQ(1, result[0].level);  // A
  EXPECT_EQ(2, result[1].level);  // B
  EXPECT_EQ(3, result[2].level);  // C
  EXPECT_EQ(4, result[3].level);  // D
  
  // 验证 team_size
  EXPECT_EQ(3, result[0].team_size);  // A has B, C, D
  EXPECT_EQ(2, result[1].team_size);  // B has C, D
  EXPECT_EQ(1, result[2].team_size);  // C has D
  EXPECT_EQ(0, result[3].team_size);  // D has no one
  
  // 验证 budget
  EXPECT_EQ(3400, result[0].budget);  // 1000 + 900 + 800 + 700
  EXPECT_EQ(2400, result[1].budget);  // 900 + 800 + 700
  EXPECT_EQ(1500, result[2].budget);  // 800 + 700
  EXPECT_EQ(700, result[3].budget);   // 700
}

TEST_P(AnalyzeOrganizationHierarchyTest, SameBudgetTieBreaker) {
  // 边界：相同 budget 时按 name 排序
  vector<Employee> employees = {
    {1, "Alice", nullopt, 10000, "Executive"},
    {2, "Charlie", 1, 5000, "D1"},
    {3, "Bob", 1, 5000, "D2"},
    {4, "David", 1, 5000, "D3"}
  };
  
  vector<ResultRow> result = solution.analyzeOrganizationHierarchy(employees);
  
  // Alice level 1
  // Bob, Charlie, David all level 2 with same budget 5000
  // Should be sorted by name: Bob, Charlie, David
  EXPECT_EQ(1, result[0].employee_id);  // Alice
  EXPECT_EQ(3, result[1].employee_id);  // Bob (alphabetically first)
  EXPECT_EQ(2, result[2].employee_id);  // Charlie
  EXPECT_EQ(4, result[3].employee_id);  // David
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, AnalyzeOrganizationHierarchyTest,
    ::testing::ValuesIn(AnalyzeOrganizationHierarchySolution().getStrategyNames()));

}  // namespace problem_3482
}  // namespace leetcode
