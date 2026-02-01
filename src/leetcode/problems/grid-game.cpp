#include "leetcode/problems/grid-game.h"

namespace leetcode {
namespace problem_2017 {

/**
 * @brief 计算第二个机器人在第一个机器人最优策略下能收集的分数
 * 
 * 关键观察：
 * 1. 第一个机器人从(0,0)到(1,n-1)，必然在某列i从第一行跳到第二行
 * 2. 路径清零后，第二个机器人的最优选择是：
 *    - 要么在i之前（含）向下，收集第二行[0, i-1]的分数
 *    - 要么在i之后向下，收集第一行[i+1, n-1]的分数
 * 3. 第二个机器人会取两者中的较大值
 * 4. 第一个机器人要最小化这个较大值
 */
static long long solution1(vector<vector<int>>& grid) {
  const int n = grid[0].size();
  
  // 计算第一行的总和（用于计算后缀和）
  long long firstRowSum = 0;
  for (int i = 0; i < n; ++i) {
    firstRowSum += grid[0][i];
  }
  
  long long result = LLONG_MAX;
  long long secondRowPrefix = 0;  // 第二行前i项的和
  long long firstRowSuffix = firstRowSum;  // 第一行从i开始到末尾的和（稍后调整）
  
  for (int i = 0; i < n; ++i) {
    // 第一个机器人在第i列向下
    // 它收集了grid[0][i]和grid[1][i]，但这些位置会被清零
    // 对于第二个机器人：
    // - 如果在i之前向下，能收集secondRowPrefix（第二行[0, i-1]的和）
    // - 如果在i之后向下，能收集firstRowSuffix - grid[0][i]（第一行[i+1, n-1]的和）
    
    firstRowSuffix -= grid[0][i];  // 现在firstRowSuffix是grid[0][i+1..n-1]的和
    
    // 第二个机器人能收集的最大分数
    long long secondRobotMax = std::max(secondRowPrefix, firstRowSuffix);
    
    // 第一个机器人要最小化这个值
    result = std::min(result, secondRobotMax);
    
    // 为下一次迭代更新secondRowPrefix
    secondRowPrefix += grid[1][i];
  }
  
  return result;
}

/**
 * @brief 另一种实现方式，更直观
 */
static long long solution2(vector<vector<int>>& grid) {
  const int n = grid[0].size();
  
  // prefixTop[i] = grid[0][0] + ... + grid[0][i-1]（前i个元素的和）
  // suffixTop[i] = grid[0][i] + ... + grid[0][n-1]
  vector<long long> suffixTop(n + 1, 0);
  
  for (int i = n - 1; i >= 0; --i) {
    suffixTop[i] = suffixTop[i + 1] + grid[0][i];
  }
  
  long long result = LLONG_MAX;
  long long prefixBottom = 0;
  
  for (int i = 0; i < n; ++i) {
    // 第一个机器人在第i列向下
    // 第二个机器人可选：
    // 1. 走下面一行到第i-1列，然后向下（但已经向下过了，所以不能这样）
    // 实际上第二个机器人只能：
    // - 在i之前某位置向下：收集第二行[0, i-1]（即prefixBottom - grid[1][i]，但我们还没加）
    // - 在第i列或之后向下：收集第一行[i+1, n-1]
    
    // suffixTop[i+1] 是 grid[0][i+1..n-1] 的和
    long long topPath = suffixTop[i + 1];
    long long bottomPath = prefixBottom;
    
    long long secondRobotMax = std::max(topPath, bottomPath);
    result = std::min(result, secondRobotMax);
    
    prefixBottom += grid[1][i];
  }
  
  return result;
}

GridGameSolution::GridGameSolution() {
  setMetaInfo({
    .id = 2017,
    .title = "Grid Game",
    .url = "https://leetcode.com/problems/grid-game/"
  });
  registerStrategy("Prefix Sum Optimized", solution1);
  registerStrategy("Prefix Suffix Array", solution2);
}

long long GridGameSolution::gridGame(vector<vector<int>>& grid) {
  return getSolution()(grid);
}

}  // namespace problem_2017
}  // namespace leetcode
