
#include "leetcode/problems/convert-a-number-to-hexadecimal.h"

namespace leetcode {
namespace problem_405 {

// 位运算法：每次取低4位转换为十六进制字符
// 时间复杂度: O(1) - 固定处理8个十六进制位（32位整数）
// 空间复杂度: O(1)
static string solution1(int num) {
  if (num == 0) return "0";
  
  // 转换为无符号整数，自动处理负数的补码表示
  unsigned int n = num;
  
  const char hexDigits[] = "0123456789abcdef";
  string result;
  
  while (n > 0) {
    // 取低4位对应的十六进制字符
    result += hexDigits[n & 0xF];
    // 无符号右移4位
    n >>= 4;
  }
  
  // 由于是从低位开始取的，需要反转
  reverse(result.begin(), result.end());
  
  return result;
}

ConvertANumberToHexadecimalSolution::ConvertANumberToHexadecimalSolution() {
  setMetaInfo({.id = 405,
               .title = "Convert a Number to Hexadecimal",
               .url = "https://leetcode.com/problems/convert-a-number-to-hexadecimal/"});
  registerStrategy("Bit Manipulation", solution1);
}

string ConvertANumberToHexadecimalSolution::toHex(int num) {
  return getSolution()(num);
}

}  // namespace problem_405
}  // namespace leetcode
