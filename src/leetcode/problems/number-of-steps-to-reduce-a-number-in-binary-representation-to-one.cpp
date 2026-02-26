#include "leetcode/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one.h"

namespace leetcode {
namespace problem_1404 {

// 模拟二进制操作
// 从字符串末尾开始处理，维护进位
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(string s) {
  int steps = 0;
  int carry = 0;
  int n = s.size();
  
  // 从后往前处理，除了最高位（s[0]）
  for (int i = n - 1; i > 0; --i) {
    int bit = (s[i] - '0') + carry;
    if (bit % 2 == 0) {
      // 偶数：除以 2，步骤 +1
      steps++;
    } else {
      // 奇数：加 1，步骤 +2（加1需要1步，除2需要1步）
      // 加1会产生进位
      steps += 2;
      carry = 1;
    }
  }
  
  // 处理最高位
  int lastBit = (s[0] - '0') + carry;
  if (lastBit == 2) {
    // 最高位 1 + carry 1 = 2 (二进制 10)
    // 还需要一步除以 2 变成 1
    steps++;
  }
  // lastBit == 1 时，已经是 1，不需要额外步骤
  
  return steps;
}

NumberOfStepsToReduceANumberInBinaryRepresentationToOneSolution::NumberOfStepsToReduceANumberInBinaryRepresentationToOneSolution() {
  setMetaInfo({.id = 1404,
               .title = "Number of Steps to Reduce a Number in Binary Representation to One",
               .url = "https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/"});
  registerStrategy("Simulation", solution1);
}

int NumberOfStepsToReduceANumberInBinaryRepresentationToOneSolution::numSteps(string s) {
  return getSolution()(s);
}

}  // namespace problem_1404
}  // namespace leetcode
