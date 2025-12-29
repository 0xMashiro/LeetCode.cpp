#include "leetcode/problems/pyramid-transition-matrix.h"

namespace leetcode {
namespace problem_756 {

// Strategy 1: Backtracking with memoization
// Build a mapping from (left, right) to possible top characters.
// Use DFS to try all possible next levels, with memoization to avoid redundant computation.
static bool solution1(string bottom, vector<string>& allowed) {
  // Build mapping: map[left][right] -> list of possible top chars
  vector<vector<vector<char>>> mapping(6, vector<vector<char>>(6));
  for (const string& s : allowed) {
    int left = s[0] - 'A';
    int right = s[1] - 'A';
    char top = s[2];
    mapping[left][right].push_back(top);
  }

  unordered_map<string, bool> memo;

  function<bool(const string&)> dfs = [&](const string& cur) -> bool {
    if (cur.size() == 1) return true;
    if (memo.count(cur)) return memo[cur];

    int n = cur.size();
    vector<vector<char>> options(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      int left = cur[i] - 'A';
      int right = cur[i + 1] - 'A';
      const vector<char>& possible = mapping[left][right];
      if (possible.empty()) {
        memo[cur] = false;
        return false;
      }
      options[i] = possible;
    }

    // Generate all possible next level strings using backtracking
    vector<string> nexts;
    function<void(int, string)> backtrack = [&](int idx, string built) {
      if (idx == n - 1) {
        nexts.push_back(built);
        return;
      }
      for (char c : options[idx]) {
        backtrack(idx + 1, built + c);
      }
    };
    backtrack(0, "");

    for (const string& next : nexts) {
      if (dfs(next)) {
        memo[cur] = true;
        return true;
      }
    }

    memo[cur] = false;
    return false;
  };

  return dfs(bottom);
}

// Strategy 2: DFS with memoization and immediate recursive building
// Instead of generating all next level strings explicitly, we recursively build
// the next level while backtracking, and immediately call dfs on completion.
static bool solution2(string bottom, vector<string>& allowed) {
  // Build mapping
  vector<vector<vector<char>>> mapping(6, vector<vector<char>>(6));
  for (const string& s : allowed) {
    int left = s[0] - 'A';
    int right = s[1] - 'A';
    char top = s[2];
    mapping[left][right].push_back(top);
  }

  unordered_map<string, bool> memo;

  function<bool(const string&)> dfs = [&](const string& cur) -> bool {
    if (cur.size() == 1) return true;
    if (memo.count(cur)) return memo[cur];

    int n = cur.size();
    vector<vector<char>> options(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      int left = cur[i] - 'A';
      int right = cur[i + 1] - 'A';
      const vector<char>& possible = mapping[left][right];
      if (possible.empty()) {
        memo[cur] = false;
        return false;
      }
      options[i] = possible;
    }

    // Backtracking to build next level, recursively check as soon as built
    function<bool(int, string)> backtrack = [&](int idx, string built) -> bool {
      if (idx == n - 1) {
        // Built a complete next level
        return dfs(built);
      }
      for (char c : options[idx]) {
        if (backtrack(idx + 1, built + c)) {
          return true;
        }
      }
      return false;
    };

    bool result = backtrack(0, "");
    memo[cur] = result;
    return result;
  };

  return dfs(bottom);
}

PyramidTransitionMatrixSolution::PyramidTransitionMatrixSolution() {
  setMetaInfo({.id = 756,
               .title = "Pyramid Transition Matrix",
               .url = "https://leetcode.com/problems/pyramid-transition-matrix"});
  registerStrategy("Backtracking with memoization", solution1);
  registerStrategy("DFS with immediate building", solution2);
}

bool PyramidTransitionMatrixSolution::pyramidTransition(string bottom, vector<string>& allowed) {
  return getSolution()(bottom, allowed);
}

}  // namespace problem_756
}  // namespace leetcode