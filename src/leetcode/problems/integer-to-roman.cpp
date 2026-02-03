#include "leetcode/problems/integer-to-roman.h"

namespace leetcode {
namespace problem_12 {

// 贪心算法：从大到小依次匹配罗马数字符号
// 时间复杂度: O(1)，因为数值范围固定且有限
// 空间复杂度: O(1)
static string solution1(int num) {
  // 定义所有罗马数字符号及其对应数值，从大到小排列
  // 包括特殊情况：4, 9, 40, 90, 400, 900
  static const pair<int, string> values[] = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
    {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
  };
  
  string result;
  
  // 从大到小依次匹配
  for (const auto& [value, symbol] : values) {
    // 当前数值能减多少次
    while (num >= value) {
      result += symbol;
      num -= value;
    }
    // 如果num已经为0，提前退出
    if (num == 0) break;
  }
  
  return result;
}

IntegerToRomanSolution::IntegerToRomanSolution() {
  setMetaInfo({.id = 12,
               .title = "Integer to Roman",
               .url = "https://leetcode.com/problems/integer-to-roman/"});
  registerStrategy("Greedy", solution1);
}

string IntegerToRomanSolution::intToRoman(int num) {
  return getSolution()(num);
}

}  // namespace problem_12
}  // namespace leetcode