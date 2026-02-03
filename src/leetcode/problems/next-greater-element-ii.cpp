#include "leetcode/problems/next-greater-element-ii.h"

namespace leetcode {
namespace problem_503 {

// 单调递减栈：遍历两遍数组，用取模处理循环
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution1(vector<int>& nums) {
  const int n = nums.size();
  vector<int> result(n, -1);
  stack<int> st;  // 存储索引

  // 遍历两遍数组，模拟循环
  for (int i = 0; i < 2 * n; ++i) {
    int idx = i % n;
    // 当前元素比栈顶元素大，说明找到了栈顶索引的下一个更大元素
    while (!st.empty() && nums[idx] > nums[st.top()]) {
      result[st.top()] = nums[idx];
      st.pop();
    }
    // 第一遍遍历时将索引入栈
    if (i < n) {
      st.push(idx);
    }
  }
  return result;
}

NextGreaterElementIiSolution::NextGreaterElementIiSolution() {
  setMetaInfo({.id = 503,
               .title = "Next Greater Element II",
               .url = "https://leetcode.com/problems/next-greater-element-ii/"});
  registerStrategy("Monotonic Stack", solution1);
}

vector<int> NextGreaterElementIiSolution::nextGreaterElements(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_503
}  // namespace leetcode
