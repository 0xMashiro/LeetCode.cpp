
#include "leetcode/core.h"

namespace leetcode {
namespace problem_240 {

using Func = std::function<bool(vector<vector<int>>&, int)>;

/**
 * 240. Search a 2D Matrix II
 * https://leetcode.com/problems/search-a-2d-matrix-ii/
 * 
 * 在一个 m x n 的整数矩阵中搜索目标值 target
 * 矩阵特性：每行从左到右升序，每列从上到下升序
 */
class SearchA2dMatrixIiSolution : public SolutionBase<Func> {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target);

  SearchA2dMatrixIiSolution();
};

}  // namespace problem_240
}  // namespace leetcode
