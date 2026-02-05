
#include "leetcode/problems/transformed-array.h"

namespace leetcode {
namespace problem_3379 {

// 直接模拟
// 对于每个位置，根据 nums[i] 的正负决定移动方向
// 由于是环形数组，使用取模运算处理越界
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution1(vector<int>& nums) {
  const int n = nums.size();
  vector<int> result(n);
  
  for (int i = 0; i < n; ++i) {
    if (nums[i] == 0) {
      result[i] = 0;
    } else {
      // 计算移动步数（带符号）
      int steps = nums[i];
      // 计算目标索引
      int target = (i + steps) % n;
      // 处理负数取模（C++负数取模结果可能为负）
      if (target < 0) {
        target += n;
      }
      result[i] = nums[target];
    }
  }
  
  return result;
}

TransformedArraySolution::TransformedArraySolution() {
  setMetaInfo({.id = 3379,
               .title = "Transformed Array",
               .url = "https://leetcode.com/problems/transformed-array/"});
  registerStrategy("Simulation", solution1);
}

vector<int> TransformedArraySolution::constructTransformedArray(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3379
}  // namespace leetcode
