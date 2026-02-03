#include "leetcode/problems/maximum-number-of-ways-to-partition-an-array.h"

namespace leetcode {
namespace problem_2025 {

static int solution1(vector<int>& nums, int k) {
  const int n = nums.size();
  
  // 计算前缀和
  vector<long long> prefix(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i] + nums[i];
  }
  long long total = prefix[n];
  
  // 不修改的情况
  int ans = 0;
  if (total % 2 == 0) {
    long long half = total / 2;
    for (int i = 1; i < n; ++i) {
      if (prefix[i] == half) {
        ++ans;
      }
    }
  }
  
  // 枚举每个位置 i，将 nums[i] 改为 k
  // diff = k - nums[i], new_total = total + diff
  //
  // 关键：pivot 的左半部分是 nums[0..pivot-1]
  // - pivot <= i：左半部分 nums[0..pivot-1] 不包含 nums[i]，和 = prefix[pivot]
  // - pivot > i：左半部分 nums[0..pivot-1] 包含 nums[i]，和 = prefix[pivot] + diff
  //
  // 等式：左半部分和 = 右半部分和 = new_total - 左半部分和
  // - pivot <= i：prefix[pivot] = (total + diff) - prefix[pivot]
  //               => 2*prefix[pivot] = total + diff
  // - pivot > i：prefix[pivot] + diff = (total + diff) - (prefix[pivot] + diff)
  //               => 2*(prefix[pivot] + diff) = total + diff
  //               => 2*prefix[pivot] = total - diff
  
  // 哈希表存储 2*prefix[pivot]
  unordered_map<long long, int> left, right;  // left: pivot > i, right: pivot <= i
  
  // 初始化：所有 pivot 1..n-1 都在 left (表示 pivot > i，当 i=0 时)
  for (int pivot = 1; pivot < n; ++pivot) {
    ++left[2 * prefix[pivot]];
  }
  
  for (int i = 0; i < n; ++i) {
    long long diff = (long long)k - nums[i];
    
    long long target_right = total + diff;  // pivot <= i: 2*prefix = total + diff
    long long target_left = total - diff;   // pivot > i: 2*prefix = total - diff
    
    int cnt = left[target_left] + right[target_right];
    ans = max(ans, cnt);
    
    // 将 pivot = i+1 从 left 移到 right（如果 i+1 < n）
    // pivot = i+1 满足 pivot > i，但现在对于下一个 i+1，它满足 pivot <= i+1
    if (i + 1 < n) {
      long long p = 2 * prefix[i + 1];
      if (--left[p] == 0) left.erase(p);
      ++right[p];
    }
  }
  
  return ans;
}

MaximumNumberOfWaysToPartitionAnArraySolution::MaximumNumberOfWaysToPartitionAnArraySolution() {
  setMetaInfo({
    .id = 2025,
    .title = "Maximum Number of Ways to Partition an Array",
    .url = "https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/"
  });
  registerStrategy("Prefix Sum + Hash", solution1);
}

int MaximumNumberOfWaysToPartitionAnArraySolution::waysToPartition(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_2025
}  // namespace leetcode
