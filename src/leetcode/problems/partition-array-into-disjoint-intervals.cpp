#include "leetcode/problems/partition-array-into-disjoint-intervals.h"

namespace leetcode {
namespace problem_915 {

// 预处理右侧最小值数组，然后一次遍历找分割点
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  
  // rightMin[i] 表示 nums[i..n-1] 中的最小值
  vector<int> rightMin(n);
  rightMin[n - 1] = nums[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    rightMin[i] = min(nums[i], rightMin[i + 1]);
  }
  
  // 从左向右遍历，维护 left 部分的最大值
  int leftMax = nums[0];
  for (int i = 0; i < n - 1; ++i) {
    leftMax = max(leftMax, nums[i]);
    // 检查在位置 i 分割是否满足条件
    // left = nums[0..i], right = nums[i+1..n-1]
    // 需要 leftMax <= rightMin[i+1]
    if (leftMax <= rightMin[i + 1]) {
      return i + 1;  // left 的长度为 i+1
    }
  }
  
  return n - 1;  // 不会执行到这里，因为题目保证有解
}

// 优化空间复杂度为 O(1) 的版本
// 维护当前 left 的最大值，以及一个候选的分割点
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution2(vector<int>& nums) {
  const int n = nums.size();
  int leftMax = nums[0];      // 当前 left 部分的最大值
  int maxSoFar = nums[0];     // 遍历过程中的全局最大值
  int partitionLen = 1;       // 当前候选的 left 长度
  
  for (int i = 1; i < n; ++i) {
    // 如果当前元素小于 leftMax，则必须将其纳入 left
    if (nums[i] < leftMax) {
      leftMax = maxSoFar;     // 更新 leftMax 为全局最大值
      partitionLen = i + 1;   // 更新分割点
    } else {
      // 否则可以留在 right，更新全局最大值
      maxSoFar = max(maxSoFar, nums[i]);
    }
  }
  
  return partitionLen;
}

PartitionArrayIntoDisjointIntervalsSolution::PartitionArrayIntoDisjointIntervalsSolution() {
  setMetaInfo({.id = 915,
               .title = "Partition Array into Disjoin Intervals",
               .url = "https://leetcode.com/problems/partition-array-into-disjoint-intervals/"});
  registerStrategy("Prefix-Suffix Array", solution1);
  registerStrategy("One Pass O(1)", solution2);
}

int PartitionArrayIntoDisjointIntervalsSolution::partitionDisjoint(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_915
}  // namespace leetcode
