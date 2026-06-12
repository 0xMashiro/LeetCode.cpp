#include "leetcode/problems/n-th-tribonacci-number.h"

namespace leetcode {
namespace problem_1137 {

// 解法1：递归 + 记忆化（Memoization）
// 直接用数组记录已计算过的 Tribonacci 数，避免重复递归
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(int n) {
  static int memo[38] = {0};
  static bool initialized = false;
  if (!initialized) {
    memo[0] = 0;
    memo[1] = 1;
    memo[2] = 1;
    initialized = true;
  }
  if (n < 3) return memo[n];
  if (memo[n] != 0) return memo[n];
  memo[n] = solution1(n - 1) + solution1(n - 2) + solution1(n - 3);
  return memo[n];
}

// 解法2：迭代 DP（滚动数组）
// 用三个变量滚动更新，自底向上计算 T_n
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution2(int n) {
  if (n == 0) return 0;
  if (n == 1 || n == 2) return 1;
  int a = 0, b = 1, c = 1;
  for (int i = 3; i <= n; ++i) {
    int next = a + b + c;
    a = b;
    b = c;
    c = next;
  }
  return c;
}

NThTribonacciNumberSolution::NThTribonacciNumberSolution() {
  setMetaInfo({.id = 1137,
               .title = "N-th Tribonacci Number",
               .url = "https://leetcode.com/problems/n-th-tribonacci-number/"});
  // 按面试思考顺序：先展示直观的记忆化解法，再给出最优的迭代 DP
  registerStrategy({.name = "Memoization"}, solution1);
  registerStrategy({.name = "Iterative DP"}, solution2);
}

int NThTribonacciNumberSolution::tribonacci(int n) {
  return getSolution()(n);
}

}  // namespace problem_1137
}  // namespace leetcode
