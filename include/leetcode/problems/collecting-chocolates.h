
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2735 {

using Func = std::function<long long(vector<int>&, int)>;

/**
 * 2735. Collecting Chocolates
 * https://leetcode.com/problems/collecting-chocolates/
 * 
 * 思路：枚举旋转次数 k，计算每种类型在 k 次旋转内的最小成本
 * - 对于每个类型 j，在 k 次旋转内可以选择位置 j, j-1, ..., j-k (mod n)
 * - 预处理 minCost[j][k] = 类型 j 在 k 次旋转内的最小成本
 * - 枚举总旋转次数 k，计算总成本 = k * x + sum(minCost[j][k])
 * 
 * 时间复杂度: O(n²)
 * 空间复杂度: O(n²)
 */
class CollectingChocolatesSolution : public SolutionBase<Func> {
 public:
  long long minCost(vector<int>& nums, int x);

  CollectingChocolatesSolution();
};

}  // namespace problem_2735
}  // namespace leetcode
