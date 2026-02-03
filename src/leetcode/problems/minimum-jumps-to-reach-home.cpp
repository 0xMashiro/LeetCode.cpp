
#include "leetcode/problems/minimum-jumps-to-reach-home.h"

namespace leetcode {
namespace problem_1654 {

// BFS 最短路径
// 状态: (当前位置, 上一步是否向后跳)
// 时间复杂度: O(上界), 空间复杂度: O(上界)
static int solution1(vector<int>& forbidden, int a, int b, int x) {
  unordered_set<int> forbid(forbidden.begin(), forbidden.end());
  
  // 计算上界：max(forbidden) + a + b + x
  // 这个上界足够覆盖所有可能的有效路径
  int max_forbid = 0;
  for (int pos : forbidden) {
    max_forbid = max(max_forbid, pos);
  }
  int upper_bound = max_forbid + a + b + max(x, a + b);
  
  // BFS: queue 存储 {当前位置, 上一步是否向后跳}
  // visited[pos][0] 表示向前跳到 pos 是否访问过
  // visited[pos][1] 表示向后跳到 pos 是否访问过
  vector<vector<bool>> visited(upper_bound + 1, vector<bool>(2, false));
  queue<tuple<int, int, bool>> q;  // {位置, 步数, 上一步是否向后}
  
  q.push({0, 0, false});
  visited[0][0] = true;
  
  while (!q.empty()) {
    auto [pos, steps, went_back] = q.front();
    q.pop();
    
    // 到达目标
    if (pos == x) {
      return steps;
    }
    
    // 尝试向前跳 (总是允许)
    int next_forward = pos + a;
    if (next_forward <= upper_bound && 
        !forbid.count(next_forward) && 
        !visited[next_forward][0]) {
      visited[next_forward][0] = true;
      q.push({next_forward, steps + 1, false});
    }
    
    // 尝试向后跳 (只有上一步不是向后跳时才允许)
    if (!went_back) {
      int next_backward = pos - b;
      if (next_backward >= 0 && 
          !forbid.count(next_backward) && 
          !visited[next_backward][1]) {
        visited[next_backward][1] = true;
        q.push({next_backward, steps + 1, true});
      }
    }
  }
  
  return -1;  // 无法到达
}

MinimumJumpsToReachHomeSolution::MinimumJumpsToReachHomeSolution() {
  setMetaInfo({.id = 1654,
               .title = "Minimum Jumps to Reach Home",
               .url = "https://leetcode.com/problems/minimum-jumps-to-reach-home/"});
  registerStrategy("BFS", solution1);
}

int MinimumJumpsToReachHomeSolution::minimumJumps(vector<int>& forbidden, int a, int b, int x) {
  return getSolution()(forbidden, a, b, x);
}

}  // namespace problem_1654
}  // namespace leetcode
