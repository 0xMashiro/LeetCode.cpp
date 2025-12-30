
#include "leetcode/problems/magic-squares-in-grid.h"

namespace leetcode {
namespace problem_840 {

// Helper function to check if a 3x3 subgrid starting at (r, c) is a magic square
static bool isMagicSquare(const vector<vector<int>>& grid, int r, int c) {
  // Quick check: center must be 5
  if (grid[r + 1][c + 1] != 5) return false;

  // Check numbers are in 1..9 and distinct
  bool seen[10] = {false};  // indices 1..9
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      int num = grid[r + i][c + j];
      if (num < 1 || num > 9) return false;
      if (seen[num]) return false;
      seen[num] = true;
    }
  }

  // Calculate sums of rows, columns, and diagonals
  // Use first row sum as reference
  int sum = grid[r][c] + grid[r][c + 1] + grid[r][c + 2];
  
  // Check other two rows
  if (grid[r + 1][c] + grid[r + 1][c + 1] + grid[r + 1][c + 2] != sum) return false;
  if (grid[r + 2][c] + grid[r + 2][c + 1] + grid[r + 2][c + 2] != sum) return false;
  
  // Check three columns
  if (grid[r][c] + grid[r + 1][c] + grid[r + 2][c] != sum) return false;
  if (grid[r][c + 1] + grid[r + 1][c + 1] + grid[r + 2][c + 1] != sum) return false;
  if (grid[r][c + 2] + grid[r + 1][c + 2] + grid[r + 2][c + 2] != sum) return false;
  
  // Check two diagonals
  if (grid[r][c] + grid[r + 1][c + 1] + grid[r + 2][c + 2] != sum) return false;
  if (grid[r][c + 2] + grid[r + 1][c + 1] + grid[r + 2][c] != sum) return false;

  // All sums equal, and because numbers are 1..9 distinct and center is 5,
  // the sum must be 15. But we can also explicitly check:
  // return sum == 15;
  // However, the above conditions already guarantee sum == 15.
  return true;
}

// Strategy 1: Brute force checking with pruning
static int solution1(vector<vector<int>>& grid) {
  int rows = grid.size();
  if (rows < 3) return 0;
  int cols = grid[0].size();
  if (cols < 3) return 0;

  int count = 0;
  for (int i = 0; i <= rows - 3; ++i) {
    for (int j = 0; j <= cols - 3; ++j) {
      if (isMagicSquare(grid, i, j)) {
        ++count;
      }
    }
  }
  return count;
}

MagicSquaresInGridSolution::MagicSquaresInGridSolution() {
  setMetaInfo({.id = 840,
               .title = "Magic Squares In Grid",
               .url = "https://leetcode.com/problems/magic-squares-in-grid/"});
  registerStrategy("Brute Force with Pruning", solution1);
}

int MagicSquaresInGridSolution::numMagicSquaresInside(vector<vector<int>>& grid) {
  return getSolution()(grid);
}

}  // namespace problem_840
}  // namespace leetcode