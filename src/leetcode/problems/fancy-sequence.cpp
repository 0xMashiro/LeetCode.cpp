#include "leetcode/problems/fancy-sequence.h"

namespace leetcode {
namespace problem_1622 {

Fancy::Fancy() : curMul(1), curAdd(0) {}

long long Fancy::modPow(long long base, long long exp) {
  long long result = 1;
  base %= MOD;
  while (exp > 0) {
    if (exp & 1) {
      result = (result * base) % MOD;
    }
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return result;
}

long long Fancy::modInv(long long x) {
  // 费马小定理：x^(MOD-1) ≡ 1 (mod MOD)
  // 因此 x^(MOD-2) ≡ x^(-1) (mod MOD)
  return modPow(x, MOD - 2);
}

void Fancy::append(int val) {
  // 将 val 转换为归一化值，使得：val = (normalized * curMul + curAdd) % MOD
  // normalized = (val - curAdd) * inv(curMul) % MOD
  long long normalized = (val - curAdd + MOD) % MOD;
  normalized = (normalized * modInv(curMul)) % MOD;
  vals.push_back(normalized);
}

void Fancy::addAll(int inc) {
  curAdd = (curAdd + inc) % MOD;
}

void Fancy::multAll(int m) {
  curMul = (curMul * m) % MOD;
  curAdd = (curAdd * m) % MOD;
}

int Fancy::getIndex(int idx) {
  if (idx < 0 || idx >= (int)vals.size()) {
    return -1;
  }
  // 计算实际值：(normalized * curMul + curAdd) % MOD
  long long result = (vals[idx] * curMul + curAdd) % MOD;
  return (int)result;
}

}  // namespace problem_1622
}  // namespace leetcode
