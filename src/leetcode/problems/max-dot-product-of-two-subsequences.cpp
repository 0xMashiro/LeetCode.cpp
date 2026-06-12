#include "leetcode/problems/max-dot-product-of-two-subsequences.h"

namespace leetcode {
namespace problem_1458 {

namespace {

const int kMinValue = INT_MIN / 2;  // 避免加法溢出

// 策略1：标准二维动态规划
// 时间复杂度: O(n*m)，空间复杂度: O(n*m)
static int solution1(vector<int>& nums1, vector<int>& nums2) {
  const int n = nums1.size();
  const int m = nums2.size();
  
  // dp[i][j] 表示考虑 nums1 前 i 个元素和 nums2 前 j 个元素时的最大点积
  // 初始化所有值为 kMinValue，表示无效状态
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, kMinValue));
  // dp[0][0] = 0，表示空子序列的点积为 0（但最终答案不能为空）
  dp[0][0] = 0;
  
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      const int product = nums1[i - 1] * nums2[j - 1];
      dp[i][j] = max({
          dp[i - 1][j - 1] + product,  // 配对当前元素，延续之前的子序列
          dp[i - 1][j],                 // 跳过 nums1[i-1]
          dp[i][j - 1],                 // 跳过 nums2[j-1]
          product                       // 只使用当前配对（开始新的子序列）
      });
    }
  }
  
  // 答案不能为空子序列，所以从 i>=1, j>=1 中取最大值
  int ans = kMinValue;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      ans = max(ans, dp[i][j]);
    }
  }
  return ans;
}

// 策略2：优化空间的动态规划（滚动数组）
// 时间复杂度: O(n*m)，空间复杂度: O(min(n,m))
static int solution2(vector<int>& nums1, vector<int>& nums2) {
  const int n = nums1.size();
  const int m = nums2.size();
  
  // 选择较短的数组作为外层循环，以最小化空间使用
  const bool swapped = n > m;
  const vector<int>& a = swapped ? nums2 : nums1;
  const vector<int>& b = swapped ? nums1 : nums2;
  const int lenA = swapped ? m : n;
  const int lenB = swapped ? n : m;
  
  // prev 对应上一行，curr 对应当前行
  vector<int> prev(lenB + 1, kMinValue);
  vector<int> curr(lenB + 1, kMinValue);
  prev[0] = 0;  // dp[0][0] = 0
  
  int ans = kMinValue;
  
  for (int i = 1; i <= lenA; ++i) {
    // 当前行的第一个元素无效（dp[i][0] = kMinValue）
    curr[0] = kMinValue;
    for (int j = 1; j <= lenB; ++j) {
      const int product = a[i - 1] * b[j - 1];
      curr[j] = max({
          prev[j - 1] + product,  // dp[i-1][j-1] + product
          prev[j],                 // dp[i-1][j]
          curr[j - 1],             // dp[i][j-1]
          product                  // 只使用当前配对
      });
      ans = max(ans, curr[j]);
    }
    swap(prev, curr);
  }
  
  return ans;
}

}  // namespace

MaxDotProductOfTwoSubsequencesSolution::MaxDotProductOfTwoSubsequencesSolution() {
  setMetaInfo({.id = 1458,
               .title = "Max Dot Product of Two Subsequences",
               .url = "https://leetcode.com/problems/max-dot-product-of-two-subsequences/"});
  registerStrategy({.name = "Standard DP (O(n*m) space)"}, solution1);
  registerStrategy({.name = "Optimized DP (O(min(n,m)) space)"}, solution2);
}

int MaxDotProductOfTwoSubsequencesSolution::maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
  return getSolution()(nums1, nums2);
}

}  // namespace problem_1458
}  // namespace leetcode