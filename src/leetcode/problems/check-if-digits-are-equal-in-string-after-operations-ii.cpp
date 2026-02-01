
#include "leetcode/problems/check-if-digits-are-equal-in-string-after-operations-ii.h"

namespace leetcode {
namespace problem_3463 {

// 计算 n! 中质因数 p 的个数
static int countFactor(long long n, int p) {
  int count = 0;
  while (n > 0) {
    n /= p;
    count += n;
  }
  return count;
}

// 快速幂
static long long power(long long base, long long exp, int mod) {
  long long res = 1;
  base %= mod;
  while (exp > 0) {
    if (exp & 1) res = res * base % mod;
    base = base * base % mod;
    exp >>= 1;
  }
  return res;
}

// 计算 n! mod p，排除 p 的倍数 (p 是质数)
static long long factWithoutP(long long n, int p) {
  if (n == 0) return 1;
  long long res = 1;
  // (p-1)! ≡ -1 (mod p) 由威尔逊定理
  long long cycles = n / p;
  long long remainder = n % p;
  // 每个完整周期贡献 (p-1)! ≡ -1
  if (cycles % 2 == 1) {
    res = p - 1;  // -1 mod p
  }
  // 剩余部分的阶乘
  for (long long i = 1; i <= remainder; ++i) {
    res = res * i % p;
  }
  // 递归计算 n/p 的阶乘
  res = res * factWithoutP(cycles, p) % p;
  return res;
}

// 计算 C(n, k) mod p (p 是质数)
static long long CModPrime(long long n, long long k, int p) {
  if (k < 0 || k > n) return 0;
  int cnt_p = countFactor(n, p) - countFactor(k, p) - countFactor(n - k, p);
  if (cnt_p > 0) return 0;
  
  long long numerator = factWithoutP(n, p);
  long long denominator = factWithoutP(k, p) * factWithoutP(n - k, p) % p;
  return numerator * power(denominator, p - 2, p) % p;
}

// 计算 C(n, k) mod 2
static int CMod2(long long n, long long k) {
  // C(n, k) mod 2 = 1 当且仅当 k & (n-k) == 0 (Lucas 定理的特例)
  return ((k & (n - k)) == 0) ? 1 : 0;
}

// 卢卡斯定理计算 C(n, k) mod 5
static int lucas5(long long n, long long k) {
  if (k < 0 || k > n) return 0;
  if (k == 0) return 1;
  int ni = n % 5;
  int ki = k % 5;
  if (ki > ni) return 0;
  // 小组合数表 mod 5
  static const int smallC[5][5] = {
    {1, 0, 0, 0, 0},
    {1, 1, 0, 0, 0},
    {1, 2, 1, 0, 0},
    {1, 3, 3, 1, 0},
    {1, 4, 1, 4, 1}  // C(4,2)=6≡1, C(4,3)=4
  };
  return (lucas5(n / 5, k / 5) * smallC[ni][ki]) % 5;
}

// 计算 C(n, k) mod 5
static int CMod5(long long n, long long k) {
  int cnt_5 = countFactor(n, 5) - countFactor(k, 5) - countFactor(n - k, 5);
  if (cnt_5 > 0) return 0;
  return lucas5(n, k);
}

// 中国剩余定理：已知 x ≡ a (mod 2), x ≡ b (mod 5)，求 x mod 10
static int crt(int a, int b) {
  // 2 和 5 互质，直接枚举
  for (int x = 0; x < 10; ++x) {
    if (x % 2 == a && x % 5 == b) return x;
  }
  return 0;
}

// 计算 C(n, k) mod 10
static int CMod10(long long n, long long k) {
  if (k < 0 || k > n) return 0;
  int cnt_2 = countFactor(n, 2) - countFactor(k, 2) - countFactor(n - k, 2);
  int cnt_5 = countFactor(n, 5) - countFactor(k, 5) - countFactor(n - k, 5);
  
  if (cnt_2 > 0 && cnt_5 > 0) {
    // 同时被 2 和 5 整除，即被 10 整除
    return 0;
  }
  if (cnt_2 > 0) {
    // 被 2 整除但不被 5 整除，结果只能是 0, 2, 4, 6, 8
    // 需要计算 mod 5，然后找出满足条件的偶数
    int mod5 = CMod5(n, k);
    for (int x = 0; x < 10; x += 2) {
      if (x % 5 == mod5) return x;
    }
    return 0;
  }
  if (cnt_5 > 0) {
    // 被 5 整除但不被 2 整除，结果只能是 0, 5
    // 需要计算 mod 2
    int mod2 = CMod2(n, k);
    if (mod2 == 0) return 0;
    else return 5;
  }
  
  // 既不被 2 也不被 5 整除
  int mod2 = CMod2(n, k);
  int mod5 = CMod5(n, k);
  return crt(mod2, mod5);
}

// 主解法：数学优化 O(n log n)
static bool solution(string s) {
  int n = s.size();
  if (n == 2) return s[0] == s[1];
  
  // 计算第一个数字：sum_{k=0}^{n-2} s[k] * C(n-2, k) mod 10
  // 计算第二个数字：sum_{k=0}^{n-2} s[k+1] * C(n-2, k) mod 10
  long long first = 0, second = 0;
  long long m = n - 2;
  
  for (int k = 0; k <= m; ++k) {
    int coeff = CMod10(m, k);
    first = (first + (s[k] - '0') * coeff) % 10;
    second = (second + (s[k + 1] - '0') * coeff) % 10;
  }
  
  return first == second;
}

CheckIfDigitsAreEqualInStringAfterOperationsIiSolution::CheckIfDigitsAreEqualInStringAfterOperationsIiSolution() {
  setMetaInfo({.id = 3463,
               .title = "Check If Digits Are Equal in String After Operations II",
               .url = "https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/"});
  registerStrategy("Math + CRT", solution);
}

bool CheckIfDigitsAreEqualInStringAfterOperationsIiSolution::hasSameDigits(string s) {
  return getSolution()(s);
}

}  // namespace problem_3463
}  // namespace leetcode
