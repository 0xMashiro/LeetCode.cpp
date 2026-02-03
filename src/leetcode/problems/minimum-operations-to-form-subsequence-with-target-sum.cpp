#include "leetcode/problems/minimum-operations-to-form-subsequence-with-target-sum.h"

namespace leetcode {
namespace problem_2835 {

// 贪心 + 二进制位操作
// 核心思想：从低位到高位处理，优先使用当前位的数，不够则从高位借
// 时间复杂度: O(n + log(max(nums, target))), 空间复杂度: O(log(max(nums, target)))
static int solution(vector<int>& nums, int target) {
  // 统计每个2的幂的出现次数
  vector<int> cnt(32, 0);
  long long totalSum = 0;
  
  for (int num : nums) {
    int power = __builtin_ctz(num);  // 计算num是2的几次幂
    cnt[power]++;
    totalSum += num;
  }
  
  // 如果总和不够，直接返回-1
  if (totalSum < target) {
    return -1;
  }
  
  int operations = 0;
  
  for (int i = 0; i < 31; i++) {
    // 检查target的第i位是否为1
    if ((target >> i) & 1) {
      if (cnt[i] > 0) {
        // 当前位有数，直接用掉一个
        cnt[i]--;
      } else {
        // 当前位没有，需要从更高位借
        int j = i + 1;
        // 找到最近的有count的位
        while (j < 31 && cnt[j] == 0) {
          j++;
        }
        
        if (j >= 31) {
          return -1;  // 不可能的情况
        }
        
        // 从j位借一个，一路拆分到i位
        cnt[j]--;
        // 从j拆分到i需要(j-i)次操作
        // 每次拆分把一个2^k变成两个2^(k-1)
        for (int k = j - 1; k >= i; k--) {
          cnt[k]++;
          operations++;
        }
        // 用掉i位的一个
        cnt[i]--;
      }
    }
    
    // 当前位剩余的数，两个可以等效为一个更高位的
    // 用于后续位的判断
    cnt[i + 1] += cnt[i] / 2;
  }
  
  return operations;
}

MinimumOperationsToFormSubsequenceWithTargetSumSolution::MinimumOperationsToFormSubsequenceWithTargetSumSolution() {
  setMetaInfo({.id = 2835, 
               .title = "Minimum Operations to Form Subsequence With Target Sum", 
               .url = "https://leetcode.com/problems/minimum-operations-to-form-subsequence-with-target-sum/"});
  registerStrategy("Greedy Bit Manipulation", solution);
}

int MinimumOperationsToFormSubsequenceWithTargetSumSolution::minOperations(vector<int>& nums, int target) {
  return getSolution()(nums, target);
}

}  // namespace problem_2835
}  // namespace leetcode
