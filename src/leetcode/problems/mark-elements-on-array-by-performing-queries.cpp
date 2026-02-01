#include "leetcode/problems/mark-elements-on-array-by-performing-queries.h"

namespace leetcode {
namespace problem_3080 {

/**
 * 解题思路：
 * 1. 使用优先队列（最小堆）存储未标记元素，按 (值, 索引) 排序
 * 2. 使用布尔数组标记已标记的元素
 * 3. 维护未标记元素的总和 sum
 * 
 * 对于每个查询 [index, k]：
 * - 首先标记 index 处的元素（如果未标记）
 * - 然后从优先队列中取出 k 个最小的未标记元素进行标记
 * - 记录当前未标记元素的和
 * 
 * 时间复杂度: O((n + m) * log n)，其中 n 是 nums 长度，m 是查询数量
 * 空间复杂度: O(n)
 */
static vector<long long> solution1(vector<int>& nums, vector<vector<int>>& queries) {
  const int n = nums.size();
  const int m = queries.size();
  
  // 计算初始总和
  long long sum = 0;
  for (int num : nums) {
    sum += num;
  }
  
  // 优先队列：按 (值, 索引) 排序，值小的优先，值相同则索引小的优先
  // 使用 greater 使最小元素在顶部
  using P = pair<int, int>;  // (值, 索引)
  priority_queue<P, vector<P>, greater<P>> pq;
  
  // 初始化优先队列
  for (int i = 0; i < n; ++i) {
    pq.push({nums[i], i});
  }
  
  // 标记数组
  vector<bool> marked(n, false);
  
  vector<long long> answer;
  answer.reserve(m);
  
  for (const auto& query : queries) {
    int index = query[0];
    int k = query[1];
    
    // 标记 index 处的元素（如果未标记）
    if (!marked[index]) {
      marked[index] = true;
      sum -= nums[index];
    }
    
    // 标记 k 个最小的未标记元素
    while (k > 0 && !pq.empty()) {
      auto [value, idx] = pq.top();
      pq.pop();
      
      // 跳过已经标记的元素（过期的堆顶元素）
      if (marked[idx]) {
        continue;
      }
      
      // 标记该元素
      marked[idx] = true;
      sum -= value;
      --k;
    }
    
    answer.push_back(sum);
  }
  
  return answer;
}

MarkElementsOnArrayByPerformingQueriesSolution::MarkElementsOnArrayByPerformingQueriesSolution() {
  setMetaInfo({
    .id = 3080,
    .title = "Mark Elements on Array by Performing Queries",
    .url = "https://leetcode.com/problems/mark-elements-on-array-by-performing-queries/"
  });
  registerStrategy("Priority Queue", solution1);
}

vector<long long> MarkElementsOnArrayByPerformingQueriesSolution::unmarkedSumArray(
    vector<int>& nums, vector<vector<int>>& queries) {
  return getSolution()(nums, queries);
}

}  // namespace problem_3080
}  // namespace leetcode
