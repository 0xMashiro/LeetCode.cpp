#include "leetcode/core.h"

namespace leetcode {
namespace problem_2850 {

using Func = std::function<int(vector<vector<int>>&)>;

/**
 * @brief Minimum Moves to Spread Stones Over Grid
 * @details https://leetcode.com/problems/minimum-moves-to-spread-stones-over-grid/
 * 
 * 题目：3x3 网格中分布着 9 个石头，每次可将一个石头移动到相邻格子（共享边），
 * 求让每个格子恰好有 1 个石头的最小移动次数。
 * 
 * 算法思路：回溯法
 * - 找出所有石头数 > 1 的格子（有多余石头，作为"源"）
 * - 找出所有石头数 = 0 的格子（需要石头，作为"目标"）
 * - 用回溯法枚举每个目标格子从哪个源格子获取石头，计算最小总距离
 * - 两格子间距离为曼哈顿距离 |x1-x2| + |y1-y2|
 */
class MinimumMovesToSpreadStonesOverGridSolution : public SolutionBase<Func> {
 public:
  int minimumMoves(vector<vector<int>>& grid);
  MinimumMovesToSpreadStonesOverGridSolution();
};

}  // namespace problem_2850
}  // namespace leetcode
