
#include "leetcode/problems/get-maximum-in-generated-array.h"

namespace leetcode {
namespace problem_1646 {

// 直接模拟生成数组并找最大值
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(int n) {
  if (n <= 1) return n;
  
  vector<int> nums(n + 1, 0);
  nums[0] = 0;
  nums[1] = 1;
  int max_val = 1;
  
  for (int i = 1; i <= n; ++i) {
    // 生成偶数位置 2*i
    if (2 * i <= n) {
      nums[2 * i] = nums[i];
      max_val = max(max_val, nums[2 * i]);
    }
    // 生成奇数位置 2*i+1
    if (2 * i + 1 <= n) {
      nums[2 * i + 1] = nums[i] + nums[i + 1];
      max_val = max(max_val, nums[2 * i + 1]);
    }
  }
  
  return max_val;
}

GetMaximumInGeneratedArraySolution::GetMaximumInGeneratedArraySolution() {
  setMetaInfo({.id = 1646,
               .title = "Get Maximum in Generated Array",
               .url = "https://leetcode.com/problems/get-maximum-in-generated-array/"});
  registerStrategy("Simulation", solution1);
}

int GetMaximumInGeneratedArraySolution::getMaximumGenerated(int n) {
  return getSolution()(n);
}

}  // namespace problem_1646
}  // namespace leetcode
