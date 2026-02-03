#include "leetcode/problems/shortest-subarray-to-be-removed-to-make-array-sorted.h"

namespace leetcode {
namespace problem_1574 {

// 双指针法：找左侧非递减前缀和右侧非递减后缀，尝试连接
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution(vector<int>& arr) {
  const int n = arr.size();
  
  // 找左侧非递减前缀的末尾
  int left = 0;
  while (left + 1 < n && arr[left] <= arr[left + 1]) {
    ++left;
  }
  
  // 如果整个数组已经有序
  if (left == n - 1) {
    return 0;
  }
  
  // 找右侧非递减后缀的开头
  int right = n - 1;
  while (right > 0 && arr[right - 1] <= arr[right]) {
    --right;
  }
  
  // 情况1：移除左侧，只保留右侧后缀
  // 情况2：移除右侧，只保留左侧前缀
  int result = min(n - left - 1, right);
  
  // 情况3：尝试连接左右两部分
  // 左指针 i 从 0 到 left，右指针 j 从 right 到 n-1
  // 找满足 arr[i] <= arr[j] 的位置
  int i = 0, j = right;
  while (i <= left && j < n) {
    if (arr[i] <= arr[j]) {
      // 可以连接，计算需要移除的长度
      result = min(result, j - i - 1);
      ++i;
    } else {
      // arr[i] > arr[j]，需要增大 j
      ++j;
    }
  }
  
  return result;
}

ShortestSubarrayToBeRemovedToMakeArraySortedSolution::ShortestSubarrayToBeRemovedToMakeArraySortedSolution() {
  setMetaInfo({.id = 1574,
               .title = "Shortest Subarray to be Removed to Make Array Sorted",
               .url = "https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/"});
  registerStrategy("Two Pointer", solution);
}

int ShortestSubarrayToBeRemovedToMakeArraySortedSolution::findLengthOfShortestSubarray(vector<int>& arr) {
  return getSolution()(arr);
}

}  // namespace problem_1574
}  // namespace leetcode
