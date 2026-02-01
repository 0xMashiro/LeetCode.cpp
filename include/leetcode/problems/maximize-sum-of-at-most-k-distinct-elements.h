#include "leetcode/core.h"

namespace leetcode {
namespace problem_3684 {

using Func = std::function<vector<int>(vector<int>&, int)>;

/**
 * 3684. Maximize Sum of At Most K Distinct Elements
 * https://leetcode.com/problems/maximize-sum-of-at-most-k-distinct-elements/
 *
 * 思路：贪心 + 排序
 * 1. 将数组去重，得到所有不同的数
 * 2. 按降序排序
 * 3. 取前 min(k, 去重后数组大小) 个数
 * 时间复杂度: O(n log n)，空间复杂度: O(n)
 */
class MaximizeSumOfAtMostKDistinctElementsSolution : public SolutionBase<Func> {
 public:
  vector<int> maxKDistinct(vector<int>& nums, int k);

  MaximizeSumOfAtMostKDistinctElementsSolution();
};

}  // namespace problem_3684
}  // namespace leetcode
