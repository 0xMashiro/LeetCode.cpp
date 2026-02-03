
#include "leetcode/problems/count-number-of-distinct-integers-after-reverse-operations.h"

namespace leetcode {
namespace problem_2442 {

// 反转整数的辅助函数
int CountNumberOfDistinctIntegersAfterReverseOperationsSolution::reverse(int num) {
  int result = 0;
  while (num > 0) {
    result = result * 10 + num % 10;
    num /= 10;
  }
  return result;
}

// 解法：使用哈希集合存储所有不同的整数
// 时间复杂度: O(n * d)，其中 n 是数组长度，d 是数字的位数（最大为7，因为 nums[i] <= 10^6）
// 空间复杂度: O(n)，用于存储集合
static int solution(vector<int>& nums) {
  unordered_set<int> distinct;
  
  for (int num : nums) {
    // 添加原数
    distinct.insert(num);
    // 添加反转后的数
    int reversed = 0;
    int temp = num;
    while (temp > 0) {
      reversed = reversed * 10 + temp % 10;
      temp /= 10;
    }
    distinct.insert(reversed);
  }
  
  return static_cast<int>(distinct.size());
}

CountNumberOfDistinctIntegersAfterReverseOperationsSolution::CountNumberOfDistinctIntegersAfterReverseOperationsSolution() {
  setMetaInfo({.id = 2442,
               .title = "Count Number of Distinct Integers After Reverse Operations",
               .url = "https://leetcode.com/problems/count-number-of-distinct-integers-after-reverse-operations/"});
  registerStrategy("Hash Set", solution);
}

int CountNumberOfDistinctIntegersAfterReverseOperationsSolution::countDistinctIntegers(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2442
}  // namespace leetcode
