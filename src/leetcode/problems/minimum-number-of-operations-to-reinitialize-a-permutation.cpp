#include "leetcode/problems/minimum-number-of-operations-to-reinitialize-a-permutation.h"

namespace leetcode {
namespace problem_1806 {

/**
 * 追踪数字 1 的位置变化
 * 
 * 观察：
 * - 数字 0 始终在位置 0，不会改变
 * - 数字 1 会遍历所有非零位置，最终回到位置 1
 * - 只需追踪数字 1 的位置，直到它回到初始位置
 * 
 * 位置变换规则：
 * - 偶数位置 i: 新位置 = i / 2 (从 perm 的前半部分取)
 * - 奇数位置 i: 新位置 = n/2 + (i-1)/2 (从 perm 的后半部分取)
 * 
 * 反向推导（从原位置推导新位置）：
 * - 如果原位置 i 在 [0, n/2-1]（前半部分）：它会被放到偶数位置 2*i
 * - 如果原位置 i 在 [n/2, n-1]（后半部分）：它会被放到奇数位置 2*(i-n/2)+1
 * 
 * 时间复杂度: O(操作次数)，最坏情况下为 O(n)
 * 空间复杂度: O(1)
 */
static int solution1(int n) {
  int operations = 0;
  int pos = 1;  // 追踪数字 1 的当前位置
  
  do {
    // 计算下一个位置
    if (pos % 2 == 0) {
      // 偶数位置：来自 perm[pos/2]
      pos = pos / 2;
    } else {
      // 奇数位置：来自 perm[n/2 + (pos-1)/2]
      pos = n / 2 + (pos - 1) / 2;
    }
    ++operations;
  } while (pos != 1);  // 当 1 回到位置 1 时停止
  
  return operations;
}

/**
 * 完整模拟法（用于验证）
 * 模拟整个 perm 数组的变化过程
 * 
 * 时间复杂度: O(n * 操作次数)
 * 空间复杂度: O(n)
 */
static int solution2(int n) {
  vector<int> perm(n);
  for (int i = 0; i < n; ++i) {
    perm[i] = i;
  }
  
  int operations = 0;
  
  while (true) {
    // 检查是否已恢复原状
    bool isInitial = true;
    for (int i = 0; i < n; ++i) {
      if (perm[i] != i) {
        isInitial = false;
        break;
      }
    }
    if (isInitial && operations > 0) {
      break;
    }
    
    // 执行一次操作
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
      if (i % 2 == 0) {
        arr[i] = perm[i / 2];
      } else {
        arr[i] = perm[n / 2 + (i - 1) / 2];
      }
    }
    perm = arr;
    ++operations;
  }
  
  return operations;
}

MinimumNumberOfOperationsToReinitializeAPermutationSolution::MinimumNumberOfOperationsToReinitializeAPermutationSolution() {
  setMetaInfo({.id = 1806,
               .title = "Minimum Number of Operations to Reinitialize a Permutation",
               .url = "https://leetcode.com/problems/minimum-number-of-operations-to-reinitialize-a-permutation/"});
  registerStrategy("Position Tracking", solution1);
  registerStrategy("Full Simulation", solution2);
}

int MinimumNumberOfOperationsToReinitializeAPermutationSolution::reinitializePermutation(int n) {
  return getSolution()(n);
}

}  // namespace problem_1806
}  // namespace leetcode
