#include "leetcode/problems/minimum-division-operations-to-make-array-non-decreasing.h"

namespace leetcode {
namespace problem_3326 {

// 线性筛预处理最小质因数
// spf[x] 表示 x 的最小质因数
static const int MAXN = 1000001;
static vector<int> spf;
static struct SPFInitializer {
  SPFInitializer() {
    spf.resize(MAXN);
    vector<int> primes;
    for (int i = 2; i < MAXN; ++i) {
      if (spf[i] == 0) {
        spf[i] = i;
        primes.push_back(i);
      }
      for (int p : primes) {
        if (p > spf[i] || (long long)i * p >= MAXN) break;
        spf[i * p] = p;
      }
    }
    // 1 的最小质因数设为 1（特殊情况）
    spf[1] = 1;
  }
} spf_init;

// 主解法：从右向左贪心
// 时间复杂度: O(n * log(max(nums))), 空间复杂度: O(MAXN) 预处理
static int solution(vector<int>& nums) {
  const int n = nums.size();
  if (n <= 1) return 0;

  long long operations = 0;
  // limit 表示右侧元素经过操作后的值，当前元素必须 <= limit
  long long limit = nums[n - 1];

  for (int i = n - 2; i >= 0; --i) {
    long long x = nums[i];

    if (x <= limit) {
      // 不需要操作，直接更新 limit
      limit = x;
      continue;
    }

    // x > limit，需要操作
    int ops = 0;
    while (x > limit) {
      // 质数无法再减小（除了本身）
      if (spf[x] == x) {
        // 是质数，无法继续减小
        return -1;
      }
      // 除以最大真因数 = 变成最小质因数
      x = spf[x];
      ops++;
    }

    operations += ops;
    limit = x;
  }

  return (int)operations;
}

MinimumDivisionOperationsToMakeArrayNonDecreasingSolution::MinimumDivisionOperationsToMakeArrayNonDecreasingSolution() {
  setMetaInfo({
    .id = 3326,
    .title = "Minimum Division Operations to Make Array Non Decreasing",
    .url = "https://leetcode.com/problems/minimum-division-operations-to-make-array-non-decreasing/"
  });
  registerStrategy("Greedy from right", solution);
}

int MinimumDivisionOperationsToMakeArrayNonDecreasingSolution::minOperations(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3326
}  // namespace leetcode
