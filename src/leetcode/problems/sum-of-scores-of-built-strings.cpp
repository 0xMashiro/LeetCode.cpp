#include "leetcode/problems/sum-of-scores-of-built-strings.h"

namespace leetcode {
namespace problem_2223 {

static long solution1(string s) {
  int n = s.size();
  if (n == 0) return 0L;
  
  // Z-algorithm: z[i] = LCP of s and s[i..]
  vector<int> z(n, 0);
  // z[0] is defined as n (the whole string matches itself)
  z[0] = n;
  
  int l = 0, r = 0;
  for (int i = 1; i < n; ++i) {
    if (i <= r) {
      z[i] = min(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  
  long total = 0;
  for (int i = 0; i < n; ++i) {
    total += z[i];
  }
  return total;
}

SumOfScoresOfBuiltStringsSolution::SumOfScoresOfBuiltStringsSolution() {
  setMetaInfo({
      .id = 2223,
      .title = "Sum of Scores of Built Strings",
      .url = "https://leetcode.com/problems/sum-of-scores-of-built-strings"
  });
  registerStrategy("Brute Force", solution1);
}

long SumOfScoresOfBuiltStringsSolution::sumScores(string s) {
  return getSolution()(s);
}

}  // namespace problem_2223
}  // namespace leetcode
