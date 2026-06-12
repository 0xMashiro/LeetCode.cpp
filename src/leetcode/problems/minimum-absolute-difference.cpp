#include "leetcode/problems/minimum-absolute-difference.h"

namespace leetcode {
namespace problem_1200 {

// 暴力法：枚举所有数对，找到最小绝对差，然后收集所有差值等于最小值的数对
// 时间复杂度: O(n²), 空间复杂度: O(1) (不计结果存储)
static vector<vector<int>> solution1(vector<int>& arr) {
  const int n = arr.size();
  int minDiff = INT_MAX;
  
  // 第一遍：找到最小绝对差
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int diff = abs(arr[i] - arr[j]);
      if (diff < minDiff) {
        minDiff = diff;
      }
    }
  }
  
  // 第二遍：收集所有差值等于最小绝对差的数对
  vector<vector<int>> result;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (abs(arr[i] - arr[j]) == minDiff) {
        int a = arr[i];
        int b = arr[j];
        if (a > b) swap(a, b);  // 确保 a < b
        result.push_back({a, b});
      }
    }
  }
  
  // 按升序排序结果（先按第一个元素，再按第二个元素）
  sort(result.begin(), result.end());
  return result;
}

// 排序法：先排序，然后相邻元素的差值即为可能的最小绝对差
// 时间复杂度: O(n log n), 空间复杂度: O(1) (排序可能需要额外空间)
static vector<vector<int>> solution2(vector<int>& arr) {
  // 对数组排序
  sort(arr.begin(), arr.end());
  
  const int n = arr.size();
  int minDiff = INT_MAX;
  vector<vector<int>> result;
  
  // 一次遍历：计算相邻差值，同时维护最小差值和结果
  for (int i = 0; i < n - 1; ++i) {
    int diff = arr[i + 1] - arr[i];  // 排序后 arr[i+1] > arr[i]，所以 diff > 0
    if (diff < minDiff) {
      // 发现更小的差值，清空之前的结果
      minDiff = diff;
      result.clear();
      result.push_back({arr[i], arr[i + 1]});
    } else if (diff == minDiff) {
      // 差值等于当前最小差值，添加到结果
      result.push_back({arr[i], arr[i + 1]});
    }
  }
  
  // 由于数组已排序，结果自然满足 a < b 且按 a 升序排列
  return result;
}

MinimumAbsoluteDifferenceSolution::MinimumAbsoluteDifferenceSolution() {
  setMetaInfo({.id = 1200,
               .title = "Minimum Absolute Difference",
               .url = "https://leetcode.com/problems/minimum-absolute-difference"});
  registerStrategy({.name = "Brute Force"}, solution1);
  registerStrategy({.name = "Sorting"}, solution2);
}

vector<vector<int>> MinimumAbsoluteDifferenceSolution::minimumAbsDifference(vector<int>& arr) {
  return getSolution()(arr);
}

}  // namespace problem_1200
}  // namespace leetcode