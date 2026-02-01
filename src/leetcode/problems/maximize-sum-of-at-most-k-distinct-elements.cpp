#include "leetcode/problems/maximize-sum-of-at-most-k-distinct-elements.h"

namespace leetcode {
namespace problem_3684 {

// 贪心策略：选择最大的k个不同元素
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static vector<int> solution1(vector<int>& nums, int k) {
  // 使用set去重并自动排序（升序）
  set<int> unique_nums(nums.begin(), nums.end());
  
  // 转换为vector并按降序排列
  vector<int> distinct(unique_nums.begin(), unique_nums.end());
  sort(distinct.begin(), distinct.end(), greater<int>());
  
  // 取前 min(k, distinct.size()) 个元素
  int take = min(k, static_cast<int>(distinct.size()));
  vector<int> result(distinct.begin(), distinct.begin() + take);
  
  return result;
}

// 优化版本：使用unordered_set去重，然后排序
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static vector<int> solution2(vector<int>& nums, int k) {
  // 使用unordered_set去重，O(n)
  unordered_set<int> unique_set(nums.begin(), nums.end());
  
  // 转换为vector
  vector<int> distinct(unique_set.begin(), unique_set.end());
  
  // 按降序排序
  sort(distinct.begin(), distinct.end(), greater<int>());
  
  // 取前 min(k, distinct.size()) 个元素
  int take = min(k, static_cast<int>(distinct.size()));
  vector<int> result(distinct.begin(), distinct.begin() + take);
  
  return result;
}

MaximizeSumOfAtMostKDistinctElementsSolution::MaximizeSumOfAtMostKDistinctElementsSolution() {
  setMetaInfo({.id = 3684,
               .title = "Maximize Sum of At Most K Distinct Elements",
               .url = "https://leetcode.com/problems/maximize-sum-of-at-most-k-distinct-elements/"});
  registerStrategy("Greedy with Set", solution1);
  registerStrategy("Greedy with UnorderedSet", solution2);
}

vector<int> MaximizeSumOfAtMostKDistinctElementsSolution::maxKDistinct(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3684
}  // namespace leetcode
