#include "leetcode/problems/rotate-function.h"

namespace leetcode {
namespace problem_396 {

/**
 * 递推法求解 Rotate Function
 * 关键观察：F(k+1) = F(k) + sum(nums) - n * last_element
 * 
 * 证明：
 * F(k) = 0*a0 + 1*a1 + 2*a2 + ... + (n-1)*a_{n-1}
 * 顺时针旋转1位后，a_{n-1}移到首位：
 * F(k+1) = 0*a_{n-1} + 1*a0 + 2*a1 + ... + (n-1)*a_{n-2}
 * 
 * F(k+1) - F(k) = [1*a0 - 0*a0] + [2*a1 - 1*a1] + ... + [(n-1)*a_{n-2} - (n-2)*a_{n-2}] - (n-1)*a_{n-1}
 *              = a0 + a1 + ... + a_{n-2} + a_{n-1} - n*a_{n-1}
 *              = sum(nums) - n*a_{n-1}
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  if (n == 1) return 0;  // 只有一个元素时，F(0) = 0
  
  long long sum = 0;  // 使用long long防止溢出
  for (int num : nums) {
    sum += num;
  }
  
  // 计算 F(0)
  long long f = 0;
  for (int i = 0; i < n; ++i) {
    f += static_cast<long long>(i) * nums[i];
  }
  
  long long max_f = f;
  
  // 利用递推公式计算 F(1), F(2), ..., F(n-1)
  // F(k+1) = F(k) + sum - n * arr_k[last]
  // 顺时针旋转，arr_k的最后一个元素是 nums[(n-1-k) mod n] = nums[(n-1-k+n) % n]
  // 实际上，当顺时针旋转k次，最后一个元素是 nums[(n-k) % n] 或 nums[(n-1-k+n) % n]
  // 简化：arr_k的最后一个元素是 nums[(n-1-k+n) % n] = nums[(n-1-k) % n + n % n]
  // 对于k次旋转，arr_k = [nums[n-k], nums[n-k+1], ..., nums[n-1], nums[0], ..., nums[n-k-1]]
  // arr_k[n-1] = nums[n-k-1] = nums[(n-k-1+n) % n]
  // 当k=0, arr_0[n-1] = nums[n-1]
  // 当k=1, arr_1[n-1] = nums[n-2]
  // 当k=i, arr_i[n-1] = nums[(n-1-i+n) % n] = nums[(n-1-i)] (当i<n)
  
  for (int k = 0; k < n - 1; ++k) {
    // arr_k的最后一个元素，顺时针旋转k次后，最后一个元素是 nums[(n-1-k+n) % n]
    int last_element = nums[(n - 1 - k + n) % n];
    f = f + sum - static_cast<long long>(n) * last_element;
    max_f = max(max_f, f);
  }
  
  return static_cast<int>(max_f);
}

/**
 * 优化的递推实现
 * 直接跟踪当前数组的最后一个元素
 */
static int solution2(vector<int>& nums) {
  const int n = nums.size();
  if (n == 1) return 0;
  
  long long sum = 0;
  for (int num : nums) sum += num;
  
  long long f = 0;
  for (int i = 0; i < n; ++i) {
    f += static_cast<long long>(i) * nums[i];
  }
  
  long long max_f = f;
  
  // 从后往前遍历，因为顺时针旋转时，最后一个元素依次是 nums[n-1], nums[n-2], ..., nums[0]
  for (int i = n - 1; i > 0; --i) {
    f = f + sum - static_cast<long long>(n) * nums[i];
    max_f = max(max_f, f);
  }
  
  return static_cast<int>(max_f);
}

RotateFunctionSolution::RotateFunctionSolution() {
  setMetaInfo({.id = 396,
               .title = "Rotate Function",
               .url = "https://leetcode.com/problems/rotate-function/"});
  registerStrategy("Iterative Formula", solution1);
  registerStrategy("Optimized Iterative", solution2);
}

int RotateFunctionSolution::maxRotateFunction(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_396
}  // namespace leetcode
