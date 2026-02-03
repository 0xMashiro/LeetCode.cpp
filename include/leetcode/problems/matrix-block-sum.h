#include "leetcode/core.h"

namespace leetcode {
namespace problem_1314 {

using Func = std::function<vector<vector<int>>(vector<vector<int>>&, int)>;

/**
 * 1314. Matrix Block Sum
 * https://leetcode.com/problems/matrix-block-sum/
 *
 * Given a m x n matrix mat and an integer k, return a matrix answer where each
 * answer[i][j] is the sum of all elements mat[r][c] for:
 * - i - k <= r <= i + k,
 * - j - k <= c <= j + k, and
 * - (r, c) is a valid position in the matrix.
 */
class MatrixBlockSumSolution : public SolutionBase<Func> {
 public:
  vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k);

  MatrixBlockSumSolution();
};

}  // namespace problem_1314
}  // namespace leetcode
