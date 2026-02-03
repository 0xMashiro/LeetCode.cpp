#include "leetcode/problems/concatenated-divisibility.h"

namespace leetcode {
namespace problem_3533 {

static vector<int> solution(vector<int>& nums, int k) {
  const int n = nums.size();
  if (n == 0) return {};
  
  // 预处理：计算每个数字的位数长度和模k余数
  vector<int> len(n);
  vector<int> rem(n);
  for (int i = 0; i < n; ++i) {
    len[i] = to_string(nums[i]).length();
    rem[i] = nums[i] % k;
  }
  
  // 预处理：pow10[i] = (10^i) % k，用于快速计算新的余数
  vector<int> pow10(7); // 最多6位数字(10^5)
  pow10[0] = 1 % k;
  for (int i = 1; i < 7; ++i) {
    pow10[i] = (pow10[i-1] * 10) % k;
  }
  
  const int fullMask = (1 << n) - 1;
  
  // dp[mask][rem] 存储字典序最小的序列，用 vector<int> 或空表示不可达
  // 由于n<=13, k<=100，总状态数约为 2^13 * 100 = 819200，可以接受
  // 为了效率，使用 vector<vector<vector<int>>> 或直接用记忆化搜索
  
  // 使用迭代DP：dp[mask] = 每个余数对应的最优序列
  // 但我们也可以反过来：从小到大枚举mask，逐步构建
  
  // 更优方案：由于要字典序最小，可以使用BFS/队列配合状态记录
  // 或者使用 DP 数组记录"从某个状态出发能否到达余数0"
  
  // 这里采用：dp[mask][rem] = 是否可达，同时记录前驱用于重构路径
  // 但为了直接得到字典序最小，我们按mask从小到大，每个mask内按数字从小到大枚举
  
  // 使用 vector of vector of optional path
  vector<vector<vector<int>>> dp(1 << n, vector<vector<int>>(k));
  // dp[mask][rem] 非空表示可达，存储对应的序列
  
  dp[0][0] = {}; // 空集合，余数为0，序列为空
  
  // 按mask从小到大处理
  for (int mask = 0; mask <= fullMask; ++mask) {
    for (int curRem = 0; curRem < k; ++curRem) {
      if (dp[mask][curRem].empty() && !(mask == 0 && curRem == 0)) continue;
      
      // 尝试添加每一个未使用的数字
      for (int i = 0; i < n; ++i) {
        if (mask & (1 << i)) continue; // 已使用
        
        // 计算新的余数
        // newNum = curNum * 10^len[i] + nums[i]
        // newRem = (curRem * 10^len[i] + rem[i]) % k
        int newRem = (curRem * pow10[len[i]] + rem[i]) % k;
        int newMask = mask | (1 << i);
        
        vector<int> newPath = dp[mask][curRem];
        newPath.push_back(nums[i]);
        
        // 如果这个状态还没被访问过，或者新路径字典序更小
        if (dp[newMask][newRem].empty() || newPath < dp[newMask][newRem]) {
          dp[newMask][newRem] = newPath;
        }
      }
    }
  }
  
  return dp[fullMask][0];
}

ConcatenatedDivisibilitySolution::ConcatenatedDivisibilitySolution() {
  setMetaInfo({.id = 3533,
               .title = "Concatenated Divisibility",
               .url = "https://leetcode.com/problems/concatenated-divisibility/"});
  registerStrategy("State Compression DP", solution);
}

vector<int> ConcatenatedDivisibilitySolution::concatenatedDivisibility(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3533
}  // namespace leetcode
