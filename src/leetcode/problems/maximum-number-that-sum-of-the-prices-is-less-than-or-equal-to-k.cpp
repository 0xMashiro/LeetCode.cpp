#include "leetcode/problems/maximum-number-that-sum-of-the-prices-is-less-than-or-equal-to-k.h"

namespace leetcode {
namespace problem_3007 {

// 计算从 1 到 num 的 accumulated price
// 对于每个位置 p = x, 2x, 3x, ...，统计有多少个数字在该位上是 1
// 位置 p 对应的二进制位是 2^(p-1)
static long long calculateAccumulatedPrice(long long num, int x) {
  if (num <= 0) return 0;
  
  long long total = 0;
  // 遍历所有相关位置: x, 2x, 3x, ...
  // 位置 p 对应二进制中的第 p 位（从1开始计数），即 2^(p-1)
  for (int p = x; p <= 60; p += x) {
    // 第 p 位对应的值是 2^(p-1)
    long long bitValue = 1LL << (p - 1);
    // 周期是 2^p = 2 * bitValue
    long long cycle = 1LL << p;
    // 每个完整周期中，该位为 1 的数字个数是 2^(p-1) = bitValue
    
    // 数字范围是 [0, num]，共 num+1 个数字
    // 计算有多少个完整周期和余数
    long long fullCycles = (num + 1) / cycle;
    long long remainder = (num + 1) % cycle;
    
    // 完整周期贡献的 1 的个数
    long long count = fullCycles * bitValue;
    
    // 不完整的周期贡献的 1 的个数
    // 在每个周期中，该位为 1 的数字是 [bitValue, 2*bitValue - 1]
    // 即 [bitValue, cycle - 1]
    // 所以余数部分中，该位为 1 的个数是 max(0, remainder - bitValue)
    count += std::max(0LL, remainder - bitValue);
    
    total += count;
  }
  return total;
}

static long long solution1(long long k, int x) {
  long long left = 0;
  // 设置一个足够大的上界
  // 当 x 较大时（如 x=8），每个数字的 price 很小，所以答案可能比 k 大很多
  // 使用一个安全的上界，确保能覆盖所有情况
  // k 最大为 10^15，使用 4e17 作为上界足够覆盖所有情况
  long long right = 4e17;
  
  long long ans = 0;
  while (left <= right) {
    long long mid = left + (right - left) / 2;
    long long price = calculateAccumulatedPrice(mid, x);
    
    if (price <= k) {
      ans = mid;  // mid 是 cheap 的，尝试更大的
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  
  return ans;
}

MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKSolution::MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKSolution() {
  setMetaInfo({
    .id = 3007,
    .title = "Maximum Number That Sum of the Prices Is Less Than or Equal to K",
    .url = "https://leetcode.com/problems/maximum-number-that-sum-of-the-prices-is-less-than-or-equal-to-k/"
  });
  registerStrategy("Binary Search + Digit DP", solution1);
}

long long MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKSolution::findMaximumNumber(long long k, int x) {
  return getSolution()(k, x);
}

}  // namespace problem_3007
}  // namespace leetcode
