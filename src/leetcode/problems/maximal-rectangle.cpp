#include "leetcode/problems/maximal-rectangle.h"

namespace leetcode {
namespace problem_85 {

// 解法1：单调栈（将问题转化为直方图最大矩形问题）
// 时间复杂度: O(rows * cols)，空间复杂度: O(cols)
static int solution1(vector<vector<char>>& matrix) {
  if (matrix.empty()) return 0;
  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<int> heights(cols, 0);
  int max_area = 0;

  for (int i = 0; i < rows; ++i) {
    // 更新当前行的高度数组
    for (int j = 0; j < cols; ++j) {
      if (matrix[i][j] == '1') {
        heights[j] += 1;
      } else {
        heights[j] = 0;
      }
    }

    // 单调栈计算直方图最大矩形面积
    stack<int> st;
    for (int j = 0; j <= cols; ++j) {
      int h = (j == cols) ? 0 : heights[j];
      while (!st.empty() && h < heights[st.top()]) {
        int height = heights[st.top()];
        st.pop();
        int width = st.empty() ? j : j - st.top() - 1;
        max_area = max(max_area, height * width);
      }
      st.push(j);
    }
  }

  return max_area;
}

// 解法2：动态规划（使用 left, right, height 数组）
// 时间复杂度: O(rows * cols)，空间复杂度: O(cols)
static int solution2(vector<vector<char>>& matrix) {
  if (matrix.empty()) return 0;
  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<int> height(cols, 0);
  vector<int> left(cols, 0);
  vector<int> right(cols, cols);
  int max_area = 0;

  for (int i = 0; i < rows; ++i) {
    int cur_left = 0, cur_right = cols;

    // 更新 height 和 left
    for (int j = 0; j < cols; ++j) {
      if (matrix[i][j] == '1') {
        height[j]++;
        left[j] = max(left[j], cur_left);
      } else {
        height[j] = 0;
        left[j] = 0;
        cur_left = j + 1;
      }
    }

    // 更新 right
    for (int j = cols - 1; j >= 0; --j) {
      if (matrix[i][j] == '1') {
        right[j] = min(right[j], cur_right);
      } else {
        right[j] = cols;
        cur_right = j;
      }
    }

    // 计算当前行的最大矩形面积
    for (int j = 0; j < cols; ++j) {
      max_area = max(max_area, height[j] * (right[j] - left[j]));
    }
  }

  return max_area;
}

MaximalRectangleSolution::MaximalRectangleSolution() {
  setMetaInfo({.id = 85,
               .title = "Maximal Rectangle",
               .url = "https://leetcode.com/problems/maximal-rectangle/"});
  registerStrategy("Monotonic Stack", solution1);
  registerStrategy("Dynamic Programming", solution2);
}

int MaximalRectangleSolution::maximalRectangle(vector<vector<char>>& matrix) {
  return getSolution()(matrix);
}

}  // namespace problem_85
}  // namespace leetcode