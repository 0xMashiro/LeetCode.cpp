#include "leetcode/problems/count-the-digits-that-divide-a-number.h"

namespace leetcode {
namespace problem_2520 {

static int solution(int num) {
  int original = num;
  int count = 0;
  
  while (num > 0) {
    int digit = num % 10;
    // 跳过数字 0，避免除以零错误
    if (digit != 0 && original % digit == 0) {
      ++count;
    }
    num /= 10;
  }
  
  return count;
}

CountTheDigitsThatDivideANumberSolution::CountTheDigitsThatDivideANumberSolution() {
  setMetaInfo({.id = 2520,
               .title = "Count the Digits That Divide a Number",
               .url = "https://leetcode.com/problems/count-the-digits-that-divide-a-number/"});
  registerStrategy("Direct Count", solution);
}

int CountTheDigitsThatDivideANumberSolution::countDigits(int num) {
  return getSolution()(num);
}

}  // namespace problem_2520
}  // namespace leetcode
