#include "leetcode/problems/minimum-pair-removal-to-sort-array-i.h"

namespace leetcode {
namespace problem_3507 {

// 辅助函数：检查数组是否非递减
static bool isNonDecreasing(const vector<int>& arr) {
  for (size_t i = 1; i < arr.size(); ++i) {
    if (arr[i] < arr[i - 1]) {
      return false;
    }
  }
  return true;
}

// 策略1：模拟操作过程
static int solution1(vector<int>& nums) {
  vector<int> cur = nums;  // 拷贝一份，避免修改原数组
  int operations = 0;
  
  // 当数组长度大于1且尚未有序时继续操作
  while (cur.size() > 1 && !isNonDecreasing(cur)) {
    // 找到最小和的相邻对
    int minSum = INT_MAX;
    size_t idx = 0;
    for (size_t i = 0; i < cur.size() - 1; ++i) {
      int sum = cur[i] + cur[i + 1];
      if (sum < minSum) {
        minSum = sum;
        idx = i;
      }
    }
    
    // 合并该对
    int newVal = cur[idx] + cur[idx + 1];
    cur.erase(cur.begin() + idx, cur.begin() + idx + 2);
    cur.insert(cur.begin() + idx, newVal);
    ++operations;
  }
  
  return operations;
}

MinimumPairRemovalToSortArrayISolution::MinimumPairRemovalToSortArrayISolution() {
  setMetaInfo({.id = 3507,
               .title = "Minimum Pair Removal to Sort Array I",
               .url = "https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/"});
  registerStrategy({.name = "Simulation"}, solution1);
}

int MinimumPairRemovalToSortArrayISolution::minimumPairRemoval(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3507
}  // namespace leetcode