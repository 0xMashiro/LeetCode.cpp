#include "leetcode/problems/n-repeated-element-in-size-2n-array.h"

namespace leetcode {
namespace problem_961 {

// 哈希表统计：遍历数组，当某个元素第二次出现时立即返回
// 时间复杂度: O(n)，空间复杂度: O(n)
static int solution1(vector<int>& nums) {
  unordered_map<int, int> count;
  for (int num : nums) {
    if (count[num]++ > 0) return num;  // 发现重复元素
  }
  return -1;  // 根据题目保证不会执行到这里
}

// 鸽巢原理：检查连续三个位置，重复元素必然在相邻两个或间隔一个的位置出现
// 时间复杂度: O(n)，空间复杂度: O(1)
static int solution2(vector<int>& nums) {
  int n = nums.size();
  // 检查相邻的两个元素
  for (int i = 0; i < n - 1; ++i) {
    if (nums[i] == nums[i + 1]) return nums[i];
  }
  // 检查间隔为2的元素（处理类似[1,2,1,3,1,4,1,5]的情况）
  for (int i = 0; i < n - 2; ++i) {
    if (nums[i] == nums[i + 2]) return nums[i];
  }
  // 根据题目保证不会执行到这里
  return nums[0];
}

NRepeatedElementInSize2nArraySolution::NRepeatedElementInSize2nArraySolution() {
  setMetaInfo({.id = 961,
               .title = "N-Repeated Element in Size 2N Array",
               .url = "https://leetcode.com/problems/n-repeated-element-in-size-2n-array/"});
  registerStrategy("Hash Table", solution1);
  registerStrategy("Pigeonhole Principle", solution2);
}

int NRepeatedElementInSize2nArraySolution::repeatedNTimes(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_961
}  // namespace leetcode