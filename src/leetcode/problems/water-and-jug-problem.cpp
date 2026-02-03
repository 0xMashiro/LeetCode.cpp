#include "leetcode/problems/water-and-jug-problem.h"

namespace leetcode {
namespace problem_365 {

// 数学解法：裴蜀定理（Bezout's Identity）
// 方程 ax + by = c 有整数解当且仅当 c 是 gcd(x, y) 的倍数
// 时间复杂度: O(log(min(x, y))), 空间复杂度: O(1)
static bool solution1(int x, int y, int target) {
  // 如果目标超过总容量，无法实现
  if (target > x + y) return false;
  
  // 如果目标为0，直接可以实现（两个壶都为空）
  if (target == 0) return true;
  
  // 计算 gcd(x, y)，使用辗转相除法
  auto gcd = [](int a, int b) {
    while (b != 0) {
      int temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  };
  
  return target % gcd(x, y) == 0;
}

// BFS 解法（状态搜索）
// 状态 (a, b) 表示第一个壶有 a 升，第二个壶有 b 升
// 时间复杂度: O(x * y), 空间复杂度: O(x * y)
static bool solution2(int x, int y, int target) {
  if (target > x + y) return false;
  if (target == 0) return true;
  
  // 使用 visited 数组记录已访问状态
  vector<vector<bool>> visited(x + 1, vector<bool>(y + 1, false));
  queue<pair<int, int>> q;
  
  q.push({0, 0});
  visited[0][0] = true;
  
  while (!q.empty()) {
    auto [a, b] = q.front();
    q.pop();
    
    // 检查是否达到目标
    if (a + b == target) return true;
    
    // 定义所有可能的操作
    vector<pair<int, int>> next_states;
    
    // 装满第一个壶
    next_states.push_back({x, b});
    // 装满第二个壶
    next_states.push_back({a, y});
    // 倒空第一个壶
    next_states.push_back({0, b});
    // 倒空第二个壶
    next_states.push_back({a, 0});
    // 从第一个壶倒入第二个壶
    int pour1 = min(a, y - b);
    next_states.push_back({a - pour1, b + pour1});
    // 从第二个壶倒入第一个壶
    int pour2 = min(b, x - a);
    next_states.push_back({a + pour2, b - pour2});
    
    for (const auto& [na, nb] : next_states) {
      if (!visited[na][nb]) {
        visited[na][nb] = true;
        q.push({na, nb});
      }
    }
  }
  
  return false;
}

WaterAndJugProblemSolution::WaterAndJugProblemSolution() {
  setMetaInfo({.id = 365,
               .title = "Water and Jug Problem",
               .url = "https://leetcode.com/problems/water-and-jug-problem/"});
  registerStrategy("Math (GCD)", solution1);
  registerStrategy("BFS", solution2);
}

bool WaterAndJugProblemSolution::canMeasureWater(int x, int y, int target) {
  return getSolution()(x, y, target);
}

}  // namespace problem_365
}  // namespace leetcode
