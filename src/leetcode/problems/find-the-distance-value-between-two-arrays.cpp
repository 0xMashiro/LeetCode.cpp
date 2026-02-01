#include "leetcode/problems/find-the-distance-value-between-two-arrays.h"

namespace leetcode {
namespace problem_1385 {

// 暴力法：对于 arr1 中每个元素，遍历 arr2 检查是否存在满足 |arr1[i]-arr2[j]| <= d 的元素
// 时间复杂度: O(n*m), 空间复杂度: O(1)
// 其中 n = arr1.length, m = arr2.length
static int solution1(vector<int>& arr1, vector<int>& arr2, int d) {
  int count = 0;
  for (int num1 : arr1) {
    bool valid = true;
    for (int num2 : arr2) {
      if (abs(num1 - num2) <= d) {
        valid = false;
        break;
      }
    }
    if (valid) {
      ++count;
    }
  }
  return count;
}

// 优化法：先对 arr2 排序，然后对每个 arr1[i]，用二分查找检查是否存在满足条件的元素
// 时间复杂度: O(n*log(m) + m*log(m)), 空间复杂度: O(1) 或 O(m)（取决于排序实现）
static int solution2(vector<int>& arr1, vector<int>& arr2, int d) {
  // 对 arr2 排序
  sort(arr2.begin(), arr2.end());
  
  int count = 0;
  for (int num1 : arr1) {
    // 在 arr2 中查找是否存在 num2 使得 |num1 - num2| <= d
    // 即 num2 在 [num1 - d, num1 + d] 范围内
    
    // 使用 lower_bound 找到第一个 >= num1 - d 的元素
    auto it = lower_bound(arr2.begin(), arr2.end(), num1 - d);
    
    // 检查找到的元素是否 <= num1 + d
    if (it == arr2.end() || *it > num1 + d) {
      // 没有找到满足条件的元素
      ++count;
    }
  }
  return count;
}

FindTheDistanceValueBetweenTwoArraysSolution::FindTheDistanceValueBetweenTwoArraysSolution() {
  setMetaInfo({.id = 1385,
               .title = "Find the Distance Value Between Two Arrays",
               .url = "https://leetcode.com/problems/find-the-distance-value-between-two-arrays/"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("Binary Search", solution2);
}

int FindTheDistanceValueBetweenTwoArraysSolution::findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
  return getSolution()(arr1, arr2, d);
}

}  // namespace problem_1385
}  // namespace leetcode
