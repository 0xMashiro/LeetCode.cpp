#include "leetcode/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements.h"

namespace leetcode {
namespace problem_3405 {

static constexpr int MOD = 1e9 + 7;

// 快速幂：计算 base^exp % MOD
static long long power(long long base, long long exp) {
  long long result = 1;
  base %= MOD;
  while (exp > 0) {
    if (exp & 1) result = result * base % MOD;
    base = base * base % MOD;
    exp >>= 1;
  }
  return result;
}

// 组合数计算：使用预处理阶乘和逆元
class Combination {
 public:
  Combination(int max_n) {
    fact.resize(max_n + 1);
    inv_fact.resize(max_n + 1);
    fact[0] = 1;
    for (int i = 1; i <= max_n; ++i) {
      fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[max_n] = power(fact[max_n], MOD - 2);  // 费马小定理求逆元
    for (int i = max_n - 1; i >= 0; --i) {
      inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
  }

  long long C(int n, int k) const {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
  }

 private:
  vector<long long> fact;
  vector<long long> inv_fact;
};

// 主解法：组合数学
static int solution(int n, int m, int k) {
  // 如果 k > n-1，不可能有解
  if (k > n - 1) return 0;
  
  // 如果 m == 1 且 k != n-1，不可能有解（所有元素必须相同）
  if (m == 1) {
    return (k == n - 1) ? 1 : 0;
  }
  
  // 预处理组合数，最大需要 C(n-1, k)，所以预处理到 n
  static Combination comb(100000);
  
  // C(n-1, k) * m * (m-1)^(n-1-k) % MOD
  long long ways_choose = comb.C(n - 1, k);
  long long first_element = m;
  long long diff_ways = power(m - 1, n - 1 - k);
  
  return (int)(ways_choose * first_element % MOD * diff_ways % MOD);
}

CountTheNumberOfArraysWithKMatchingAdjacentElementsSolution::
CountTheNumberOfArraysWithKMatchingAdjacentElementsSolution() {
  setMetaInfo({
    .id = 3405,
    .title = "Count the Number of Arrays with K Matching Adjacent Elements",
    .url = "https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/"
  });
  registerStrategy("Combinatorics", solution);
}

int CountTheNumberOfArraysWithKMatchingAdjacentElementsSolution::countGoodArrays(
    int n, int m, int k) {
  return getSolution()(n, m, k);
}

}  // namespace problem_3405
}  // namespace leetcode