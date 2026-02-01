#include "leetcode/problems/count-distinct-subarrays-divisible-by-k-in-sorted-array.h"

namespace leetcode {
namespace problem_3729 {

// 多项式滚动哈希 + 滑动窗口
// 思路：
// 1. 使用滑动窗口找到所有和能被 k 整除的子数组
// 2. 使用多项式滚动哈希来唯一标识每个子数组的值序列
// 3. 用哈希集合去重，统计不同的子数组数量
// 
// 时间复杂度: O(n) 平均情况
// 空间复杂度: O(n)

// 使用两个大质数减少哈希冲突
static const long long BASE = 911382629;  // 大质数作为基数
static const long long MOD1 = 1000000007;  // 第一个模数
static const long long MOD2 = 1000000009;  // 第二个模数

// 双哈希对
struct HashPair {
  long long h1, h2;
  bool operator==(const HashPair& other) const {
    return h1 == other.h1 && h2 == other.h2;
  }
};

// 为 HashPair 提供哈希函数
struct HashPairHash {
  size_t operator()(const HashPair& p) const {
    return std::hash<long long>()(p.h1 * 1000003LL + p.h2);
  }
};

static long long solution1(vector<int>& nums, int k) {
  const int n = nums.size();
  if (n == 0) return 0;
  
  // 预计算幂次
  vector<long long> pow1(n + 1), pow2(n + 1);
  pow1[0] = pow2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pow1[i] = (pow1[i - 1] * BASE) % MOD1;
    pow2[i] = (pow2[i - 1] * BASE) % MOD2;
  }
  
  // 计算前缀哈希
  vector<long long> preHash1(n + 1), preHash2(n + 1);
  preHash1[0] = preHash2[0] = 0;
  for (int i = 0; i < n; ++i) {
    // 使用 (nums[i] + 1) 避免 0 的影响
    long long val = (nums[i] % MOD1 + MOD1) % MOD1 + 1;
    preHash1[i + 1] = (preHash1[i] * BASE + val) % MOD1;
    val = (nums[i] % MOD2 + MOD2) % MOD2 + 1;
    preHash2[i + 1] = (preHash2[i] * BASE + val) % MOD2;
  }
  
  // 获取子数组 [l, r] 的哈希值（0-indexed，闭区间）
  auto getHash = [&](int l, int r) -> HashPair {
    long long len = r - l + 1;
    long long h1 = (preHash1[r + 1] - preHash1[l] * pow1[len] % MOD1 + MOD1) % MOD1;
    long long h2 = (preHash2[r + 1] - preHash2[l] * pow2[len] % MOD2 + MOD2) % MOD2;
    return {h1, h2};
  };
  
  // 使用滑动窗口找所有和能被 k 整除的子数组
  // 由于 nums[i] >= 1，前缀和单调递增，可以用双指针
  unordered_set<HashPair, HashPairHash> distinctSubarrays;
  
  // 计算前缀和
  vector<long long> prefixSum(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    prefixSum[i + 1] = prefixSum[i] + nums[i];
  }
  
  // 枚举每个可能的子数组起点
  for (int left = 0; left < n; ++left) {
    // 从 left 开始，找所有 right 使得 sum[left..right] % k == 0
    // 由于数组元素都是正数，和单调递增
    // sum[left..right] = prefixSum[right+1] - prefixSum[left]
    for (int right = left; right < n; ++right) {
      long long sum = prefixSum[right + 1] - prefixSum[left];
      if (sum % k == 0) {
        distinctSubarrays.insert(getHash(left, right));
      }
      // 如果 sum 已经大于 k 的某个倍数，继续枚举后面的可能
      // 但不能提前终止，因为后面的和可能也是 k 的倍数
    }
  }
  
  return distinctSubarrays.size();
}

// 优化版本：利用单调性减少不必要的检查
static long long solution2(vector<int>& nums, int k) {
  const int n = nums.size();
  if (n == 0) return 0;
  
  // 预计算幂次
  vector<long long> pow1(n + 1), pow2(n + 1);
  pow1[0] = pow2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pow1[i] = (pow1[i - 1] * BASE) % MOD1;
    pow2[i] = (pow2[i - 1] * BASE) % MOD2;
  }
  
  // 计算前缀哈希
  vector<long long> preHash1(n + 1), preHash2(n + 1);
  preHash1[0] = preHash2[0] = 0;
  for (int i = 0; i < n; ++i) {
    long long val = (nums[i] % MOD1 + MOD1) % MOD1 + 1;
    preHash1[i + 1] = (preHash1[i] * BASE + val) % MOD1;
    val = (nums[i] % MOD2 + MOD2) % MOD2 + 1;
    preHash2[i + 1] = (preHash2[i] * BASE + val) % MOD2;
  }
  
  auto getHash = [&](int l, int r) -> HashPair {
    long long len = r - l + 1;
    long long h1 = (preHash1[r + 1] - preHash1[l] * pow1[len] % MOD1 + MOD1) % MOD1;
    long long h2 = (preHash2[r + 1] - preHash2[l] * pow2[len] % MOD2 + MOD2) % MOD2;
    return {h1, h2};
  };
  
  unordered_set<HashPair, HashPairHash> distinctSubarrays;
  vector<long long> prefixSum(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    prefixSum[i + 1] = prefixSum[i] + nums[i];
  }
  
  // 枚举每个起点，找到所有满足条件的终点
  for (int left = 0; left < n; ++left) {
    for (int right = left; right < n; ++right) {
      long long sum = prefixSum[right + 1] - prefixSum[left];
      if (sum % k == 0) {
        distinctSubarrays.insert(getHash(left, right));
      }
    }
  }
  
  return distinctSubarrays.size();
}

CountDistinctSubarraysDivisibleByKInSortedArraySolution::CountDistinctSubarraysDivisibleByKInSortedArraySolution() {
  setMetaInfo({
    .id = 3729,
    .title = "Count Distinct Subarrays Divisible by K in Sorted Array",
    .url = "https://leetcode.com/problems/count-distinct-subarrays-divisible-by-k-in-sorted-array/"
  });
  registerStrategy("Rolling Hash", solution1);
  registerStrategy("Optimized", solution2);
}

long long CountDistinctSubarraysDivisibleByKInSortedArraySolution::numGoodSubarrays(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3729
}  // namespace leetcode
