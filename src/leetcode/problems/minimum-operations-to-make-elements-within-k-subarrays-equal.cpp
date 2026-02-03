#include "leetcode/problems/minimum-operations-to-make-elements-within-k-subarrays-equal.h"

namespace leetcode {
namespace problem_3505 {

/**
 * 计算将一个子数组变为所有元素相等的最小操作次数
 * 使用双堆 + 延迟删除维护滑动窗口的中位数
 * 
 * 时间复杂度: O(n log x + n * k)
 * 空间复杂度: O(n)
 */
static long long solve(vector<int>& nums, int x, int k) {
  const int n = nums.size();
  
  // cost[i] 表示从位置 i 开始，长度为 x 的子数组变成全相等的最小代价
  // 如果 i + x > n，则无法形成完整子数组
  vector<long long> cost(n, -1);
  
  // 双堆 + 延迟删除
  priority_queue<long long> small;  // 大顶堆，存较小的一半
  priority_queue<long long, vector<long long>, greater<long long>> large;  // 小顶堆
  unordered_map<long long, int> delayed;
  
  long long smallSum = 0, largeSum = 0;
  int smallSize = 0, largeSize = 0;
  
  auto pruneSmall = [&]() {
    while (!small.empty() && delayed[small.top()] > 0) {
      delayed[small.top()]--;
      small.pop();
    }
  };
  
  auto pruneLarge = [&]() {
    while (!large.empty() && delayed[large.top()] > 0) {
      delayed[large.top()]--;
      large.pop();
    }
  };
  
  auto balance = [&]() {
    // 确保 small 的大小 = large 的大小 或 large 的大小 + 1
    if (smallSize > largeSize + 1) {
      pruneSmall();
      largeSum += small.top();
      smallSum -= small.top();
      large.push(small.top());
      small.pop();
      smallSize--; largeSize++;
    } else if (smallSize < largeSize) {
      pruneLarge();
      smallSum += large.top();
      largeSum -= large.top();
      small.push(large.top());
      large.pop();
      smallSize++; largeSize--;
    }
  };
  
  auto addNum = [&](long long num) {
    if (small.empty() || num <= small.top()) {
      small.push(num);
      smallSum += num;
      smallSize++;
    } else {
      large.push(num);
      largeSum += num;
      largeSize++;
    }
    balance();
  };
  
  auto removeNum = [&](long long num) {
    delayed[num]++;
    if (!small.empty() && num <= small.top()) {
      smallSum -= num;
      smallSize--;
      if (num == small.top()) pruneSmall();
    } else {
      largeSum -= num;
      largeSize--;
      if (!large.empty() && num == large.top()) pruneLarge();
    }
    balance();
  };
  
  auto getMedian = [&]() -> long long {
    pruneSmall();
    return small.top();
  };
  
  auto getOperationCost = [&]() -> long long {
    long long median = getMedian();
    long long leftCost = median * (long long)smallSize - smallSum;
    long long rightCost = largeSum - median * (long long)largeSize;
    return leftCost + rightCost;
  };
  
  // 初始化窗口 [0, x-1]
  for (int i = 0; i < x && i < n; ++i) {
    addNum(nums[i]);
  }
  
  if (x <= n) {
    cost[0] = getOperationCost();
  }
  
  // 滑动窗口
  for (int i = 1; i + x - 1 < n; ++i) {
    removeNum(nums[i - 1]);
    addNum(nums[i + x - 1]);
    cost[i] = getOperationCost();
  }
  
  // 动态规划
  // dp[i][j] = 考虑前 i 个元素（nums[0..i-1]），选择 j 个不重叠子数组的最小代价
  // 转移：
  // 1. 不选择以 i-1 结尾的子数组: dp[i][j] = dp[i-1][j]
  // 2. 选择以 i-1 结尾的子数组（从 i-x 开始）: dp[i][j] = dp[i-x][j-1] + cost[i-x]
  
  const long long INF = (long long)4e18;
  // 使用滚动数组，只需要保留前 x 个状态
  vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, INF));
  dp[0][0] = 0;
  
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) {
      // 不选择以 i-1 结尾的子数组
      dp[i][j] = dp[i-1][j];
      
      // 选择以 i-1 结尾的子数组
      if (j > 0 && i >= x && cost[i - x] >= 0) {
        dp[i][j] = min(dp[i][j], dp[i - x][j - 1] + cost[i - x]);
      }
    }
  }
  
  return dp[n][k];
}

MinimumOperationsToMakeElementsWithinKSubarraysEqualSolution::MinimumOperationsToMakeElementsWithinKSubarraysEqualSolution() {
  setMetaInfo({.id = 3505,
               .title = "Minimum Operations to Make Elements Within K Subarrays Equal",
               .url = "https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/"});
  registerStrategy("Sliding Window + DP", solve);
}

long long MinimumOperationsToMakeElementsWithinKSubarraysEqualSolution::minOperations(vector<int>& nums, int x, int k) {
  return getSolution()(nums, x, k);
}

}  // namespace problem_3505
}  // namespace leetcode
