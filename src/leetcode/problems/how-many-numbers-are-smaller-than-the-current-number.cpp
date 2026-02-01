
#include "leetcode/problems/how-many-numbers-are-smaller-than-the-current-number.h"

namespace leetcode {
namespace problem_1365 {

// 暴力枚举：对每个元素，遍历整个数组统计比它小的个数
// 时间复杂度: O(n²), 空间复杂度: O(1)（不包括结果数组）
static vector<int> solution1(vector<int>& nums) {
  const int n = nums.size();
  vector<int> result(n);
  for (int i = 0; i < n; ++i) {
    int count = 0;
    for (int j = 0; j < n; ++j) {
      if (i != j && nums[j] < nums[i]) {
        ++count;
      }
    }
    result[i] = count;
  }
  return result;
}

// 排序 + 哈希表：先排序，记录每个值第一次出现的位置
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static vector<int> solution2(vector<int>& nums) {
  const int n = nums.size();
  // 复制并排序
  vector<int> sorted(nums);
  sort(sorted.begin(), sorted.end());
  
  // 记录每个值第一次出现的位置（即比它小的数字个数）
  unordered_map<int, int> firstPos;
  for (int i = 0; i < n; ++i) {
    if (firstPos.find(sorted[i]) == firstPos.end()) {
      firstPos[sorted[i]] = i;
    }
  }
  
  // 构造结果
  vector<int> result(n);
  for (int i = 0; i < n; ++i) {
    result[i] = firstPos[nums[i]];
  }
  return result;
}

// 计数排序：利用值域 0-100 的特性，使用前缀和
// 时间复杂度: O(n + k), 空间复杂度: O(k)，k=101
static vector<int> solution3(vector<int>& nums) {
  const int n = nums.size();
  const int MAX_VAL = 101;
  
  // 统计每个值出现的次数
  vector<int> count(MAX_VAL, 0);
  for (int num : nums) {
    ++count[num];
  }
  
  // 前缀和：count[i] 表示小于 i 的数字个数
  for (int i = 1; i < MAX_VAL; ++i) {
    count[i] += count[i - 1];
  }
  
  // 构造结果：比 nums[i] 小的数字个数为 count[nums[i] - 1]（如果 nums[i] > 0）
  vector<int> result(n);
  for (int i = 0; i < n; ++i) {
    result[i] = (nums[i] > 0) ? count[nums[i] - 1] : 0;
  }
  return result;
}

HowManyNumbersAreSmallerThanTheCurrentNumberSolution::HowManyNumbersAreSmallerThanTheCurrentNumberSolution() {
  setMetaInfo({.id = 1365,
               .title = "How Many Numbers Are Smaller Than the Current Number",
               .url = "https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("Sorting + Hash Map", solution2);
  registerStrategy("Counting Sort", solution3);
}

vector<int> HowManyNumbersAreSmallerThanTheCurrentNumberSolution::smallerNumbersThanCurrent(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_1365
}  // namespace leetcode
