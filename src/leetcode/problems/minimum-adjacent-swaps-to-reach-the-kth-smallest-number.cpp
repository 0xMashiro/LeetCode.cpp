#include "leetcode/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number.h"

namespace leetcode {
namespace problem_1850 {

// 计算将 s 变成 t 所需的最小相邻交换次数
// 使用贪心模拟：对于 t 的每个位置，在 s 中找到对应字符并交换到前面
static int minSwaps(string s, string t) {
  int n = s.size();
  int swaps = 0;
  
  for (int i = 0; i < n; ++i) {
    if (s[i] == t[i]) continue;
    
    // 在 s 的 [i+1, n) 范围内找到第一个等于 t[i] 的字符
    int j = i + 1;
    while (j < n && s[j] != t[i]) {
      ++j;
    }
    
    // 将 s[j] 通过相邻交换移动到位置 i
    // 需要交换 (j - i) 次
    while (j > i) {
      swap(s[j], s[j - 1]);
      ++swaps;
      --j;
    }
  }
  
  return swaps;
}

// 主解法：先找到第 k 个排列，再计算最小交换次数
static int solution(string num, int k) {
  string target = num;
  
  // 使用 next_permutation 找到第 k 个排列
  for (int i = 0; i < k; ++i) {
    next_permutation(target.begin(), target.end());
  }
  
  // 计算从 num 变成 target 的最小相邻交换次数
  return minSwaps(num, target);
}

MinimumAdjacentSwapsToReachTheKthSmallestNumberSolution::MinimumAdjacentSwapsToReachTheKthSmallestNumberSolution() {
  setMetaInfo({.id = 1850,
               .title = "Minimum Adjacent Swaps to Reach the Kth Smallest Number",
               .url = "https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/"});
  registerStrategy("Next Permutation + Greedy", solution);
}

int MinimumAdjacentSwapsToReachTheKthSmallestNumberSolution::getMinSwaps(string num, int k) {
  return getSolution()(num, k);
}

}  // namespace problem_1850
}  // namespace leetcode
