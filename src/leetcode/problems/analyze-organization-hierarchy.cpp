#include "leetcode/problems/analyze-organization-hierarchy.h"

namespace leetcode {
namespace problem_3482 {

/**
 * 解决方案：使用 DFS 递归计算层级、团队大小和预算
 * 
 * 思路：
 * 1. 构建邻接表：manager_id -> 下属列表
 * 2. 找到 CEO（manager_id 为 null 的员工）
 * 3. 从 CEO 开始进行 DFS：
 *    - level：当前层级（CEO 为 1）
 *    - team_size：所有直接和间接下属的数量
 *    - budget：自己薪资 + 所有下属的 budget
 * 4. 按规则排序结果
 * 
 * 时间复杂度：O(n)，每个员工只访问一次
 * 空间复杂度：O(n)，存储邻接表和结果
 */
static vector<ResultRow> solution1(vector<Employee>& employees) {
  if (employees.empty()) return {};
  
  const int n = employees.size();
  
  // 构建从 employee_id 到 Employee 的映射
  unordered_map<int, const Employee*> emp_map;
  for (const auto& emp : employees) {
    emp_map[emp.employee_id] = &emp;
  }
  
  // 构建邻接表：manager_id -> 下属 id 列表
  unordered_map<int, vector<int>> children;
  int ceo_id = -1;
  for (const auto& emp : employees) {
    if (emp.manager_id.has_value()) {
      children[emp.manager_id.value()].push_back(emp.employee_id);
    } else {
      ceo_id = emp.employee_id;
    }
  }
  
  // 存储每个员工的信息：level, team_size, budget
  unordered_map<int, tuple<int, int, long long>> info;  // id -> (level, team_size, budget)
  
  // DFS 函数，返回 (team_size, budget)
  function<pair<int, long long>(int, int)> dfs = [&](int emp_id, int level) -> pair<int, long long> {
    const Employee* emp = emp_map[emp_id];
    long long budget = emp->salary;
    int team_size = 0;
    
    // 遍历所有下属
    if (children.count(emp_id)) {
      for (int child_id : children[emp_id]) {
        auto [child_team_size, child_budget] = dfs(child_id, level + 1);
        team_size += 1 + child_team_size;  // 1 是下属本身，child_team_size 是下属的下属
        budget += child_budget;
      }
    }
    
    info[emp_id] = {level, team_size, budget};
    return {team_size, budget};
  };
  
  // 从 CEO 开始 DFS
  if (ceo_id != -1) {
    dfs(ceo_id, 1);
  }
  
  // 构建结果
  vector<ResultRow> result;
  result.reserve(n);
  for (const auto& emp : employees) {
    auto [level, team_size, budget] = info[emp.employee_id];
    result.push_back({
      emp.employee_id,
      emp.employee_name,
      level,
      team_size,
      budget
    });
  }
  
  // 排序：level 升序，budget 降序，employee_name 升序
  sort(result.begin(), result.end(), [](const ResultRow& a, const ResultRow& b) {
    if (a.level != b.level) return a.level < b.level;
    if (a.budget != b.budget) return a.budget > b.budget;
    return a.employee_name < b.employee_name;
  });
  
  return result;
}

/**
 * 迭代解法：使用 BFS 计算层级，后序遍历计算团队大小和预算
 */
static vector<ResultRow> solution2(vector<Employee>& employees) {
  if (employees.empty()) return {};
  
  const int n = employees.size();
  
  // 构建从 employee_id 到 Employee 的映射
  unordered_map<int, const Employee*> emp_map;
  for (const auto& emp : employees) {
    emp_map[emp.employee_id] = &emp;
  }
  
  // 构建邻接表：manager_id -> 下属 id 列表
  unordered_map<int, vector<int>> children;
  int ceo_id = -1;
  for (const auto& emp : employees) {
    if (emp.manager_id.has_value()) {
      children[emp.manager_id.value()].push_back(emp.employee_id);
    } else {
      ceo_id = emp.employee_id;
    }
  }
  
  // 使用 BFS 计算层级
  unordered_map<int, int> level;  // id -> level
  if (ceo_id != -1) {
    queue<int> q;
    q.push(ceo_id);
    level[ceo_id] = 1;
    
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      
      if (children.count(cur)) {
        for (int child : children[cur]) {
          level[child] = level[cur] + 1;
          q.push(child);
        }
      }
    }
  }
  
  // 拓扑排序：按层级从高到低处理（后序遍历）
  // 先按层级分组
  unordered_map<int, vector<int>> level_groups;
  int max_level = 0;
  for (const auto& [id, lvl] : level) {
    level_groups[lvl].push_back(id);
    max_level = max(max_level, lvl);
  }
  
  // 从最低层级向上计算 team_size 和 budget
  unordered_map<int, int> team_size;  // id -> team_size
  unordered_map<int, long long> budget;  // id -> budget
  
  for (int lvl = max_level; lvl >= 1; --lvl) {
    for (int emp_id : level_groups[lvl]) {
      const Employee* emp = emp_map[emp_id];
      long long cur_budget = emp->salary;
      int cur_team_size = 0;
      
      if (children.count(emp_id)) {
        for (int child : children[emp_id]) {
          cur_team_size += 1 + team_size[child];
          cur_budget += budget[child];
        }
      }
      
      team_size[emp_id] = cur_team_size;
      budget[emp_id] = cur_budget;
    }
  }
  
  // 构建结果
  vector<ResultRow> result;
  result.reserve(n);
  for (const auto& emp : employees) {
    result.push_back({
      emp.employee_id,
      emp.employee_name,
      level[emp.employee_id],
      team_size[emp.employee_id],
      budget[emp.employee_id]
    });
  }
  
  // 排序：level 升序，budget 降序，employee_name 升序
  sort(result.begin(), result.end(), [](const ResultRow& a, const ResultRow& b) {
    if (a.level != b.level) return a.level < b.level;
    if (a.budget != b.budget) return a.budget > b.budget;
    return a.employee_name < b.employee_name;
  });
  
  return result;
}

AnalyzeOrganizationHierarchySolution::AnalyzeOrganizationHierarchySolution() {
  setMetaInfo({
    .id = 3482,
    .title = "Analyze Organization Hierarchy",
    .url = "https://leetcode.com/problems/analyze-organization-hierarchy/"
  });
  registerStrategy("DFS Recursive", solution1);
  registerStrategy("BFS + Topological", solution2);
}

vector<ResultRow> AnalyzeOrganizationHierarchySolution::analyzeOrganizationHierarchy(vector<Employee>& employees) {
  return getSolution()(employees);
}

}  // namespace problem_3482
}  // namespace leetcode
