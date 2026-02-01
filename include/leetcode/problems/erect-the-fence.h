#include "leetcode/core.h"

namespace leetcode {
namespace problem_587 {

using Func = std::function<vector<vector<int>>(vector<vector<int>>&)>;

/**
 * 587. Erect the Fence
 * https://leetcode.com/problems/erect-the-fence/
 * 
 * 使用 Andrew's Monotone Chain 算法（单调链算法）求凸包
 * 时间复杂度: O(n log n)，空间复杂度: O(n)
 */
class ErectTheFenceSolution : public SolutionBase<Func> {
 public:
  vector<vector<int>> outerTrees(vector<vector<int>>& trees);
  
  ErectTheFenceSolution();
};

}  // namespace problem_587
}  // namespace leetcode
