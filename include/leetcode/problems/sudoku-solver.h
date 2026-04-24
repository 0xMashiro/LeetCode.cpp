#include "leetcode/core.h"

namespace leetcode {
namespace problem_37 {

using Func = std::function<void(vector<vector<char>>&)>;

class SudokuSolverSolution : public SolutionBase<Func> {
 public:
  //! 37. Sudoku Solver
  //! https://leetcode.com/problems/sudoku-solver/
  void solveSudoku(vector<vector<char>>& board);

  SudokuSolverSolution();
};

}  // namespace problem_37
}  // namespace leetcode
