#include "leetcode/problems/next-greater-element-i.h"

namespace leetcode {
namespace problem_496 {

// 暴力解法：对于 nums1 中的每个元素，在 nums2 中找到位置后向右扫描
// 时间复杂度: O(nums1.length * nums2.length)
// 空间复杂度: O(1)，不包括返回值
static vector<int> solution1(vector<int>& nums1, vector<int>& nums2) {
  const int m = nums1.size();
  const int n = nums2.size();
  vector<int> ans(m, -1);
  
  for (int i = 0; i < m; ++i) {
    // 在 nums2 中找到 nums1[i] 的位置
    int j = 0;
    while (j < n && nums2[j] != nums1[i]) {
      ++j;
    }
    // 向右查找第一个更大的元素
    for (++j; j < n; ++j) {
      if (nums2[j] > nums1[i]) {
        ans[i] = nums2[j];
        break;
      }
    }
  }
  
  return ans;
}

// 单调栈 + 哈希表优化
// 思路：用单调递减栈预处理 nums2，得到每个元素的下一个更大元素
// 时间复杂度: O(nums1.length + nums2.length)
// 空间复杂度: O(nums2.length)
static vector<int> solution2(vector<int>& nums1, vector<int>& nums2) {
  const int m = nums1.size();
  const int n = nums2.size();
  
  // 用单调栈求 nums2 中每个元素的下一个更大元素
  unordered_map<int, int> nextGreater;  // num -> next greater element
  stack<int> stk;  // 单调递减栈，存储元素值
  
  for (int i = 0; i < n; ++i) {
    // 当前元素比栈顶元素大，说明当前元素是栈顶元素的下一个更大元素
    while (!stk.empty() && nums2[i] > stk.top()) {
      nextGreater[stk.top()] = nums2[i];
      stk.pop();
    }
    stk.push(nums2[i]);
  }
  // 栈中剩余元素没有下一个更大元素，默认为 -1
  
  // 查询 nums1 中每个元素的结果
  vector<int> ans(m);
  for (int i = 0; i < m; ++i) {
    auto it = nextGreater.find(nums1[i]);
    ans[i] = (it != nextGreater.end()) ? it->second : -1;
  }
  
  return ans;
}

NextGreaterElementISolution::NextGreaterElementISolution() {
  setMetaInfo({.id = 496,
               .title = "Next Greater Element I",
               .url = "https://leetcode.com/problems/next-greater-element-i/"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("Monotonic Stack", solution2);
}

vector<int> NextGreaterElementISolution::nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
  return getSolution()(nums1, nums2);
}

}  // namespace problem_496
}  // namespace leetcode
