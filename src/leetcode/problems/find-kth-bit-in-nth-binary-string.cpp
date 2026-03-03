#include "leetcode/problems/find-kth-bit-in-nth-binary-string.h"

namespace leetcode {
namespace problem_1545 {

/**
 * 递归分治解法
 * 
 * Sₙ 的结构分析：
 * Sₙ = Sₙ₋₁ + "1" + reverse(invert(Sₙ₋₁))
 * 长度：len(Sₙ) = 2ⁿ - 1 = (2ⁿ⁻¹ - 1) + 1 + (2ⁿ⁻¹ - 1)
 * 
 * 对于第 k 位：
 * - 如果 k == 2ⁿ⁻¹，返回 "1"
 * - 如果 k < 2ⁿ⁻¹，在 Sₙ₋₁ 中找第 k 位
 * - 如果 k > 2ⁿ⁻¹，在 reverse(invert(Sₙ₋₁)) 中找第 k - 2ⁿ⁻¹ 位
 *   这等于在 invert(Sₙ₋₁) 中找倒数第 (k - 2ⁿ⁻¹) 位
 *   即 Sₙ₋₁ 的正数第 (2ⁿ⁻¹ - (k - 2ⁿ⁻¹)) = (2ⁿ - k) 位取反
 * 
 * 时间复杂度: O(n)，每次递归 n 减 1
 * 空间复杂度: O(n)，递归栈深度
 */
static char solution1(int n, int k) {
  // 递归辅助函数，flip 表示当前位需要翻转的次数（0 或 1）
  function<char(int, int, int)> dfs = [&](int n, int k, int flip) -> char {
    if (n == 1) {
      // S₁ = "0"
      return flip ? '1' : '0';
    }
    
    int mid = 1 << (n - 1);  // 2ⁿ⁻¹，中间位置（Sₙ 的正中间是第 2ⁿ⁻¹ 位）
    
    if (k == mid) {
      // 中间位置，固定是 "1"
      return flip ? '0' : '1';
    } else if (k < mid) {
      // 在左半部分 Sₙ₋₁ 中
      return dfs(n - 1, k, flip);
    } else {
      // 在右半部分 reverse(invert(Sₙ₋₁)) 中
      // 第 k 位对应于 Sₙ₋₁ 的第 (2ⁿ - k) 位取反
      // 取反通过 flip 的奇偶性来传递
      return dfs(n - 1, (1 << n) - k, flip ^ 1);
    }
  };
  
  return dfs(n, k, 0);
}

/**
 * 迭代版本（避免递归开销）
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
static char solution2(int n, int k) {
  int flip = 0;
  
  while (n > 1) {
    int mid = 1 << (n - 1);  // 2ⁿ⁻¹
    
    if (k == mid) {
      // 中间位置，固定是 "1"
      return flip ? '0' : '1';
    } else if (k > mid) {
      // 在右半部分，需要取反，并映射到对称位置
      k = (1 << n) - k;
      flip ^= 1;
    }
    // 如果在左半部分，直接继续，n 减 1
    n--;
  }
  
  // n == 1，S₁ = "0"
  return flip ? '1' : '0';
}

FindKthBitInNthBinaryStringSolution::FindKthBitInNthBinaryStringSolution() {
  setMetaInfo({
    .id = 1545,
    .title = "Find Kth Bit in Nth Binary String",
    .url = "https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/"
  });
  registerStrategy("Recursive", solution1);
  registerStrategy("Iterative", solution2);
}

char FindKthBitInNthBinaryStringSolution::findKthBit(int n, int k) {
  return getSolution()(n, k);
}

}  // namespace problem_1545
}  // namespace leetcode
