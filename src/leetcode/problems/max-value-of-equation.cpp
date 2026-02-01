#include "leetcode/problems/max-value-of-equation.h"

namespace leetcode {
namespace problem_1499 {

/**
 * 单调队列优化解法
 * 
 * 关键变形：由于点按 x 严格递增，对于 i < j 有 |xi - xj| = xj - xi
 * 所以方程 yi + yj + |xi - xj| = yi + yj + xj - xi = (yj + xj) + (yi - xi)
 * 
 * 对于固定的 j，我们需要在满足 xj - xi <= k 的 i 中，找到 (yi - xi) 的最大值
 * 
 * 算法：
 * 1. 使用双端队列维护候选点，存储 (xi, yi - xi)
 * 2. 队列保持单调递减（按 yi - xi 值）
 * 3. 遍历每个点 j：
 *    - 移除队首不满足 xj - xi <= k 的元素
 *    - 如果队列非空，计算最大值候选
 *    - 将当前点加入队尾，保持单调性
 * 
 * 时间复杂度：O(n)，每个元素入队出队各一次
 * 空间复杂度：O(n)
 */
static int solution1(vector<vector<int>>& points, int k) {
  // 双端队列存储 pair<xi, yi - xi>
  deque<pair<int, int>> dq;
  int result = INT_MIN;
  
  for (const auto& point : points) {
    int xj = point[0];
    int yj = point[1];
    
    // 移除不满足 xj - xi <= k 的队首元素
    while (!dq.empty() && xj - dq.front().first > k) {
      dq.pop_front();
    }
    
    // 如果队列非空，计算候选值
    if (!dq.empty()) {
      int candidate = yj + xj + dq.front().second;
      result = max(result, candidate);
    }
    
    // 计算当前点的 (yi - xi) 值
    int val = yj - xj;
    
    // 保持队列单调递减，移除队尾比当前值小的元素
    while (!dq.empty() && dq.back().second <= val) {
      dq.pop_back();
    }
    
    // 将当前点加入队尾
    dq.emplace_back(xj, val);
  }
  
  return result;
}

MaxValueOfEquationSolution::MaxValueOfEquationSolution() {
  setMetaInfo({.id = 1499,
               .title = "Max Value of Equation",
               .url = "https://leetcode.com/problems/max-value-of-equation/"});
  registerStrategy("Monotonic Deque", solution1);
}

int MaxValueOfEquationSolution::findMaxValueOfEquation(vector<vector<int>>& points, int k) {
  return getSolution()(points, k);
}

}  // namespace problem_1499
}  // namespace leetcode
