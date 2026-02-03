#include "leetcode/problems/binary-watch.h"

namespace leetcode {
namespace problem_401 {

// 计算一个数的二进制中 1 的个数
static int countBits(int n) {
  int count = 0;
  while (n > 0) {
    count += n & 1;
    n >>= 1;
  }
  return count;
}

// 枚举所有可能的小时和分钟组合
// 时间复杂度: O(12 * 60) = O(720), 空间复杂度: O(1)
static vector<string> solution1(int turnedOn) {
  vector<string> result;
  
  // 枚举所有可能的小时 (0-11)
  for (int h = 0; h < 12; ++h) {
    // 枚举所有可能的分钟 (0-59)
    for (int m = 0; m < 60; ++m) {
      // 如果小时和分钟的二进制 1 的个数之和等于 turnedOn
      if (countBits(h) + countBits(m) == turnedOn) {
        // 格式化时间字符串
        string time = to_string(h) + ":" + (m < 10 ? "0" : "") + to_string(m);
        result.push_back(time);
      }
    }
  }
  
  return result;
}

BinaryWatchSolution::BinaryWatchSolution() {
  setMetaInfo({.id = 401,
               .title = "Binary Watch",
               .url = "https://leetcode.com/problems/binary-watch/"});
  registerStrategy("Enumerate", solution1);
}

vector<string> BinaryWatchSolution::readBinaryWatch(int turnedOn) {
  return getSolution()(turnedOn);
}

}  // namespace problem_401
}  // namespace leetcode
