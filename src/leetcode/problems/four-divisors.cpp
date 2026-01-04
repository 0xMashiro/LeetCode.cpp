#include "leetcode/problems/four-divisors.h"

namespace leetcode {
namespace problem_1390 {

// 策略1：暴力枚举，遍历每个数的所有因子
// 时间复杂度：O(N * sqrt(max(nums)))，其中 N 为数组长度
// 空间复杂度：O(1)
static int solution1(vector<int>& nums) {
  int total = 0;
  for (int n : nums) {
    int cnt = 0;
    int sum = 0;
    for (int i = 1; i * i <= n; ++i) {
      if (n % i == 0) {
        if (i == n / i) {
          ++cnt;
          sum += i;
        } else {
          cnt += 2;
          sum += i + n / i;
        }
      }
    }
    if (cnt == 4) {
      total += sum;
    }
  }
  return total;
}

// 策略2：数学方法，利用恰好有四个因子的数的性质
// 性质：一个数有恰好四个因子当且仅当它是：
//   1. 质数的立方：n = p^3 (p 为质数)
//   2. 两个不同质数的乘积：n = p * q (p, q 为不同质数)
// 时间复杂度：O(N * (π(sqrt(M)) + 预计算质数表))，其中 π(x) 为不大于 x 的质数个数
// 空间复杂度：O(M)，M = 100000
static int solution2(vector<int>& nums) {
  const int MAX_N = 100000;
  
  // 预计算质数表
  static vector<bool> is_prime(MAX_N + 1, true);
  static vector<int> primes;
  static bool initialized = false;
  
  if (!initialized) {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MAX_N; ++i) {
      if (is_prime[i]) {
        for (int j = i * i; j <= MAX_N; j += i) {
          is_prime[j] = false;
        }
      }
    }
    for (int i = 2; i <= MAX_N; ++i) {
      if (is_prime[i]) {
        primes.push_back(i);
      }
    }
    initialized = true;
  }
  
  int total = 0;
  for (int n : nums) {
    if (n <= 1) continue;
    
    // 检查是否为质数的立方
    int cbrt_val = static_cast<int>(round(pow(n, 1.0 / 3.0)));
    if (cbrt_val * cbrt_val * cbrt_val == n && is_prime[cbrt_val]) {
      int p = cbrt_val;
      total += 1 + p + p * p + p * p * p;
      continue;
    }
    
    // 检查是否为两个不同质数的乘积
    bool found = false;
    int p_found = 0, q_found = 0;
    for (int p : primes) {
      if (p * p > n) break;  // 只需要检查到 sqrt(n)
      if (n % p == 0) {
        int q = n / p;
        if (p != q && is_prime[q]) {
          p_found = p;
          q_found = q;
          found = true;
          break;
        }
        // 如果 p * p == n，但 n 不是质数的立方，则不可能有4个因子
        // 所以可以直接 break，因为质因数分解的唯一性
        break;
      }
    }
    if (found) {
      total += 1 + p_found + q_found + p_found * q_found;
    }
  }
  return total;
}

FourDivisorsSolution::FourDivisorsSolution() {
  setMetaInfo({.id = 1390,
               .title = "Four Divisors",
               .url = "https://leetcode.com/problems/four-divisors/"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("Mathematical", solution2);
}

int FourDivisorsSolution::sumFourDivisors(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_1390
}  // namespace leetcode