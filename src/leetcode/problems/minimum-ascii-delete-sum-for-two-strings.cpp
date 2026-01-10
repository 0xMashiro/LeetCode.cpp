#include "leetcode/problems/minimum-ascii-delete-sum-for-two-strings.h"

namespace leetcode {
namespace problem_712 {

namespace {

// Helper function to compute ASCII sum of a string
static int asciiSum(const string& s) {
  int sum = 0;
  for (char c : s) {
    sum += static_cast<int>(c);
  }
  return sum;
}

// Strategy 1: Bottom-up DP with 2D table
static int solution1(string s1, string s2) {
  const int m = s1.size();
  const int n = s2.size();
  
  // dp[i][j]: maximum ASCII sum of common subsequence between
  // first i chars of s1 and first j chars of s2
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + static_cast<int>(s1[i - 1]);
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  
  int total1 = asciiSum(s1);
  int total2 = asciiSum(s2);
  return total1 + total2 - 2 * dp[m][n];
}

// Strategy 2: Space-optimized DP using two 1D arrays
static int solution2(string s1, string s2) {
  const int m = s1.size();
  const int n = s2.size();
  
  // Use two rows: prev and curr
  vector<int> prev(n + 1, 0);
  vector<int> curr(n + 1, 0);
  
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        curr[j] = prev[j - 1] + static_cast<int>(s1[i - 1]);
      } else {
        curr[j] = max(prev[j], curr[j - 1]);
      }
    }
    swap(prev, curr);
    // Reset curr to zeros for next iteration (not strictly needed as we overwrite)
    fill(curr.begin(), curr.end(), 0);
  }
  
  int total1 = asciiSum(s1);
  int total2 = asciiSum(s2);
  return total1 + total2 - 2 * prev[n];
}

// Strategy 3: Top-down memoization (recursive with memo)
static int memoizationHelper(const string& s1, const string& s2, 
                             int i, int j, vector<vector<int>>& memo) {
  const int m = s1.size();
  const int n = s2.size();
  
  if (i == m || j == n) return 0;
  if (memo[i][j] != -1) return memo[i][j];
  
  int result;
  if (s1[i] == s2[j]) {
    result = memoizationHelper(s1, s2, i + 1, j + 1, memo) + static_cast<int>(s1[i]);
  } else {
    int skip1 = memoizationHelper(s1, s2, i + 1, j, memo);
    int skip2 = memoizationHelper(s1, s2, i, j + 1, memo);
    result = max(skip1, skip2);
  }
  
  memo[i][j] = result;
  return result;
}

static int solution3(string s1, string s2) {
  const int m = s1.size();
  const int n = s2.size();
  
  vector<vector<int>> memo(m, vector<int>(n, -1));
  int maxCommon = memoizationHelper(s1, s2, 0, 0, memo);
  
  int total1 = asciiSum(s1);
  int total2 = asciiSum(s2);
  return total1 + total2 - 2 * maxCommon;
}

}  // namespace

MinimumAsciiDeleteSumForTwoStringsSolution::MinimumAsciiDeleteSumForTwoStringsSolution() {
  setMetaInfo({.id = 712,
               .title = "Minimum ASCII Delete Sum for Two Strings",
               .url = "https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/"});
  registerStrategy("Bottom-up DP (2D table)", solution1);
  registerStrategy("Space-optimized DP (1D arrays)", solution2);
  registerStrategy("Top-down memoization", solution3);
}

int MinimumAsciiDeleteSumForTwoStringsSolution::minimumDeleteSum(string s1, string s2) {
  return getSolution()(s1, s2);
}

}  // namespace problem_712
}  // namespace leetcode