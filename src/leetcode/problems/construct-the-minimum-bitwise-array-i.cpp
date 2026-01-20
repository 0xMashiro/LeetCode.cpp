#include "leetcode/problems/construct-the-minimum-bitwise-array-i.h"

namespace leetcode {
namespace problem_3314 {

// 策略1：暴力枚举
// 对于每个 nums[i]，从 0 开始枚举 x，检查是否满足 x | (x + 1) == nums[i]
// 时间复杂度: O(n * m)，其中 n 是数组长度，m 是 nums[i] 的最大值（≤1000）
// 空间复杂度: O(1)（不包括输出数组）
static std::vector<int> solution1(std::vector<int>& nums) {
  std::vector<int> ans;
  ans.reserve(nums.size());
  for (int n : nums) {
    int x = -1;
    // x 最大为 n-1，因为 x|(x+1) >= x+1 > x，所以 x < n
    for (int candidate = 0; candidate < n; ++candidate) {
      if ((candidate | (candidate + 1)) == n) {
        x = candidate;
        break;
      }
    }
    ans.push_back(x);
  }
  return ans;
}

// 策略2：数学推导（基于位运算性质）
// 对于给定的 n，寻找最小的 x 使得 x | (x+1) == n
// 设 k 为 x 的最低位的 0 的位置，则：
// 1. n 的第 k 位必须是 1（因为 x|(x+1) 的第 k 位为 1）
// 2. n 的低 k 位（第 0 到 k-1 位）必须全是 1
// 如果满足上述条件，则 x = n & ~(1 << k) 是一个候选解
// 我们需要找到最大的 k 满足条件（因为 k 越大，x 越小）
// 从高位向低位遍历 k，找到第一个满足条件的 k 即可得到最小 x
// 时间复杂度: O(n * log(max(nums)))
static std::vector<int> solution2(std::vector<int>& nums) {
  std::vector<int> ans;
  ans.reserve(nums.size());
  for (int n : nums) {
    int x = -1;
    // 从高位向低位遍历 k（30 足够，因为 n ≤ 1000 < 2^10）
    for (int k = 30; k >= 0; --k) {
      // 检查第 k 位是否为 1
      if (((n >> k) & 1) == 0) continue;
      // 检查低 k 位是否全为 1
      // 注意：当 k == 0 时，低 0 位默认为全 1（空真）
      if (k > 0 && (n & ((1 << k) - 1)) != ((1 << k) - 1)) continue;
      // 构造候选 x
      int candidate = n & ~(1 << k);
      // 验证条件（虽然理论上应该成立，但为了安全还是验证一下）
      if ((candidate | (candidate + 1)) == n) {
        x = candidate;
        break;
      }
    }
    ans.push_back(x);
  }
  return ans;
}

ConstructTheMinimumBitwiseArrayISolution::ConstructTheMinimumBitwiseArrayISolution() {
  setMetaInfo({.id = 3314,
               .title = "Construct the Minimum Bitwise Array I",
               .url = "https://leetcode.com/problems/construct-the-minimum-bitwise-array-i/"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("Mathematical", solution2);
}

std::vector<int> ConstructTheMinimumBitwiseArrayISolution::minBitwiseArray(std::vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3314
}  // namespace leetcode