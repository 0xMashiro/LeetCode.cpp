#include "leetcode/problems/neither-minimum-nor-maximum.h"

namespace leetcode {
namespace problem_2733 {

// 方法1：遍历找最小最大值，再找中间值
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(vector<int>& nums) {
  int n = nums.size();
  if (n < 3) return -1;
  
  int minVal = nums[0];
  int maxVal = nums[0];
  
  for (int num : nums) {
    minVal = min(minVal, num);
    maxVal = max(maxVal, num);
  }
  
  for (int num : nums) {
    if (num != minVal && num != maxVal) {
      return num;
    }
  }
  
  return -1;
}

// 方法2：只需要看前3个数，排序后取中间的
// 因为数组元素互不相同，前3个数中必有一个既不是最小也不是最大
// 时间复杂度: O(1), 空间复杂度: O(1)
static int solution2(vector<int>& nums) {
  int n = nums.size();
  if (n < 3) return -1;
  
  int a = nums[0], b = nums[1], c = nums[2];
  
  // 返回中间值
  if ((a > b && a < c) || (a < b && a > c)) return a;
  if ((b > a && b < c) || (b < a && b > c)) return b;
  return c;
}

NeitherMinimumNorMaximumSolution::NeitherMinimumNorMaximumSolution() {
  setMetaInfo({
    .id = 2733,
    .title = "Neither Minimum nor Maximum",
    .url = "https://leetcode.com/problems/neither-minimum-nor-maximum/"
  });
  registerStrategy("Find Min/Max then Search", solution1);
  registerStrategy("First Three Elements", solution2);
}

int NeitherMinimumNorMaximumSolution::findNonMinOrMax(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2733
}  // namespace leetcode
