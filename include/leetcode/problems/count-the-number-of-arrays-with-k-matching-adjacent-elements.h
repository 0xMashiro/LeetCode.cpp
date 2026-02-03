#include "leetcode/core.h"

namespace leetcode {
namespace problem_3405 {

using Func = std::function<int(int, int, int)>;

/**
 * @brief 计算满足条件的数组数量
 * 
 * 好数组定义：长度为 n，元素在 [1, m] 范围内，恰好有 k 对相邻元素相等
 * 
 * 算法思路：
 * 1. 从 n-1 个相邻位置中选 k 个作为相等位置：C(n-1, k)
 * 2. 第一个元素有 m 种选择
 * 3. 选中的 k 个位置各有 1 种选择（必须等于前一个）
 * 4. 其余 (n-1-k) 个位置各有 (m-1) 种选择（必须不同于前一个）
 * 
 * 答案 = C(n-1, k) * m * (m-1)^(n-1-k) % MOD
 */
class CountTheNumberOfArraysWithKMatchingAdjacentElementsSolution 
    : public SolutionBase<Func> {
 public:
  int countGoodArrays(int n, int m, int k);
  
  CountTheNumberOfArraysWithKMatchingAdjacentElementsSolution();
};

}  // namespace problem_3405
}  // namespace leetcode