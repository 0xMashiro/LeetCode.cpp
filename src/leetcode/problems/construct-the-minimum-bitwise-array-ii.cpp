#include "leetcode/problems/construct-the-minimum-bitwise-array-ii.h"

namespace leetcode {
namespace problem_3315 {

// 策略1：直接计算后缀连续1的个数，然后减去相应位
// 时间复杂度: O(n log MAX)，空间复杂度: O(1)
static vector<int> solution1(vector<int>& nums) {
  vector<int> ans;
  ans.reserve(nums.size());
  for (int num : nums) {
    // 计算从最低位开始的连续1的个数
    int suffix_ones = 0;
    int temp = num;
    while ((temp & 1) == 1) {
      ++suffix_ones;
      temp >>= 1;
    }
    // 如果后缀连续1的个数为0，则无解
    if (suffix_ones == 0) {
      ans.push_back(-1);
    } else {
      // 最小x = num - (1 << (suffix_ones - 1))
      ans.push_back(num - (1 << (suffix_ones - 1)));
    }
  }
  return ans;
}

// 策略2：使用位运算技巧，直接构造x
// 时间复杂度: O(n log MAX)，空间复杂度: O(1)
static vector<int> solution2(vector<int>& nums) {
  vector<int> ans;
  ans.reserve(nums.size());
  for (int num : nums) {
    // 找到最低的0位的位置（从0开始），实际上就是后缀连续1的个数
    int suffix_ones = 0;
    int temp = num;
    while ((temp & 1) == 1) {
      ++suffix_ones;
      temp >>= 1;
    }
    if (suffix_ones == 0) {
      ans.push_back(-1);
    } else {
      // 构造mask，将第(suffix_ones-1)位清零
      int mask = 1 << (suffix_ones - 1);
      ans.push_back(num & ~mask);
    }
  }
  return ans;
}

// 策略3：使用内置函数__builtin_ctz计算后缀0的个数，从而得到连续1的个数
// 注意：__builtin_ctz(0)是未定义的，但这里temp = num ^ ((1 << suffix_ones) - 1)可能为0
// 更安全的方法：直接计算连续1的个数
// 时间复杂度: O(n)，空间复杂度: O(1)
static vector<int> solution3(vector<int>& nums) {
  vector<int> ans;
  ans.reserve(nums.size());
  for (int num : nums) {
    // 计算后缀连续1的个数：找到最低的0位
    // 方法：计算 (num ^ (num + 1)) >> 1 的尾部0的个数？需要推导
    // 更简单：直接循环
    int suffix_ones = 0;
    int temp = num;
    while ((temp & 1) == 1) {
      ++suffix_ones;
      temp >>= 1;
    }
    if (suffix_ones == 0) {
      ans.push_back(-1);
    } else {
      ans.push_back(num - (1 << (suffix_ones - 1)));
    }
  }
  return ans;
}

ConstructTheMinimumBitwiseArrayIiSolution::ConstructTheMinimumBitwiseArrayIiSolution() {
  setMetaInfo({.id = 3315,
               .title = "Construct the Minimum Bitwise Array II",
               .url = "https://leetcode.com/problems/construct-the-minimum-bitwise-array-ii/"});
  registerStrategy({.name = "Count Suffix Ones"}, solution1);
  registerStrategy({.name = "Bit Mask"}, solution2);
  registerStrategy({.name = "Alternative"}, solution3);
}

vector<int> ConstructTheMinimumBitwiseArrayIiSolution::minBitwiseArray(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3315
}  // namespace leetcode