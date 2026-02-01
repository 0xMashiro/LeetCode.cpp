#include "leetcode/problems/sum-of-distances.h"

namespace leetcode {
namespace problem_2615 {

/**
 * 思路：哈希表 + 前缀和优化
 * 1. 使用哈希表按值分组，记录每个值出现的所有索引
 * 2. 对每个值的索引列表，使用前缀和快速计算每个位置到其他位置的距离和
 * 
 * 对于索引列表 [i0, i1, ..., ik]，位置 ij 的距离和为：
 * - 左边部分：ij * j - (i0 + i1 + ... + i(j-1))
 * - 右边部分：(i(j+1) + ... + ik) - ij * (k-j)
 * 使用前缀和可在 O(1) 内计算每个位置的结果
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
 */
static vector<long long> solution(vector<int>& nums) {
  const int n = nums.size();
  
  // 按值分组，记录每个值出现的所有索引
  unordered_map<int, vector<int>> groups;
  for (int i = 0; i < n; ++i) {
    groups[nums[i]].push_back(i);
  }
  
  vector<long long> result(n, 0);
  
  // 对每个值的索引列表计算距离和
  for (auto& [val, indices] : groups) {
    const int m = indices.size();
    if (m == 1) {
      // 只有一个元素，距离为 0
      result[indices[0]] = 0;
      continue;
    }
    
    // 计算前缀和
    vector<long long> prefix(m + 1, 0);
    for (int i = 0; i < m; ++i) {
      prefix[i + 1] = prefix[i] + indices[i];
    }
    
    // 计算每个位置的距离和
    for (int i = 0; i < m; ++i) {
      long long idx = indices[i];
      // 左边有 i 个元素，下标范围 [0, i-1]
      long long left_sum = idx * i - prefix[i];
      // 右边有 m - i - 1 个元素，下标范围 [i+1, m-1]
      long long right_sum = (prefix[m] - prefix[i + 1]) - idx * (m - i - 1);
      result[idx] = left_sum + right_sum;
    }
  }
  
  return result;
}

SumOfDistancesSolution::SumOfDistancesSolution() {
  setMetaInfo({.id = 2615,
               .title = "Sum of Distances",
               .url = "https://leetcode.com/problems/sum-of-distances/"});
  registerStrategy("Hash Table + Prefix Sum", solution);
}

vector<long long> SumOfDistancesSolution::distance(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2615
}  // namespace leetcode
