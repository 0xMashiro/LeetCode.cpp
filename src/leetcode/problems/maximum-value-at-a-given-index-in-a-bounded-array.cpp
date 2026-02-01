
#include "leetcode/problems/maximum-value-at-a-given-index-in-a-bounded-array.h"

namespace leetcode {
namespace problem_1802 {

// 辅助函数：计算从 start 开始向一侧递减（长度为 L）时的最小和
// 序列形如：start, start-1, start-2, ... 直到 1，然后补 1
// 注意：start 必须 >= 1，且序列中每个元素 >= 1
// 如果 start >= L: 序列为 start, start-1, ..., start-L+1（全部 >= 1）
// 如果 start < L: 序列为 start, start-1, ..., 1, 1, ..., 1（后面补 L-start 个 1）
static long long calculateSideSum(long long start, long long L) {
  if (start <= 0) {
    // 如果起始值小于等于0，只能全部填1
    return L;
  }
  if (start >= L) {
    // 等差数列求和：start + (start-1) + ... + (start-L+1)
    return (start + (start - L + 1)) * L / 2;
  } else {
    // start + (start-1) + ... + 1 + 1*(L-start) = start*(start+1)/2 + (L-start)
    return start * (start + 1) / 2 + (L - start);
  }
}

// 二分搜索解法
// 时间复杂度: O(log(maxSum)), 空间复杂度: O(1)
static int solution1(int n, int index, int maxSum) {
  long long left = 1, right = maxSum;
  int ans = 1;
  
  while (left <= right) {
    long long mid = left + (right - left) / 2;
    
    // 计算以 mid 为峰值时的最小总和
    // 左边（index 个元素）：从 index-1 到 0，从 mid-1 开始递减
    // 右边（n-index-1 个元素）：从 index+1 到 n-1，从 mid-1 开始递减
    long long leftSum = calculateSideSum(mid - 1, index);
    long long rightSum = calculateSideSum(mid - 1, n - index - 1);
    long long total = mid + leftSum + rightSum;
    
    if (total <= maxSum) {
      // mid 可行，尝试更大的值
      ans = mid;
      left = mid + 1;
    } else {
      // mid 太大，需要减小
      right = mid - 1;
    }
  }
  
  return ans;
}

MaximumValueAtAGivenIndexInABoundedArraySolution::MaximumValueAtAGivenIndexInABoundedArraySolution() {
  setMetaInfo({.id = 1802,
               .title = "Maximum Value at a Given Index in a Bounded Array",
               .url = "https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/"});
  registerStrategy("Binary Search", solution1);
}

int MaximumValueAtAGivenIndexInABoundedArraySolution::maxValue(int n, int index, int maxSum) {
  return getSolution()(n, index, maxSum);
}

}  // namespace problem_1802
}  // namespace leetcode
