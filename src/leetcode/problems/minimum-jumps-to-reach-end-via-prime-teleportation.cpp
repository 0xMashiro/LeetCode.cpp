#include "leetcode/problems/minimum-jumps-to-reach-end-via-prime-teleportation.h"

#include <queue>

namespace leetcode {
namespace problem_3629 {

// 本题核心解法：BFS + 质数分类剪枝
//
// 为什么只有这一种合理思路？
// - 边权均为 1 → BFS 即最短路径，不需要 Dijkstra
// - 存在向后移动 (i-1)，不是 DAG，DP 不可行
// - 朴素传送建边 O(n?) 会超时，必须用质数分类懒展开
//
// 算法步骤：
// 1. 用 SPF 筛预处理 [1 .. max(nums)]，O(maxVal log log maxVal)
// 2. 对每个 nums[i] 做质因子分解，将 i 加入每个质因子 p 的列表
// 3. BFS 从 0 出发，遇到质数 p 时，将其列表中的全部未访问节点入队，然后清空列表（剪枝）
//
// 时间复杂度: O(n log MAX_VAL + MAX_VAL log log MAX_VAL)
// 空间复杂度: O(n + MAX_VAL)
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  if (n == 1) return 0;  // 已经在终点

  // ---- 1. 预处理 SPF（最小质因子） ----
  int max_val = 0;
  for (int x : nums)
    if (x > max_val) max_val = x;

  vector<int> spf(max_val + 1);
  for (int i = 0; i <= max_val; ++i) spf[i] = i;
  for (int i = 2; i * i <= max_val; ++i) {
    if (spf[i] == i) {  // i 是质数
      for (int j = i * i; j <= max_val; j += i) {
        if (spf[j] == j) spf[j] = i;
      }
    }
  }

  // ---- 2. 建立 质数 p → 下标 j（满足 p | nums[j]）的映射 ----
  // 注意：同一个下标可能出现在多个质数的列表中
  unordered_map<int, vector<int>> prime_to_indices;
  for (int i = 0; i < n; ++i) {
    int val = nums[i];
    if (val == 1) continue;
    int last_p = 0;
    while (val > 1) {
      int p = spf[val];
      if (p != last_p) {           // 去重：同一个质因子只加一次
        prime_to_indices[p].push_back(i);
        last_p = p;
      }
      val /= p;
    }
  }

  // ---- 3. BFS ----
  vector<int> dist(n, -1);
  queue<int> q;
  dist[0] = 0;
  q.push(0);

  while (!q.empty()) {
    int i = q.front();
    q.pop();
    int d = dist[i];

    if (i == n - 1) return d;  // 已到终点，BFS 保证首次即最短

    // 3a. 相邻移动
    if (i > 0 && dist[i - 1] == -1) {
      dist[i - 1] = d + 1;
      q.push(i - 1);
    }
    if (i + 1 < n && dist[i + 1] == -1) {
      dist[i + 1] = d + 1;
      q.push(i + 1);
    }

    // 3b. 质数传送
    int val = nums[i];
    if (val > 1 && spf[val] == val) {  // nums[i] 是质数
      auto it = prime_to_indices.find(val);
      if (it != prime_to_indices.end()) {
        for (int j : it->second) {
          if (j != i && dist[j] == -1) {
            dist[j] = d + 1;
            q.push(j);
          }
        }
        // 关键剪枝：该质数的所有可传送目标已入队（最短距离已确定）
        // 后续再遇到该质数无需重复处理
        prime_to_indices.erase(it);
      }
    }
  }

  // 理论上总能通过相邻移动到达，不会走到这里
  return -1;
}

MinimumJumpsToReachEndViaPrimeTeleportationSolution::
    MinimumJumpsToReachEndViaPrimeTeleportationSolution() {
  setMetaInfo({.id = 3629,
               .title = "Minimum Jumps to Reach End via Prime Teleportation",
               .url = "https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/"});
  // 本题结构唯一合理解为 BFS + 质数分类剪枝，无明显多解
  registerStrategy({.name = "BFS + Prime Factorization"}, solution1);
}

int MinimumJumpsToReachEndViaPrimeTeleportationSolution::minJumps(
    vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3629
}  // namespace leetcode
