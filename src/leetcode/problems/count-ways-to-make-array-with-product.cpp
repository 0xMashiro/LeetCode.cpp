#include "leetcode/problems/count-ways-to-make-array-with-product.h"

namespace leetcode {
namespace problem_1735 {

static const int MOD = 1000000007;
static const int MAX_K = 10000;
static const int MAX_A = 15;

static long long modPow(long long base, long long exp, long long mod) {
  long long result = 1;
  base %= mod;
  while (exp > 0) {
    if (exp & 1) result = result * base % mod;
    base = base * base % mod;
    exp >>= 1;
  }
  return result;
}

class Combination {
 public:
  vector<long long> fact, invFact;

  Combination(int n) {
    fact.resize(n + 1);
    invFact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
      fact[i] = fact[i - 1] * i % MOD;
    }
    invFact[n] = modPow(fact[n], MOD - 2, MOD);
    for (int i = n - 1; i >= 0; --i) {
      invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }
  }

  long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
  }
};

static vector<int> sieve(int n) {
  vector<int> primes;
  vector<bool> isPrime(n + 1, true);
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i <= n; ++i) {
    if (isPrime[i]) primes.push_back(i);
    for (size_t j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
      isPrime[i * primes[j]] = false;
      if (i % primes[j] == 0) break;
    }
  }
  return primes;
}

static vector<int> solution(vector<vector<int>> &queries) {
  static vector<int> primes = sieve(MAX_K);
  static Combination comb(MAX_K + MAX_A);

  vector<int> answer;
  answer.reserve(queries.size());

  for (const auto &query : queries) {
    int n = query[0];
    int k = query[1];
    long long ways = 1;

    int tempK = k;
    for (int p : primes) {
      if (p * p > tempK) break;
      if (tempK % p == 0) {
        int cnt = 0;
        while (tempK % p == 0) {
          tempK /= p;
          ++cnt;
        }
        ways = ways * comb.C(cnt + n - 1, cnt) % MOD;
      }
    }
    if (tempK > 1) {
      ways = ways * n % MOD;
    }

    answer.push_back((int)ways);
  }

  return answer;
}

CountWaysToMakeArrayWithProductSolution::CountWaysToMakeArrayWithProductSolution() {
  setMetaInfo({.id = 1735,
               .title = "Count Ways to Make Array With Product",
               .url = "https://leetcode.com/problems/count-ways-to-make-array-with-product/"});
  registerStrategy("Prime Factorization + Combination", solution);
}

vector<int> CountWaysToMakeArrayWithProductSolution::waysToFillArray(
    vector<vector<int>> &queries) {
  return getSolution()(queries);
}

}  // namespace problem_1735
}  // namespace leetcode
