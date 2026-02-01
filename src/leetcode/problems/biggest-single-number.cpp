#include "leetcode/problems/biggest-single-number.h"

namespace leetcode {
namespace problem_619 {

// 哈希表统计频率 + 找最大单数字
// 时间复杂度: O(n), 空间复杂度: O(n)
static std::optional<int> solution1(const vector<int>& nums) {
  // 统计每个数字出现的次数
  unordered_map<int, int> freq;
  for (int num : nums) {
    freq[num]++;
  }

  // 找出出现次数为 1 的数字中的最大值
  std::optional<int> result;
  for (const auto& [num, count] : freq) {
    if (count == 1) {
      if (!result.has_value() || num > result.value()) {
        result = num;
      }
    }
  }

  return result;  // 如果没有单数字，返回 nullopt
}

// 排序 + 扫描：先排序，然后扫描找出只出现一次的数字
// 时间复杂度: O(n log n), 空间复杂度: O(1) 或 O(n)（取决于排序实现）
static std::optional<int> solution2(const vector<int>& nums) {
  if (nums.empty()) {
    return std::nullopt;
  }

  vector<int> sorted = nums;  // 复制一份用于排序
  sort(sorted.begin(), sorted.end());

  std::optional<int> result;
  const int n = sorted.size();

  for (int i = 0; i < n; ) {
    int j = i;
    // 找到相同数字的边界
    while (j < n && sorted[j] == sorted[i]) {
      j++;
    }

    // 如果这个数字只出现一次
    if (j - i == 1) {
      if (!result.has_value() || sorted[i] > result.value()) {
        result = sorted[i];
      }
    }

    i = j;
  }

  return result;
}

BiggestSingleNumberSolution::BiggestSingleNumberSolution() {
  setMetaInfo({.id = 619,
               .title = "Biggest Single Number",
               .url = "https://leetcode.com/problems/biggest-single-number/"});
  registerStrategy("Hash Map", solution1);
  registerStrategy("Sorting", solution2);
}

std::optional<int> BiggestSingleNumberSolution::biggestSingleNumber(const vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_619
}  // namespace leetcode
