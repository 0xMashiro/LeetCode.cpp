#include "leetcode/problems/maximize-win-from-two-segments.h"

namespace leetcode {
namespace problem_2555 {

// 滑动窗口 + 前缀最大值
// 1. 用滑动窗口计算 cnt[i]：以 prizePositions[i] 为左端点的线段覆盖多少奖品
// 2. dp[i] 表示从位置 i 往后，单个线段最多覆盖多少奖品
// 3. 枚举第一个线段的位置 i，答案为 cnt[i] + dp[i+cnt[i]]
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<int>& prizePositions, int k) {
  const int n = prizePositions.size();
  if (n == 0) return 0;
  
  // cnt[i] 表示以 prizePositions[i] 为左端点的线段覆盖多少奖品
  vector<int> cnt(n);
  int j = 0;
  for (int i = 0; i < n; ++i) {
    // 移动右指针，使得 prizePositions[j] <= prizePositions[i] + k
    while (j < n && prizePositions[j] <= prizePositions[i] + k) {
      ++j;
    }
    cnt[i] = j - i;
  }
  
  // dp[i] 表示从位置 i 往后，单个线段最多覆盖多少奖品
  vector<int> dp(n + 1, 0);
  for (int i = n - 1; i >= 0; --i) {
    dp[i] = max(cnt[i], dp[i + 1]);
  }
  
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    // 第一个线段从 i 开始，覆盖 cnt[i] 个奖品
    // 第二个线段从 i+cnt[i] 开始（或者更后，取 dp 数组的最大值）
    ans = max(ans, cnt[i] + dp[min(i + cnt[i], n)]);
  }
  
  return ans;
}

MaximizeWinFromTwoSegmentsSolution::MaximizeWinFromTwoSegmentsSolution() {
  setMetaInfo({.id = 2555,
               .title = "Maximize Win From Two Segments",
               .url = "https://leetcode.com/problems/maximize-win-from-two-segments/"});
  registerStrategy("Sliding Window + DP", solution1);
}

int MaximizeWinFromTwoSegmentsSolution::maximizeWin(vector<int>& prizePositions, int k) {
  return getSolution()(prizePositions, k);
}

}  // namespace problem_2555
}  // namespace leetcode
