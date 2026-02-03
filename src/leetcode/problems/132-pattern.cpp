
#include "leetcode/problems/132-pattern.h"

namespace leetcode {
namespace problem_456 {

// 单调栈解法
// 预处理每个位置左边的最小值，然后从右向左遍历
// 维护一个单调递减栈和一个"次大值"变量
// 时间复杂度: O(n), 空间复杂度: O(n)
static bool solution1(vector<int>& nums) {
  const int n = nums.size();
  if (n < 3) return false;

  // 预处理：min_left[i] 表示 nums[0..i] 的最小值
  vector<int> min_left(n);
  min_left[0] = nums[0];
  for (int i = 1; i < n; ++i) {
    min_left[i] = std::min(min_left[i - 1], nums[i]);
  }

  // 单调栈（递减），存储的是 nums[j] 的值
  // 从右向左遍历，找是否存在满足条件的 k
  stack<int> st;
  // second 表示右边找到的满足 min_left[j] < second < nums[j] 的最大值
  // 也就是"2"的位置候选
  for (int j = n - 1; j >= 0; --j) {
    // 如果当前元素就是左边最小值，不可能作为"3"
    if (nums[j] == min_left[j]) continue;

    // 维护单调递减栈：栈顶是当前最大值
    // 弹出所有小于等于 min_left[j] 的元素，因为它们不能作为"2"
    while (!st.empty() && st.top() <= min_left[j]) {
      st.pop();
    }

    // 如果栈不为空，且栈顶小于 nums[j]，则找到132模式
    // 栈顶就是"2"，min_left[j] 是"1"，nums[j] 是"3"
    if (!st.empty() && st.top() < nums[j]) {
      return true;
    }

    // 将当前元素入栈，作为后面元素的候选"2"
    st.push(nums[j]);
  }

  return false;
}

// 优化版本：使用一个变量 second 代替栈的复杂逻辑
// 时间复杂度: O(n), 空间复杂度: O(n)（预处理数组）
static bool solution2(vector<int>& nums) {
  const int n = nums.size();
  if (n < 3) return false;

  vector<int> min_left(n);
  min_left[0] = nums[0];
  for (int i = 1; i < n; ++i) {
    min_left[i] = std::min(min_left[i - 1], nums[i]);
  }

  stack<int> st;
  for (int j = n - 1; j >= 0; --j) {
    if (nums[j] > min_left[j]) {
      // 维护栈：确保栈顶大于 min_left[j]
      while (!st.empty() && st.top() <= min_left[j]) {
        st.pop();
      }
      // 检查是否找到132模式
      if (!st.empty() && st.top() < nums[j]) {
        return true;
      }
      st.push(nums[j]);
    }
  }

  return false;
}

Pattern132Solution::Pattern132Solution() {
  setMetaInfo({.id = 456,
               .title = "132 Pattern",
               .url = "https://leetcode.com/problems/132-pattern/"});
  registerStrategy("Monotonic Stack", solution1);
  registerStrategy("Optimized Stack", solution2);
}

bool Pattern132Solution::find132pattern(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_456
}  // namespace leetcode
