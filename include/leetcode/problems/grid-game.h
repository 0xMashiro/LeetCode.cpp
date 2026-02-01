#include "leetcode/core.h"

namespace leetcode {
namespace problem_2017 {

using Func = std::function<long long(vector<vector<int>>&)>;

/**
 * @brief Grid Game 解决方案
 * 
 * 思路：前缀和 + 枚举
 * 第一个机器人在第i列向下时，第二个机器人能收集的最大分数为：
 * max(第二行前i项和, 第一行i+1到末尾的和)
 * 第一个机器人会选择使这个最大值最小的i
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
class GridGameSolution : public SolutionBase<Func> {
 public:
  //! 2017. Grid Game
  //! https://leetcode.com/problems/grid-game/
  long long gridGame(vector<vector<int>>& grid);

  GridGameSolution();
};

}  // namespace problem_2017
}  // namespace leetcode
