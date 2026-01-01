#include "leetcode/problems/plus-one.h"

namespace leetcode {
namespace problem_66 {

// 策略1：模拟加法，从后向前遍历，处理进位
// 时间复杂度: O(n)，空间复杂度: O(1)（最坏情况 O(n) 用于结果数组）
static vector<int> solution1(vector<int>& digits) {
  int n = digits.size();
  // 从最后一位开始加一
  for (int i = n - 1; i >= 0; --i) {
    if (digits[i] < 9) {
      // 如果当前位小于9，直接加一后返回
      ++digits[i];
      return digits;
    }
    // 当前位为9，加一后变为0，进位
    digits[i] = 0;
  }
  // 如果所有位都是9，需要在数组最前面插入1
  digits.insert(digits.begin(), 1);
  return digits;
}

// 策略2：更直观的写法，使用进位标志
// 时间复杂度: O(n)，空间复杂度: O(1)（最坏情况 O(n)）
static vector<int> solution2(vector<int>& digits) {
  int carry = 1;  // 初始进位为1，表示加一
  int n = digits.size();
  for (int i = n - 1; i >= 0 && carry > 0; --i) {
    int sum = digits[i] + carry;
    digits[i] = sum % 10;
    carry = sum / 10;
  }
  // 如果还有进位，说明需要在最前面插入1
  if (carry > 0) {
    digits.insert(digits.begin(), carry);
  }
  return digits;
}

PlusOneSolution::PlusOneSolution() {
  setMetaInfo({.id = 66,
               .title = "Plus One",
               .url = "https://leetcode.com/problems/plus-one"});
  registerStrategy("Simulation", solution1);
  registerStrategy("Carry Flag", solution2);
}

vector<int> PlusOneSolution::plusOne(vector<int>& digits) {
  return getSolution()(digits);
}

}  // namespace problem_66
}  // namespace leetcode