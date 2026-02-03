
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3264 {

using Func = std::function<vector<int>(vector<int>&, int, int)>;

/**
 * Final Array State After K Multiplication Operations I
 * 思路：暴力模拟，每次找到最小值并乘以 multiplier
 * 时间复杂度: O(k * n), 空间复杂度: O(1)
 */
class FinalArrayStateAfterKMultiplicationOperationsISolution : public SolutionBase<Func> {
 public:
  vector<int> getFinalState(vector<int>& nums, int k, int multiplier);

  FinalArrayStateAfterKMultiplicationOperationsISolution();
};

}  // namespace problem_3264
}  // namespace leetcode
