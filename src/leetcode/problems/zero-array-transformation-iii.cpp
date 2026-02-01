#include "leetcode/problems/zero-array-transformation-iii.h"

namespace leetcode {
namespace problem_3362 {

// 检查是否可以用给定的查询使 nums 变为零数组
// 使用贪心策略：对于每个位置，选择能覆盖它且右端点最远的查询
static bool canTransform(vector<int>& nums, vector<vector<int>>& queries, int k) {
  int n = nums.size();
  int m = queries.size();
  
  // 保留前 m-k 个查询（按某种策略排序后的）
  // 这里我们尝试用所有查询，但限制使用数量
  
  // 按左端点分组存储查询的右端点
  vector<vector<int>> startAt(n);
  for (int i = 0; i < m - k; i++) {
    startAt[queries[i][0]].push_back(queries[i][1]);
  }
  
  // 优先队列（最大堆），存储当前可用查询的右端点
  priority_queue<int> pq;
  
  // diff[i] 表示位置 i 还需要多少覆盖
  vector<int> diff = nums;
  
  for (int i = 0; i < n; i++) {
    // 将所有从 i 开始的查询加入优先队列
    for (int r : startAt[i]) {
      pq.push(r);
    }
    
    // 移除已经过期的查询（右端点 < i）
    while (!pq.empty() && pq.top() < i) {
      pq.pop();
    }
    
    // 需要 diff[i] 个查询覆盖位置 i
    while (diff[i] > 0) {
      // 如果没有可用查询，返回失败
      if (pq.empty()) return false;
      
      // 使用一个查询，它可以覆盖从 i 到 pq.top() 的范围
      int r = pq.top();
      pq.pop();
      
      // 这个查询可以给 [i, r] 的每个位置减 1
      // 我们需要计算实际贡献：对于位置 i，减 1
      diff[i]--;
    }
  }
  
  return true;
}

// 另一种验证方法：差分数组 + 贪心
static bool check(vector<int>& nums, vector<vector<int>>& queries, int k) {
  int n = nums.size();
  int m = queries.size();
  int keep = m - k;  // 保留的查询数量
  
  if (keep < 0) return false;
  
  // 按左端点排序查询
  vector<pair<int, int>> sortedQueries;
  for (int i = 0; i < keep; i++) {
    sortedQueries.push_back({queries[i][0], queries[i][1]});
  }
  sort(sortedQueries.begin(), sortedQueries.end());
  
  // 差分数组
  vector<int> diff(n + 1, 0);
  int curr = 0;  // 当前覆盖次数
  int idx = 0;   // 当前处理的查询索引
  
  // 按右端点排序的优先队列（最大堆）
  priority_queue<int> available;
  
  for (int i = 0; i < n; i++) {
    // 添加所有从 i 开始的查询
    while (idx < keep && sortedQueries[idx].first <= i) {
      available.push(sortedQueries[idx].second);
      idx++;
    }
    
    // 计算当前位置的覆盖
    curr += diff[i];
    
    // 还需要多少覆盖
    int need = nums[i] - curr;
    
    while (need > 0) {
      // 找能覆盖到 i 或更远的查询
      while (!available.empty() && available.top() < i) {
        available.pop();
      }
      
      if (available.empty()) return false;
      
      // 使用这个查询
      int r = available.top();
      available.pop();
      
      // 在 r+1 处结束覆盖
      if (r + 1 < n) diff[r + 1]--;
      curr++;
      need--;
    }
  }
  
  return true;
}

// 主解决方案：二分搜索 + 贪心验证
static int solution(vector<int>& nums, vector<vector<int>>& queries) {
  int n = nums.size();
  int m = queries.size();
  
  // 首先检查总和：所有查询能提供的最大减法和
  // 每个查询最多给范围内每个位置减 1
  // 但实际上每个查询只能用一次
  
  // 二分搜索最大可移除数量
  int left = -1, right = m + 1;
  
  // 需要按某种策略排序查询，使得前面的查询更"有用"
  // 按左端点升序，左端点相同则按右端点降序（覆盖范围大的优先）
  sort(queries.begin(), queries.end(), [](const vector<int>& a, const vector<int>& b) {
    if (a[0] != b[0]) return a[0] < b[0];
    return a[1] > b[1];
  });
  
  while (left + 1 < right) {
    int mid = left + (right - left) / 2;
    if (check(nums, queries, mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }
  
  return left;
}

ZeroArrayTransformationIiiSolution::ZeroArrayTransformationIiiSolution() {
  setMetaInfo({.id = 3362,
               .title = "Zero Array Transformation III",
               .url = "https://leetcode.com/problems/zero-array-transformation-iii/"});
  registerStrategy("Binary Search + Greedy", solution);
}

int ZeroArrayTransformationIiiSolution::maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
  return getSolution()(nums, queries);
}

}  // namespace problem_3362
}  // namespace leetcode
