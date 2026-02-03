
#include "leetcode/problems/k-th-smallest-in-lexicographical-order.h"

namespace leetcode {
namespace problem_440 {

// 计算以 prefix 为前缀的数字个数（在 [1, n] 范围内）
static long long countPrefix(long long prefix, long long n) {
  long long count = 0;
  long long first = prefix;      // 当前层的第一个数
  long long last = prefix;       // 当前层的最后一个数
  
  while (first <= n) {
    // 当前层的数字个数：min(last, n) - first + 1
    count += std::min(last, n) - first + 1;
    first *= 10;
    last = last * 10 + 9;
  }
  
  return count;
}

// 字典序十叉树遍历
// 时间复杂度: O(log n * log n)，空间复杂度: O(1)
static int solution1(int n, int k) {
  int prefix = 1;  // 从1开始
  k--;  // 减去1本身
  
  while (k > 0) {
    long long count = countPrefix(prefix, n);
    
    if (count <= k) {
      // 跳过以 prefix 为前缀的所有数
      k -= count;
      prefix++;  // 尝试下一个前缀
    } else {
      // 目标在当前前缀的子树中
      k--;  // 减去当前 prefix 本身
      prefix *= 10;  // 进入子树
    }
  }
  
  return prefix;
}

KThSmallestInLexicographicalOrderSolution::KThSmallestInLexicographicalOrderSolution() {
  setMetaInfo({.id = 440,
               .title = "K-th Smallest in Lexicographical Order",
               .url = "https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/"});
  registerStrategy("Prefix Tree", solution1);
}

int KThSmallestInLexicographicalOrderSolution::findKthNumber(int n, int k) {
  return getSolution()(n, k);
}

}  // namespace problem_440
}  // namespace leetcode
