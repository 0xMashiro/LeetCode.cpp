#include "leetcode/problems/power-of-two.h"

namespace leetcode {
namespace problem_231 {

static bool solution1(int n) {
  // 2的幂一定是正数，且二进制形式只有一个1
  // n > 0 && (n & (n-1)) == 0 是经典判定方法
  return n > 0 && (n & (n - 1)) == 0;
}

PowerOfTwoSolution::PowerOfTwoSolution() {
  setMetaInfo({
      .id = 231,
      .title = "Power of Two",
      .url = "https://leetcode.com/problems/power-of-two"
  });
  registerStrategy("Brute Force", solution1);
}

bool PowerOfTwoSolution::isPowerOfTwo(int n) {
  return getSolution()(n);
}

}  // namespace problem_231
}  // namespace leetcode
