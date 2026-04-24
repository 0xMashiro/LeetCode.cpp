#include "leetcode/problems/longest-arithmetic-sequence-after-changing-at-most-one-element.h"

namespace leetcode {
namespace problem_3872 {

// ------------------------------------------------------------
// 解法 1：暴力枚举（教学用，会 TLE）
// 枚举所有子数组，以每对相邻元素为锚定等差，检查是否至多一个坏元素
// 时间复杂度: O(n^4)，空间复杂度: O(1)
// ------------------------------------------------------------
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      const int len = j - i + 1;
      if (len <= 2) {
        ans = max(ans, len);
        continue;
      }
      bool ok = false;
      for (int p = i; p < j && !ok; ++p) {
        long long d = (long long)nums[p + 1] - (long long)nums[p];
        int bad = 0;
        for (int q = i; q <= j; ++q) {
          long long expected = (long long)nums[p] + (long long)(q - p) * d;
          if ((long long)nums[q] != expected) {
            ++bad;
            if (bad > 1) break;
          }
        }
        if (bad <= 1) {
          ans = max(ans, len);
          ok = true;
        }
      }
    }
  }
  return ans;
}

// ------------------------------------------------------------
// 解法 2：差分数组 + 枚举修改位置（最优解）
//
// 核心思想：
//   等差子数组 ⇔ 差分数组 D[i]=nums[i+1]-nums[i] 中连续相等的一段
//   修改 nums[k] 会改变 D[k-1] 和/或 D[k]（至多 2 个相邻位置），
//   且满足耦合约束: D[k-1]+D[k] = nums[k+1]-nums[k-1] (常数)
//
//   枚举 k 作为修改位置，分三种情况：
//   (A) 子数组从 k 开始（向左扩展）：将 D[k] 设为 D[k+1]，跑向右
//   (B) 子数组到 k 结束（向右扩展）：将 D[k-1] 设为 D[k-2]，跑向左
//   (C) 桥接（子数组包含 k 两侧）：D[k-1]=D[k]=d,
//       d = (nums[k+1]-nums[k-1])/2 (必须为整数)
//       左跑来自 D[k-2]==d 时 leftRun[k-2]
//       右跑来自 D[k+1]==d 时 rightRun[k+1]
//
//   利用 leftRun/rightRun 实现 O(1) 查询运行长度
// 时间复杂度: O(n)，空间复杂度: O(n)
// ------------------------------------------------------------
static int solution2(vector<int>& nums) {
  const int n = nums.size();
  if (n <= 2) return n;

  // 差分数组 D[i] = nums[i+1] - nums[i]
  const int m = n - 1;
  vector<long long> D(m);
  for (int i = 0; i < m; ++i) {
    D[i] = (long long)nums[i + 1] - (long long)nums[i];
  }

  // leftRun[i] = 在 D 中，以 i 结尾的连续相等值长度
  vector<int> leftRun(m, 1);
  for (int i = 1; i < m; ++i) {
    if (D[i] == D[i - 1]) leftRun[i] = leftRun[i - 1] + 1;
  }

  // rightRun[i] = 在 D 中，以 i 开头的连续相等值长度
  vector<int> rightRun(m, 1);
  for (int i = m - 2; i >= 0; --i) {
    if (D[i] == D[i + 1]) rightRun[i] = rightRun[i + 1] + 1;
  }

  // 不修改的情况
  int ans = 0;
  for (int i = 0; i < m; ++i) {
    ans = max(ans, leftRun[i] + 1);  // D 段长度 + 1 = 原数组长度
  }
  if (ans == n) return n;

  // 枚举修改位置 k
  for (int k = 0; k < n; ++k) {
    // ---- (A) 子数组从 k 开始：修改 k 延展向右 ----
    if (k < n - 1) {
      // D[k] 被修改。可以将其设为 D[k+1] 的值（如果 k+1 在范围内）
      if (k + 1 < m) {
        // D[k] 被设为 D[k+1]，跑长度为 1 + rightRun[k+1]
        int run = 1 + rightRun[k + 1];
        ans = max(ans, run + 1);
      } else {
        // k == n-2, D[k] 是最后一个 diff，只有 [k, k+1] 两个元素
        ans = max(ans, 2);
      }
    }

    // ---- (B) 子数组到 k 结束：修改 k 延展向左 ----
    if (k > 0) {
      // D[k-1] 被修改。可以将其设为 D[k-2] 的值（如果 k-2 在范围内）
      if (k >= 2) {
        int run = leftRun[k - 2] + 1;
        ans = max(ans, run + 1);
      } else {
        // k == 1, D[0] 被修改，只有 [0, 1] 两个元素
        ans = max(ans, 2);
      }
    }

    // ---- (C) 桥接：修改 k 使左右连接 ----
    if (k > 0 && k < n - 1) {
      // 耦合约束: D[k-1] + D[k] = nums[k+1] - nums[k-1]
      // 要 D[k-1] = D[k] = d, 需 2d = nums[k+1] - nums[k-1]
      long long diff = (long long)nums[k + 1] - (long long)nums[k - 1];
      if (diff % 2 == 0) {
        long long d = diff / 2;
        int leftExt = (k >= 2 && D[k - 2] == d) ? leftRun[k - 2] : 0;
        int rightExt = (k + 1 < m && D[k + 1] == d) ? rightRun[k + 1] : 0;
        int run = leftExt + 2 + rightExt;
        ans = max(ans, run + 1);
      }
    }

    // 任何情况下，修改一个元素至少可以得到长度 2
    ans = max(ans, 2);
  }

  return ans;
}

// ------------------------------------------------------------
// 构造函数：注册策略
// ------------------------------------------------------------
LongestArithmeticSequenceAfterChangingAtMostOneElementSolution::LongestArithmeticSequenceAfterChangingAtMostOneElementSolution() {
  setMetaInfo({.id = 3872,
               .title = "Longest Arithmetic Sequence After Changing At Most One Element",
               .url = "https://leetcode.com/problems/longest-arithmetic-sequence-after-changing-at-most-one-element/"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("Diff Array O(n)", solution2);
}

int LongestArithmeticSequenceAfterChangingAtMostOneElementSolution::longestArithmetic(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3872
}  // namespace leetcode
