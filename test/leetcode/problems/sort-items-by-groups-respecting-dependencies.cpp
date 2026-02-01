#include "leetcode/problems/sort-items-by-groups-respecting-dependencies.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1203 {

class SortItemsByGroupsRespectingDependenciesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SortItemsByGroupsRespectingDependenciesSolution solution;
};

// 辅助函数：验证结果是否满足约束
bool validateResult(int n, int m, const vector<int>& group, 
                   const vector<vector<int>>& beforeItems, 
                   const vector<int>& result) {
  if (result.empty()) return true;  // 无解时返回空列表是合法的
  
  // 检查长度
  if ((int)result.size() != n) return false;
  
  // 检查是否包含所有项目
  vector<bool> seen(n, false);
  for (int x : result) {
    if (x < 0 || x >= n || seen[x]) return false;
    seen[x] = true;
  }
  
  // 检查同一组的项目是否相邻
  vector<int> position(n);
  for (int i = 0; i < n; ++i) {
    position[result[i]] = i;
  }
  
  // 检查组内连续性
  vector<vector<int>> groupItems(m);
  int maxGroup = m - 1;
  for (int i = 0; i < n; ++i) {
    if (group[i] != -1) {
      groupItems[group[i]].push_back(i);
    } else {
      // 给无组项目分配虚拟组
      maxGroup++;
      groupItems.resize(maxGroup + 1);
      groupItems[maxGroup].push_back(i);
    }
  }
  
  for (const auto& items : groupItems) {
    if (items.size() <= 1) continue;
    vector<int> positions;
    for (int item : items) {
      positions.push_back(position[item]);
    }
    sort(positions.begin(), positions.end());
    for (size_t i = 1; i < positions.size(); ++i) {
      if (positions[i] != positions[i-1] + 1) return false;
    }
  }
  
  // 检查依赖关系
  for (int i = 0; i < n; ++i) {
    for (int before : beforeItems[i]) {
      if (position[before] >= position[i]) return false;
    }
  }
  
  return true;
}

TEST_P(SortItemsByGroupsRespectingDependenciesTest, Example1) {
  int n = 8, m = 2;
  vector<int> group = {-1, -1, 1, 0, 0, 1, 0, -1};
  vector<vector<int>> beforeItems = {{}, {6}, {5}, {6}, {3, 6}, {}, {}, {}};
  vector<int> result = solution.sortItems(n, m, group, beforeItems);
  
  EXPECT_FALSE(result.empty());
  EXPECT_TRUE(validateResult(n, m, group, beforeItems, result));
}

TEST_P(SortItemsByGroupsRespectingDependenciesTest, Example2) {
  int n = 8, m = 2;
  vector<int> group = {-1, -1, 1, 0, 0, 1, 0, -1};
  vector<vector<int>> beforeItems = {{}, {6}, {5}, {6}, {3}, {}, {4}, {}};
  vector<int> result = solution.sortItems(n, m, group, beforeItems);
  
  // 这个例子无解，应该返回空列表
  EXPECT_TRUE(result.empty());
}

TEST_P(SortItemsByGroupsRespectingDependenciesTest, SingleItem) {
  int n = 1, m = 1;
  vector<int> group = {0};
  vector<vector<int>> beforeItems = {{}};
  vector<int> result = solution.sortItems(n, m, group, beforeItems);
  
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0], 0);
}

TEST_P(SortItemsByGroupsRespectingDependenciesTest, NoDependencies) {
  int n = 4, m = 2;
  vector<int> group = {0, 0, 1, 1};
  vector<vector<int>> beforeItems = {{}, {}, {}, {}};
  vector<int> result = solution.sortItems(n, m, group, beforeItems);
  
  EXPECT_FALSE(result.empty());
  EXPECT_TRUE(validateResult(n, m, group, beforeItems, result));
}

TEST_P(SortItemsByGroupsRespectingDependenciesTest, AllNoGroup) {
  int n = 4, m = 1;
  vector<int> group = {-1, -1, -1, -1};
  vector<vector<int>> beforeItems = {{}, {0}, {1}, {2}};
  vector<int> result = solution.sortItems(n, m, group, beforeItems);
  
  EXPECT_FALSE(result.empty());
  EXPECT_TRUE(validateResult(n, m, group, beforeItems, result));
  // 检查顺序：应该是 0, 1, 2, 3
  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 1);
  EXPECT_EQ(result[2], 2);
  EXPECT_EQ(result[3], 3);
}

TEST_P(SortItemsByGroupsRespectingDependenciesTest, GroupCycle) {
  int n = 4, m = 2;
  vector<int> group = {0, 1, 1, 0};
  // 组0 -> 组1（项目1依赖项目0）
  // 组1 -> 组0（项目3依赖项目2）
  // 形成环：组0 -> 组1 -> 组0
  vector<vector<int>> beforeItems = {{}, {0}, {}, {2}};
  vector<int> result = solution.sortItems(n, m, group, beforeItems);
  
  // 组间有环，无解
  EXPECT_TRUE(result.empty());
}

TEST_P(SortItemsByGroupsRespectingDependenciesTest, ItemCycleInGroup) {
  int n = 3, m = 1;
  vector<int> group = {0, 0, 0};
  // 项目间形成环: 0 -> 1 -> 2 -> 0
  vector<vector<int>> beforeItems = {{2}, {0}, {1}};
  vector<int> result = solution.sortItems(n, m, group, beforeItems);
  
  // 组内有环，无解
  EXPECT_TRUE(result.empty());
}

TEST_P(SortItemsByGroupsRespectingDependenciesTest, SimpleChain) {
  int n = 4, m = 1;
  vector<int> group = {0, 0, 0, 0};
  vector<vector<int>> beforeItems = {{}, {0}, {1}, {2}};
  vector<int> result = solution.sortItems(n, m, group, beforeItems);
  
  EXPECT_FALSE(result.empty());
  EXPECT_TRUE(validateResult(n, m, group, beforeItems, result));
  // 应该是 0, 1, 2, 3
  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 1);
  EXPECT_EQ(result[2], 2);
  EXPECT_EQ(result[3], 3);
}

TEST_P(SortItemsByGroupsRespectingDependenciesTest, ComplexDependencies) {
  int n = 6, m = 3;
  vector<int> group = {0, 1, 2, 0, 1, 2};
  // 组内依赖和组间依赖混合
  vector<vector<int>> beforeItems = {
    {},      // 0: 无依赖
    {0},     // 1: 依赖 0（组0在组1前）
    {1},     // 2: 依赖 1（组1在组2前）
    {},      // 3: 无依赖
    {3},     // 4: 依赖 3（组0在组1前）
    {4}      // 5: 依赖 4（组1在组2前）
  };
  vector<int> result = solution.sortItems(n, m, group, beforeItems);
  
  EXPECT_FALSE(result.empty());
  EXPECT_TRUE(validateResult(n, m, group, beforeItems, result));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, 
    SortItemsByGroupsRespectingDependenciesTest,
    ::testing::ValuesIn(SortItemsByGroupsRespectingDependenciesSolution().getStrategyNames()));

}  // namespace problem_1203
}  // namespace leetcode
