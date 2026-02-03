#include "leetcode/problems/count-good-triplets.h"

namespace leetcode {
namespace problem_1534 {

// 暴力枚举：三重循环遍历所有满足 i < j < k 的三元组
// 时间复杂度: O(n³), 空间复杂度: O(1)
static int solution1(vector<int>& arr, int a, int b, int c) {
  const int n = arr.size();
  int count = 0;
  
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      // 提前剪枝：如果 |arr[i] - arr[j]| > a，跳过k的循环
      if (abs(arr[i] - arr[j]) > a) continue;
      
      for (int k = j + 1; k < n; ++k) {
        if (abs(arr[j] - arr[k]) <= b && abs(arr[i] - arr[k]) <= c) {
          ++count;
        }
      }
    }
  }
  
  return count;
}

CountGoodTripletsSolution::CountGoodTripletsSolution() {
  setMetaInfo({.id = 1534,
               .title = "Count Good Triplets",
               .url = "https://leetcode.com/problems/count-good-triplets/"});
  registerStrategy("Brute Force", solution1);
}

int CountGoodTripletsSolution::countGoodTriplets(vector<int>& arr, int a, int b, int c) {
  return getSolution()(arr, a, b, c);
}

}  // namespace problem_1534
}  // namespace leetcode
