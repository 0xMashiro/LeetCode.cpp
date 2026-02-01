#include "leetcode/problems/ways-to-split-array-into-three-subarrays.h"

namespace leetcode {
namespace problem_1712 {

static constexpr int MOD = 1e9 + 7;

// 前缀和 + 二分查找
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  
  // 计算前缀和
  vector<long long> prefix(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i] + nums[i];
  }
  
  long long total = prefix[n];
  long long ans = 0;
  
  // 枚举左子数组的结束位置 i (left 为 [0, i])
  // i 的范围：至少留 2 个元素给 mid 和 right
  for (int i = 0; i < n - 2; ++i) {
    long long left_sum = prefix[i + 1];
    
    // mid 至少要有一个元素，所以 j 从 i+1 开始
    // right 至少要有一个元素，所以 j 最大到 n-2
    
    // 找到最小的 j，使得 prefix[j+1] >= 2 * left_sum
    // 即 mid_sum >= left_sum
    int lo = i + 1, hi = n - 1;
    int min_j = n - 1;  // j 是 mid 的结束位置，mid = [i+1, j]
    
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      long long mid_sum = prefix[mid + 1] - left_sum;
      if (mid_sum >= left_sum) {
        min_j = mid;
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }
    
    // 找到最大的 j，使得 mid_sum <= right_sum
    // prefix[j+1] - left_sum <= total - prefix[j+1]
    // 2 * prefix[j+1] <= total + left_sum
    // prefix[j+1] <= (total + left_sum) / 2
    lo = i + 1;
    hi = n - 2;  // right 至少一个元素，所以 j <= n-2
    int max_j = i;  // 初始化为无效值
    
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      long long mid_sum = prefix[mid + 1] - left_sum;
      long long right_sum = total - prefix[mid + 1];
      if (mid_sum <= right_sum) {
        max_j = mid;
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }
    
    if (max_j >= min_j) {
      ans += (max_j - min_j + 1);
      ans %= MOD;
    }
  }
  
  return static_cast<int>(ans);
}

// 优化版本：使用双指针
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution2(vector<int>& nums) {
  const int n = nums.size();
  
  // 计算前缀和
  vector<long long> prefix(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i] + nums[i];
  }
  
  long long total = prefix[n];
  long long ans = 0;
  
  // j 和 k 是双指针，表示 mid 结束位置的范围
  int j = 1;  // mid 的结束位置最小值
  int k = 1;  // mid 的结束位置最大值
  
  for (int i = 0; i < n - 2; ++i) {
    long long left_sum = prefix[i + 1];
    
    // j 至少为 i+1
    j = max(j, i + 1);
    
    // 找到最小的 j，使得 mid_sum >= left_sum
    // 即 prefix[j+1] >= 2 * left_sum
    while (j < n - 1 && prefix[j + 1] < 2 * left_sum) {
      ++j;
    }
    
    // 找到最大的 k，使得 mid_sum <= right_sum
    // 即 prefix[k+1] <= (total + left_sum) / 2
    k = max(k, j);
    while (k < n - 1 && prefix[k + 1] - left_sum <= total - prefix[k + 1]) {
      ++k;
    }
    
    // k 是第一个不满足条件的，所以最后一个满足条件的是 k-1
    if (k > j) {
      ans += (k - j);
      ans %= MOD;
    }
  }
  
  return static_cast<int>(ans);
}

WaysToSplitArrayIntoThreeSubarraysSolution::WaysToSplitArrayIntoThreeSubarraysSolution() {
  setMetaInfo({.id = 1712,
               .title = "Ways to Split Array Into Three Subarrays",
               .url = "https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/"});
  registerStrategy("Prefix Sum + Binary Search", solution1);
  registerStrategy("Prefix Sum + Two Pointers", solution2);
}

int WaysToSplitArrayIntoThreeSubarraysSolution::waysToSplit(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_1712
}  // namespace leetcode
