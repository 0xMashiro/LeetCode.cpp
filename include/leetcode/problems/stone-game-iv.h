
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1510 {

using Func = std::function<bool(int)>;

/**
 * 1510. Stone Game IV
 * https://leetcode.com/problems/stone-game-iv/
 *
 * Alice and Bob take turns playing a game, with Alice starting first.
 * Initially, there are n stones in a pile.
 * On each player's turn, that player removes any non-zero square number of stones.
 * Return true if Alice wins the game assuming both players play optimally.
 */
class StoneGameIvSolution : public SolutionBase<Func> {
 public:
  bool winnerSquareGame(int n);

  StoneGameIvSolution();
};

}  // namespace problem_1510
}  // namespace leetcode
