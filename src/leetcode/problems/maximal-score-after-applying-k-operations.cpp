#include "leetcode/problems/maximal-score-after-applying-k-operations.h"

namespace leetcode {
namespace problem_2530 {

// 贪心 + 最大堆
// 每次选择最大的元素，累加分数后将其替换为 ceil(val/3) 放回堆中
// 时间复杂度: O((n + k) log n), 空间复杂度: O(n)
static long long solution1(vector<int>& nums, int k) {
  // 使用最大堆，默认是最大堆
  priority_queue<long long> pq;
  
  // 将所有元素放入堆中，转换为 long long 避免溢出
  for (int num : nums) {
    pq.push(static_cast<long long>(num));
  }
  
  long long score = 0;
  
  // 执行 k 次操作
  for (int i = 0; i < k; ++i) {
    // 取出当前最大值
    long long val = pq.top();
    pq.pop();
    
    // 增加分数
    score += val;
    
    // 计算 ceil(val / 3) = (val + 2) / 3
    long long newVal = (val + 2) / 3;
    
    // 将新值放回堆中
    pq.push(newVal);
  }
  
  return score;
}

MaximalScoreAfterApplyingKOperationsSolution::MaximalScoreAfterApplyingKOperationsSolution() {
  setMetaInfo({.id = 2530,
               .title = "Maximal Score After Applying K Operations",
               .url = "https://leetcode.com/problems/maximal-score-after-applying-k-operations/"});
  registerStrategy("Greedy + Max Heap", solution1);
}

long long MaximalScoreAfterApplyingKOperationsSolution::maxKelements(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_2530
}  // namespace leetcode