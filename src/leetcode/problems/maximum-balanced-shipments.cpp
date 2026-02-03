#include "leetcode/problems/maximum-balanced-shipments.h"

namespace leetcode {
namespace problem_3638 {

// 动态规划 + 单调栈
// dp[i] 表示考虑前 i 个元素（0到i-1）能形成的最大平衡发货数
// 对于每个位置 i，我们寻找以 i-1 结尾的平衡发货
//
// 关键观察：对于以位置 j 结尾的发货，如果存在一个起始位置 i 使得 [i,j] 平衡
// 我们需要找最大的 dp[i] + 1
//
// 优化：使用单调递减栈维护可能的起始位置
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<int>& weight) {
  const int n = weight.size();
  if (n < 2) return 0;
  
  // dp[i] 表示前 i 个元素的最大发货数
  vector<int> dp(n + 1, 0);
  
  // 单调递减栈，存储的是位置，对应的 weight 值递减
  // 栈中存储可能成为未来平衡发货起点的位置
  vector<int> stack;
  
  for (int i = 0; i < n; ++i) {
    // 默认不选当前元素
    dp[i + 1] = dp[i];
    
    // 维护单调递减栈：移除栈顶小于等于当前元素的
    // 这些元素不可能成为更短平衡发货的起点
    while (!stack.empty() && weight[stack.back()] <= weight[i]) {
      stack.pop_back();
    }
    
    // 现在栈顶（如果存在）是左边第一个大于 weight[i] 的位置
    // 这意味着从栈顶位置+1 到 i，最大值是 weight[栈顶]
    // 但我们需要找到以 i 结尾的平衡发货
    
    // 实际上，我们换个思路：
    // 对于当前元素 weight[i]，我们想找以它结尾的最短平衡发货
    // 即找最大的 j，使得 max(weight[j..i]) > weight[i]
    // 由于栈是递减的，栈中元素都 > weight[i]
    
    // 我们需要找到栈中使得 dp[j+1] 最大的那个 j
    // 但我们需要找的是以 i 结尾的平衡发货的起点
    
    // 重新思考：栈中存储的是递减的位置
    // 对于当前 i，栈顶是左边最近的 > weight[i] 的位置
    // 从栈顶+1 到 i-1 的元素都 <= weight[i]
    // 所以如果从某个位置 k (<= 栈顶) 开始到 i，max 会是 weight[栈顶]
    // 我们需要 max(weight[k..i]) > weight[i]，所以 k 必须在栈顶的左边或等于栈顶
    
    // 简化：我们直接找以 i 结尾的平衡发货
    // 需要找起始位置 j，使得存在某个位置 k in [j,i-1]，weight[k] > weight[i]
    // 且 j 尽量靠右（使得 dp[j] 尽量大）
    
    // 栈顶就是最近的满足条件的起点-1
    if (!stack.empty()) {
      // 栈顶位置 stack.back()，从 stack.back() 开始或之前到 i 都满足 max > weight[i]
      // 但我们想要最短的平衡发货，即从 stack.back() 到 i
      // 这样 dp[stack.back()] + 1 就是以 i 结尾的最优选择
      int startPos = stack.back();
      dp[i + 1] = max(dp[i + 1], dp[startPos] + 1);
    }
    
    // 将当前位置入栈
    stack.push_back(i);
  }
  
  return dp[n];
}

// 更清晰的贪心思路
// 尽可能早地结束一个平衡发货，这样后面有更多机会
// 从左到右扫描，维护当前区间的最大值
static int solution2(vector<int>& weight) {
  const int n = weight.size();
  if (n < 2) return 0;
  
  int result = 0;
  int i = 0;
  
  while (i < n) {
    // 尝试从位置 i 开始找一个平衡发货
    int maxInRange = weight[i];
    bool found = false;
    
    // 扩展区间直到找到平衡发货
    for (int j = i + 1; j < n; ++j) {
      maxInRange = max(maxInRange, weight[j]);
      // 检查是否平衡：最后一个 < 最大值
      if (weight[j] < maxInRange) {
        // 找到一个平衡发货 [i, j]
        result++;
        i = j + 1;  // 从下一个位置继续
        found = true;
        break;
      }
    }
    
    if (!found) break;  // 找不到更多的平衡发货了
  }
  
  return result;
}

// 优化的贪心：使用单调栈快速找到最短的平衡发货
static int solution3(vector<int>& weight) {
  const int n = weight.size();
  if (n < 2) return 0;
  
  int result = 0;
  int i = 0;
  
  while (i < n) {
    // 找以 i 为起点的最短平衡发货
    // 需要找到最小的 j > i，使得 max(weight[i..j]) > weight[j]
    
    int maxSoFar = weight[i];
    bool found = false;
    
    for (int j = i + 1; j < n && !found; ++j) {
      if (weight[j] > maxSoFar) {
        maxSoFar = weight[j];
      }
      if (weight[j] < maxSoFar) {
        // 找到平衡发货 [i, j]
        result++;
        i = j + 1;
        found = true;
      }
    }
    
    if (!found) break;
  }
  
  return result;
}

// 最终优化版本：使用单调递减栈的贪心
// 核心思想：每次找最短的平衡发货，使得后面有最大机会
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution(vector<int>& weight) {
  const int n = weight.size();
  if (n < 2) return 0;
  
  int result = 0;
  int i = 0;
  
  // 预处理：对于每个位置，找到右边第一个比它大的元素的位置
  // 使用单调递减栈
  vector<int> nextGreater(n, n);  // n 表示不存在
  vector<int> stack;
  
  for (int j = 0; j < n; ++j) {
    while (!stack.empty() && weight[stack.back()] < weight[j]) {
      nextGreater[stack.back()] = j;
      stack.pop_back();
    }
    stack.push_back(j);
  }
  
  // 现在贪心：从位置 i 开始，找最短的平衡发货
  i = 0;
  while (i < n) {
    // 从 i 开始，我们需要找到一个 j，使得 [i,j] 是平衡的
    // 即 max(weight[i..j]) > weight[j]
    
    // 如果 nextGreater[i] 存在，说明 weight[i] 不是最大值
    // 我们需要找到 j >= nextGreater[i]，使得 weight[j] < max(weight[i..j])
    
    int start = i;
    int maxVal = weight[i];
    bool found = false;
    
    for (int j = i + 1; j < n; ++j) {
      maxVal = max(maxVal, weight[j]);
      if (weight[j] < maxVal) {
        // 找到最短的平衡发货
        result++;
        i = j + 1;
        found = true;
        break;
      }
    }
    
    if (!found) break;
  }
  
  return result;
}

MaximumBalancedShipmentsSolution::MaximumBalancedShipmentsSolution() {
  setMetaInfo({.id = 3638,
               .title = "Maximum Balanced Shipments",
               .url = "https://leetcode.com/problems/maximum-balanced-shipments/"});
  registerStrategy("Greedy with Stack", solution);
}

int MaximumBalancedShipmentsSolution::maxBalancedShipments(vector<int>& weight) {
  return getSolution()(weight);
}

}  // namespace problem_3638
}  // namespace leetcode
