#include "leetcode/problems/kth-smallest-instructions.h"

namespace leetcode {
namespace problem_1643 {

// 预计算组合数 C(n, k)，其中 n <= 30 (因为 row+column <= 30)
// 使用动态规划或公式计算
static long long comb[31][31];

static void initComb() {
  static bool initialized = false;
  if (initialized) return;
  initialized = true;
  for (int i = 0; i <= 30; ++i) {
    comb[i][0] = comb[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
    }
  }
}

// 贪心构造第 k 小的路径
// 时间复杂度: O((row+column) * 1) = O(row+column)
// 空间复杂度: O(1)
static string solution1(vector<int>& destination, int k) {
  initComb();
  
  int v = destination[0];  // 需要向下走的步数 (V)
  int h = destination[1];  // 需要向右走的步数 (H)
  
  string result;
  result.reserve(v + h);
  
  // 还剩 v 个 V 和 h 个 H 需要放置
  // 在当前位置，考虑放 H 还是 V
  while (v > 0 || h > 0) {
    if (h == 0) {
      // 只能放 V
      result.push_back('V');
      --v;
    } else if (v == 0) {
      // 只能放 H
      result.push_back('H');
      --h;
    } else {
      // 可以放 H 或 V，计算如果放 H，有多少种方案
      // 还剩 v 个 V 和 h 个 H，如果当前放 H，剩下 v 个 V 和 h-1 个 H
      long long countH = comb[v + h - 1][v];  // C(v+h-1, v) = C(v+h-1, h-1)
      
      if (k <= countH) {
        // 第 k 个在放 H 的方案中
        result.push_back('H');
        --h;
      } else {
        // 第 k 个在放 V 的方案中
        result.push_back('V');
        k -= countH;  // 跳过所有以 H 开头的方案
        --v;
      }
    }
  }
  
  return result;
}

KthSmallestInstructionsSolution::KthSmallestInstructionsSolution() {
  setMetaInfo({.id = 1643,
               .title = "Kth Smallest Instructions",
               .url = "https://leetcode.com/problems/kth-smallest-instructions/"});
  registerStrategy("Combinatorics Greedy", solution1);
}

string KthSmallestInstructionsSolution::kthSmallestPath(vector<int>& destination, int k) {
  return getSolution()(destination, k);
}

}  // namespace problem_1643
}  // namespace leetcode
