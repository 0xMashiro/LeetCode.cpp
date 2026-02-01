#include "leetcode/core.h"

namespace leetcode {
namespace problem_1622 {

/**
 * Fancy Sequence 实现
 * 
 * 思路：懒惰标记 + 模逆元
 * - 维护当前的累积乘法因子 (curMul) 和加法因子 (curAdd)
 * - 对于每个 append 的值，记录其归一化后的值 (normalized)
 * - addAll(inc): curAdd = (curAdd + inc) % MOD
 * - multAll(m): curMul = (curMul * m) % MOD; curAdd = (curAdd * m) % MOD
 * - getIndex(idx): 返回 (normalized[idx] * curMul + curAdd) % MOD
 * 
 * 归一化：val = (normalized * curMul + curAdd) % MOD
 * 因此：normalized = (val - curAdd) * inv(curMul) % MOD
 * 
 * 时间复杂度：所有操作均为 O(log MOD)（由于快速幂求逆元）
 * 空间复杂度：O(n)，n 为 append 次数
 */
class Fancy {
 public:
  Fancy();

  void append(int val);

  void addAll(int inc);

  void multAll(int m);

  int getIndex(int idx);

 private:
  static const int MOD = 1000000007;
  
  // 快速幂求模逆元（费马小定理，MOD 是质数）
  long long modPow(long long base, long long exp);
  
  // 求 x 的模逆元
  long long modInv(long long x);

  vector<long long> vals;  // 存储归一化后的值
  long long curMul;        // 当前累积乘法因子
  long long curAdd;        // 当前累积加法因子
};

}  // namespace problem_1622
}  // namespace leetcode
