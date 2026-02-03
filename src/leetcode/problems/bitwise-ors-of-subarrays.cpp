#include "leetcode/problems/bitwise-ors-of-subarrays.h"

namespace leetcode {
namespace problem_898 {

// 动态规划 + 集合优化
// 关键观察：按位或是单调递增的，以位置i结尾的不同或值最多32个
// dp[i]表示以i结尾的所有子数组的按位或结果集合
// dp[i] = {arr[i]} ∪ {x | arr[i] for x in dp[i-1]}
// 时间复杂度: O(n * 32) = O(n), 空间复杂度: O(32) = O(1)
static int solution1(vector<int>& arr) {
  unordered_set<int> all_results;  // 存储所有不同的按位或结果
  unordered_set<int> prev;         // 以i-1结尾的所有按位或结果
  
  for (int num : arr) {
    unordered_set<int> curr;
    curr.insert(num);
    // 以当前元素结尾的子数组的按位或结果
    for (int x : prev) {
      curr.insert(x | num);
    }
    // 将当前结果加入全局集合
    for (int x : curr) {
      all_results.insert(x);
    }
    prev = std::move(curr);
  }
  
  return static_cast<int>(all_results.size());
}

// 优化版本：使用vector代替unordered_set，减少常数因子
// 利用按位或的单调性，prev中的元素是严格递增的
static int solution2(vector<int>& arr) {
  unordered_set<int> all_results;
  vector<int> prev;
  
  for (int num : arr) {
    vector<int> curr;
    curr.push_back(num);
    // 去重：只保留能产生新结果的值
    for (int x : prev) {
      if ((x | num) != curr.back()) {
        curr.push_back(x | num);
      }
    }
    // 加入全局结果
    for (int x : curr) {
      all_results.insert(x);
    }
    prev = std::move(curr);
  }
  
  return static_cast<int>(all_results.size());
}

BitwiseOrsOfSubarraysSolution::BitwiseOrsOfSubarraysSolution() {
  setMetaInfo({.id = 898,
               .title = "Bitwise ORs of Subarrays",
               .url = "https://leetcode.com/problems/bitwise-ors-of-subarrays/"});
  registerStrategy("DP with HashSet", solution1);
  registerStrategy("DP with Vector Optimization", solution2);
}

int BitwiseOrsOfSubarraysSolution::subarrayBitwiseORs(vector<int>& arr) {
  return getSolution()(arr);
}

}  // namespace problem_898
}  // namespace leetcode
