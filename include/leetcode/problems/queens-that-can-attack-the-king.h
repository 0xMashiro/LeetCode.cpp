#include "leetcode/core.h"

namespace leetcode {
namespace problem_1222 {

using Func = std::function<vector<vector<int>>(vector<vector<int>>&, vector<int>&)>;

/**
 * 1222. Queens That Can Attack the King
 * https://leetcode.com/problems/queens-that-can-attack-the-king/
 *
 * On a 0-indexed 8x8 chessboard, there can be multiple black queens and one white king.
 * Return the coordinates of the black queens that can directly attack the king.
 *
 * Strategy: From the king's position, search in 8 directions. For each direction,
 * find the closest queen (if any). Only the closest queen in each direction can attack.
 */
class QueensThatCanAttackTheKingSolution : public SolutionBase<Func> {
 public:
  vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king);

  QueensThatCanAttackTheKingSolution();
};

}  // namespace problem_1222
}  // namespace leetcode
