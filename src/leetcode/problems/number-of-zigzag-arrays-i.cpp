#include "leetcode/problems/number-of-zigzag-arrays-i.h"

#include <vector>

namespace leetcode {
namespace problem_3699 {

static constexpr int MOD = 1'000'000'007;

// DP with prefix sums:
// dp_up[x]  = number of valid sequences ending at value x with last step up
// dp_down[x] = number of valid sequences ending at value x with last step down
// Transition:
//   new_up[x]   = sum_{y < x} down[y]
//   new_down[x] = sum_{y > x} up[y]
// Use prefix sums to compute in O(m) per layer, total O(n*m).
//
// Time: O(n * (r-l+1)), Space: O(r-l+1)
static int solution1(int n, int l, int r) {
  int m = r - l + 1;
  std::vector<int> up(m, 1), down(m, 1);  // length = 1

  for (int len = 2; len <= n; ++len) {
    // Prefix sums of down (for up transitions)
    std::vector<int> pref_down(m + 1, 0);
    for (int x = 0; x < m; ++x) {
      pref_down[x + 1] = (pref_down[x] + down[x]) % MOD;
    }

    // Suffix sums of up (for down transitions)
    std::vector<int> suff_up(m + 1, 0);
    for (int x = m - 1; x >= 0; --x) {
      suff_up[x] = (suff_up[x + 1] + up[x]) % MOD;
    }

    std::vector<int> new_up(m, 0), new_down(m, 0);
    for (int x = 0; x < m; ++x) {
      new_up[x] = pref_down[x];            // sum_{y < x} down[y]
      new_down[x] = suff_up[x + 1];        // sum_{y > x} up[y]
    }

    up = std::move(new_up);
    down = std::move(new_down);
  }

  long long ans = 0;
  for (int x = 0; x < m; ++x) {
    ans = (ans + up[x] + down[x]) % MOD;
  }
  return static_cast<int>(ans);
}

NumberOfZigzagArraysISolution::NumberOfZigzagArraysISolution() {
  setMetaInfo({.id = 3699,
               .title = "Number of ZigZag Arrays I",
               .url = "https://leetcode.com/problems/number-of-zigzag-arrays-i/"});
  registerStrategy(
      {.name = "DP with Prefix Sums",
       .expected = "Accepted",
       .time_complexity = "O(n * (r-l+1))",
       .space_complexity = "O(r-l+1)",
       .tags = {"Dynamic Programming", "Prefix Sum"}},
      solution1);
}

int NumberOfZigzagArraysISolution::zigZagArrays(int n, int l, int r) {
  return getSolution()(n, l, r);
}

}  // namespace problem_3699
}  // namespace leetcode
