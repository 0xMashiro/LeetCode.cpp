#include "leetcode/problems/number-of-paths-with-max-score.h"

#include <algorithm>

namespace leetcode {
namespace problem_1301 {

static constexpr int kMod = 1'000'000'007;

// DP from top-left (E) to bottom-right (S).
// For each cell (i, j), dp[i][j] = {max_score, path_count}.
// Transition sources: (i-1, j), (i, j-1), (i-1, j-1).
// Time: O(n^2), Space: O(n^2)
static std::vector<int> solution1(std::vector<std::string>& board) {
  const int n = static_cast<int>(board.size());
  if (n == 0) return {0, 0};

  // dp[i][j].first = max score, .second = number of ways
  using Cell = std::pair<int, int>;
  std::vector<std::vector<Cell>> dp(n, std::vector<Cell>(n, {-1, 0}));

  // Start cell 'E' at (0,0): score 0, 1 way
  dp[0][0] = {0, 1};

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (board[i][j] == 'X') {
        dp[i][j] = {-1, 0};
        continue;
      }
      if (i == 0 && j == 0) continue;  // already initialized

      int best_score = -1;
      int total_ways = 0;

      // Check three predecessors: up, left, up-left
      auto try_from = [&](int pi, int pj) {
        if (pi < 0 || pj < 0) return;
        if (dp[pi][pj].second == 0) return;  // unreachable
        int cand = dp[pi][pj].first;
        if (cand > best_score) {
          best_score = cand;
          total_ways = dp[pi][pj].second;
        } else if (cand == best_score) {
          total_ways = (total_ways + dp[pi][pj].second) % kMod;
        }
      };

      try_from(i - 1, j);      // up
      try_from(i, j - 1);      // left
      try_from(i - 1, j - 1);  // up-left

      if (best_score == -1) {
        dp[i][j] = {-1, 0};
      } else {
        int add = (board[i][j] >= '1' && board[i][j] <= '9') ? (board[i][j] - '0') : 0;
        dp[i][j] = {best_score + add, total_ways};
      }
    }
  }

  const auto& dest = dp[n - 1][n - 1];
  if (dest.second == 0) return {0, 0};
  return {dest.first, dest.second};
}

NumberOfPathsWithMaxScoreSolution::NumberOfPathsWithMaxScoreSolution() {
  setMetaInfo({.id = 1301,
               .title = "Number of Paths with Max Score",
               .url = "https://leetcode.com/problems/number-of-paths-with-max-score/"});
  registerStrategy({.name = "DP (2D)",
                    .expected = "Accepted",
                    .time_complexity = "O(n^2)",
                    .space_complexity = "O(n^2)",
                    .tags = {"Array", "Dynamic Programming", "Matrix"}},
                   solution1);
}

std::vector<int> NumberOfPathsWithMaxScoreSolution::pathsWithMaxScore(
    std::vector<std::string>& board) {
  return getSolution()(board);
}

}  // namespace problem_1301
}  // namespace leetcode
