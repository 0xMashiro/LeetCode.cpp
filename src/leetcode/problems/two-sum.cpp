
#include "leetcode/problems/two-sum.h"

namespace leetcode {
namespace problem_1 {

// 暴力枚举：遍历所有数对
// 时间复杂度: O(n²), 空间复杂度: O(1)
static vector<int> solution1(vector<int>& nums, int target) {
  const int n = nums.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (nums[i] + nums[j] == target) {
        return {i, j};
      }
    }
  }
  return {};
}

// 排序 + 双指针：先排序保留索引，再用双指针查找
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static vector<int> solution2(vector<int>& nums, int target) {
  const int n = nums.size();
  vector<pair<int, int>> valueAndIndex(n);
  auto getValue = [&](int k) { return valueAndIndex[k].first; };
  auto getIndex = [&](int k) { return valueAndIndex[k].second; };
  for (int i = 0; i < n; ++i) {
    valueAndIndex[i] = {nums[i], i};
  }
  sort(valueAndIndex.begin(), valueAndIndex.end());

  int l = 0, r = n - 1;
  while (l < r) {
    int sum = getValue(l) + getValue(r);
    if (sum == target) {
      return {getIndex(l), getIndex(r)};
    }
    (sum < target) ? ++l : --r;
  }
  return {};
}

// 哈希表（两遍）：先建立映射，再查找补数
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution3(vector<int>& nums, int target) {
  const int n = nums.size();
  unordered_map<int, int> indices;
  for (int i = 0; i < n; ++i) {
    indices[nums[i]] = i;
  }

  for (int i = 0; i < n; ++i) {
    int x = target - nums[i];
    if (indices.find(x) != indices.end() && indices[x] != i) {
      return {i, indices[x]};
    }
  }
  return {};
}

// 哈希表（一遍）：边遍历边查找
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution4(vector<int>& nums, int target) {
  const int n = nums.size();
  unordered_map<int, int> indices;
  for (int i = 0; i < n; ++i) {
    int x = target - nums[i];
    if (indices.find(x) != indices.end()) {
      return {i, indices[x]};
    }
    indices[nums[i]] = i;
  }
  return {};
}

TwoSumSolution::TwoSumSolution() {
  setMetaInfo({.id = 1,
               .title = "Two Sum",
               .url = "https://leetcode.com/problems/two-sum"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("Sorting + Two Pointer", solution2);
  registerStrategy("Hash Table Two-Pass", solution3);
  registerStrategy("Hash Table One-Pass", solution4);
}

vector<int> TwoSumSolution::twoSum(vector<int>& nums, int target) {
  return getSolution()(nums, target);
}

}  // namespace problem_1
}  // namespace leetcode
