
#include "leetcode/problems/count-the-number-of-infection-sequences.h"

namespace leetcode {
namespace problem_2954 {

static const int MOD = 1e9 + 7;

// 快速幂计算 a^b % MOD
static long long power(long long a, long long b) {
  long long res = 1;
  a %= MOD;
  while (b > 0) {
    if (b & 1) res = res * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return res;
}

// 计算组合数 C(n, k) % MOD，使用预计算的阶乘
static long long comb(int n, int k, const vector<long long>& fact, const vector<long long>& invFact) {
  if (k < 0 || k > n) return 0;
  return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

static int solution1(int n, vector<int>& sick) {
  int m = sick.size();
  int totalUninfected = n - m;  // 总共需要被感染的人数
  
  if (totalUninfected == 0) return 1;
  
  // 预计算阶乘和逆阶乘（最大需要计算到 n）
  vector<long long> fact(n + 1);
  vector<long long> invFact(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = fact[i - 1] * i % MOD;
  }
  invFact[n] = power(fact[n], MOD - 2);
  for (int i = n - 1; i >= 0; i--) {
    invFact[i] = invFact[i + 1] * (i + 1) % MOD;
  }
  
  long long ans = 1;
  int remainingSteps = totalUninfected;  // 剩余需要安排的步数
  
  // 处理最左边的区间 [0, sick[0]-1]
  if (sick[0] > 0) {
    int L = sick[0];  // 区间长度
    // 只能从右边向左感染，顺序固定，方案数为 C(remainingSteps, L)
    ans = ans * comb(remainingSteps, L, fact, invFact) % MOD;
    remainingSteps -= L;
  }
  
  // 处理中间的区间 [sick[i]+1, sick[i+1]-1]
  for (int i = 0; i < m - 1; i++) {
    int L = sick[i + 1] - sick[i] - 1;  // 区间长度
    if (L == 0) continue;
    // 两边同时向内感染，每步可以选择从左边或右边（除了最后一步两边相遇）
    // 方案数 = C(remainingSteps, L) * 2^(L-1)
    ans = ans * comb(remainingSteps, L, fact, invFact) % MOD;
    ans = ans * power(2, L - 1) % MOD;
    remainingSteps -= L;
  }
  
  // 处理最右边的区间 [sick[m-1]+1, n-1]
  if (sick[m - 1] < n - 1) {
    int L = n - 1 - sick[m - 1];  // 区间长度
    // 只能从左边向右感染，顺序固定
    ans = ans * comb(remainingSteps, L, fact, invFact) % MOD;
    remainingSteps -= L;
  }
  
  return (int)ans;
}

CountTheNumberOfInfectionSequencesSolution::CountTheNumberOfInfectionSequencesSolution() {
  setMetaInfo({.id = 2954,
               .title = "Count the Number of Infection Sequences",
               .url = "https://leetcode.com/problems/count-the-number-of-infection-sequences/"});
  registerStrategy("Combinatorics", solution1);
}

int CountTheNumberOfInfectionSequencesSolution::numberOfSequence(int n, vector<int>& sick) {
  return getSolution()(n, sick);
}

}  // namespace problem_2954
}  // namespace leetcode
