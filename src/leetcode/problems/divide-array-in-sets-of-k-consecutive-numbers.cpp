#include "leetcode/problems/divide-array-in-sets-of-k-consecutive-numbers.h"

namespace leetcode {
namespace problem_1296 {

// 贪心算法 + 有序映射
// 1. 统计每个数字出现次数
// 2. 从小到大遍历，每次尝试构造 k 个连续数字的组
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static bool solution(vector<int>& nums, int k) {
  int n = nums.size();
  // 如果总数不能被 k 整除，无法分组
  if (n % k != 0) {
    return false;
  }
  
  // 统计每个数字出现次数
  map<int, int> count;
  for (int num : nums) {
    count[num]++;
  }
  
  // 贪心：从小到大处理每个数字
  for (auto& [num, cnt] : count) {
    if (cnt == 0) continue;  // 该数字已用完
    
    // 需要以 num 为起点构造 cnt 个长度为 k 的连续序列
    // 检查并消耗 num+1, num+2, ..., num+k-1
    for (int i = 1; i < k; i++) {
      int next_num = num + i;
      if (count.find(next_num) == count.end() || count[next_num] < cnt) {
        // 下一个连续数字不存在或数量不足
        return false;
      }
      count[next_num] -= cnt;
    }
  }
  
  return true;
}

DivideArrayInSetsOfKConsecutiveNumbersSolution::DivideArrayInSetsOfKConsecutiveNumbersSolution() {
  setMetaInfo({
    .id = 1296,
    .title = "Divide Array in Sets of K Consecutive Numbers",
    .url = "https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/"
  });
  registerStrategy("Greedy + Map", solution);
}

bool DivideArrayInSetsOfKConsecutiveNumbersSolution::isPossibleDivide(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_1296
}  // namespace leetcode
