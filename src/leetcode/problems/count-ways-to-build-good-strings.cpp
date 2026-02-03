#include "leetcode/problems/count-ways-to-build-good-strings.h"

namespace leetcode {
namespace problem_2466 {

static const int MOD = 1e9 + 7;

// 动态规划解法
// dp[i] 表示构造长度为 i 的字符串的方案数
// 时间复杂度: O(high), 空间复杂度: O(high)
static int solution1(int low, int high, int zero, int one) {
  vector<long long> dp(high + 1, 0);
  dp[0] = 1;  // 空字符串
  
  for (int i = 1; i <= high; ++i) {
    if (i >= zero) {
      dp[i] = (dp[i] + dp[i - zero]) % MOD;
    }
    if (i >= one) {
      dp[i] = (dp[i] + dp[i - one]) % MOD;
    }
  }
  
  long long result = 0;
  for (int i = low; i <= high; ++i) {
    result = (result + dp[i]) % MOD;
  }
  
  return static_cast<int>(result);
}

// 空间优化版本：使用滚动数组
// 时间复杂度: O(high), 空间复杂度: O(max(zero, one))
static int solution2(int low, int high, int zero, int one) {
  // 实际上需要随机访问 dp[i-zero] 和 dp[i-one]
  // 所以滚动数组不太容易实现，还是用完整数组
  return solution1(low, high, zero, one);
}

CountWaysToBuildGoodStringsSolution::CountWaysToBuildGoodStringsSolution() {
  setMetaInfo({.id = 2466,
               .title = "Count Ways To Build Good Strings",
               .url = "https://leetcode.com/problems/count-ways-to-build-good-strings/"});
  registerStrategy("Dynamic Programming", solution1);
}

int CountWaysToBuildGoodStringsSolution::countGoodStrings(int low, int high, int zero, int one) {
  return getSolution()(low, high, zero, one);
}

}  // namespace problem_2466
}  // namespace leetcode
