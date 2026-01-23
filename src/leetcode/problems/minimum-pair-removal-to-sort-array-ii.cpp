#include "leetcode/problems/minimum-pair-removal-to-sort-array-ii.h"

namespace leetcode {
namespace problem_3510 {

// 贪心策略：每次合并最小和的相邻对，使用数组模拟双向链表和有序集合
// 时间复杂度: O(n log n)，空间复杂度: O(n)
static int solution1(vector<int>& nums) {
  int n = nums.size();
  if (n <= 1) return 0;
  
  // 转换为 long long 防止溢出
  vector<long long> val(n);
  for (int i = 0; i < n; ++i) val[i] = nums[i];
  
  // 双向链表
  vector<int> prev(n), next(n);
  for (int i = 0; i < n; ++i) {
    prev[i] = i - 1;
    next[i] = i + 1;
  }
  prev[0] = -1;
  next[n-1] = -1;
  
  // 节点是否存活
  vector<bool> alive(n, true);
  
  // 计算初始逆序对数量
  int inv_count = 0;
  for (int i = 0; i < n-1; ++i) {
    if (val[i] > val[i+1]) ++inv_count;
  }
  
  // 如果已经非递减，直接返回
  if (inv_count == 0) return 0;
  
  // 有序集合存储 (sum, left_index)，自动按 sum 升序，sum 相同时按 left_index 升序
  set<pair<long long, int>> pairs;
  
  // 记录每个左索引对应的和，用于删除
  vector<long long> pair_sum(n, 0);
  
  // 初始化相邻对
  for (int i = 0; i < n-1; ++i) {
    long long s = val[i] + val[i+1];
    pairs.insert({s, i});
    pair_sum[i] = s;
  }
  
  // 辅助函数：删除相邻对 (left, right)，其中 right = next[left]
  auto remove_pair = [&](int left) {
    if (left < 0 || left >= n || !alive[left]) return;
    int right = next[left];
    if (right == -1 || !alive[right]) return;
    // 查找并删除
    auto it = pairs.find({pair_sum[left], left});
    if (it != pairs.end()) {
      pairs.erase(it);
    }
  };
  
  // 辅助函数：添加相邻对 (left, right)
  auto add_pair = [&](int left) {
    if (left < 0 || left >= n || !alive[left]) return;
    int right = next[left];
    if (right == -1 || !alive[right]) return;
    long long s = val[left] + val[right];
    pairs.insert({s, left});
    pair_sum[left] = s;
  };
  
  int operations = 0;
  
  while (inv_count > 0 && !pairs.empty()) {
    // 取最小和的相邻对
    auto it = pairs.begin();
    long long sum = it->first;
    int left = it->second;
    pairs.erase(it);
    
    // 验证这对是否仍然有效
    if (!alive[left]) continue;
    int right = next[left];
    if (right == -1 || !alive[right] || prev[right] != left) continue;
    
    // 合并前删除所有受影响的相邻对
    int prev_left = prev[left];
    int next_right = next[right];
    
    if (prev_left != -1 && alive[prev_left]) {
      remove_pair(prev_left);
    }
    // (left, right) 已经从 pairs 中删除
    if (next_right != -1 && alive[next_right]) {
      remove_pair(right);
    }
    
    // 更新逆序计数
    if (prev_left != -1 && alive[prev_left] && val[prev_left] > val[left]) --inv_count;
    if (val[left] > val[right]) --inv_count;
    if (next_right != -1 && alive[next_right] && val[right] > val[next_right]) --inv_count;
    
    // 合并
    long long new_val = val[left] + val[right];
    val[left] = new_val;
    
    // 标记 right 为死亡
    alive[right] = false;
    
    // 更新链表连接
    next[left] = next_right;
    if (next_right != -1) prev[next_right] = left;
    
    // 合并后更新逆序计数
    if (prev_left != -1 && alive[prev_left] && val[prev_left] > new_val) ++inv_count;
    if (next_right != -1 && alive[next_right] && new_val > val[next_right]) ++inv_count;
    
    ++operations;
    
    // 添加新的相邻对
    if (prev_left != -1 && alive[prev_left]) {
      add_pair(prev_left);
    }
    if (next_right != -1 && alive[next_right]) {
      add_pair(left);
    }
  }
  
  return operations;
}

MinimumPairRemovalToSortArrayIiSolution::MinimumPairRemovalToSortArrayIiSolution() {
  setMetaInfo({.id = 3510,
               .title = "Minimum Pair Removal to Sort Array II",
               .url = "https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/"});
  registerStrategy("Greedy with Priority Queue", solution1);
}

int MinimumPairRemovalToSortArrayIiSolution::minimumPairRemoval(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3510
}  // namespace leetcode