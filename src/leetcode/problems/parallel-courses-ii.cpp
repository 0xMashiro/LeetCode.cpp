#include "leetcode/problems/parallel-courses-ii.h"

namespace leetcode {
namespace problem_1494 {

static int solution1(int n, vector<vector<int>>& relations, int k) {
  // pre[i] = bitmask of prerequisites for course i (0-indexed)
  vector<int> pre(n, 0);
  for (auto& rel : relations) {
    int prev = rel[0] - 1;
    int next = rel[1] - 1;
    pre[next] |= (1 << prev);
  }

  int total = 1 << n;
  const int INF = 1e9;
  vector<int> dp(total, INF);
  dp[0] = 0;

  // Precompute count of bits for each mask (for quick subset size check)
  vector<int> bitCount(total, 0);
  for (int mask = 1; mask < total; ++mask) {
    bitCount[mask] = bitCount[mask >> 1] + (mask & 1);
  }

  for (int mask = 0; mask < total; ++mask) {
    if (dp[mask] == INF) continue;

    // Compute available courses: not taken yet, and all prerequisites satisfied
    int available = 0;
    for (int i = 0; i < n; ++i) {
      if (!(mask & (1 << i)) && (pre[i] & mask) == pre[i]) {
        available |= (1 << i);
      }
    }

    if (available == 0) continue;

    // If we can take all available courses in one semester (within limit k)
    if (bitCount[available] <= k) {
      dp[mask | available] = min(dp[mask | available], dp[mask] + 1);
      continue;
    }

    // Enumerate subsets of available that have size >= 1 and <= k
    // Use submask enumeration technique
    for (int take = (available - 1) & available; take; take = (take - 1) & available) {
      if (bitCount[take] > k) continue;
      dp[mask | take] = min(dp[mask | take], dp[mask] + 1);
    }
    // Also consider taking exactly 1 course
    for (int i = 0; i < n; ++i) {
      if (available & (1 << i)) {
        dp[mask | (1 << i)] = min(dp[mask | (1 << i)], dp[mask] + 1);
      }
    }
  }

  return dp[total - 1];
}

ParallelCoursesIiSolution::ParallelCoursesIiSolution() {
  setMetaInfo({
      .id = 1494,
      .title = "Parallel Courses II",
      .url = "https://leetcode.com/problems/parallel-courses-ii"
  });
  registerStrategy({.name = "Brute Force"}, solution1);
}

int ParallelCoursesIiSolution::minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
  return getSolution()(n, relations, k);
}

}  // namespace problem_1494
}  // namespace leetcode
