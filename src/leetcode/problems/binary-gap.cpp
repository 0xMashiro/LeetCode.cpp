#include "leetcode/problems/binary-gap.h"

namespace leetcode {
namespace problem_868 {

// 位运算扫描：从低位到高位遍历，记录上一个1的位置
// 时间复杂度: O(log n), 空间复杂度: O(1)
static int solution(int n) {
  int lastPos = -1;  // 上一个1的位置
  int maxDist = 0;   // 最大距离
  int pos = 0;       // 当前位位置

  while (n > 0) {
    // 检查当前最低位是否为1
    if (n & 1) {
      if (lastPos != -1) {
        // 计算与上一个1的距离
        maxDist = max(maxDist, pos - lastPos);
      }
      lastPos = pos;  // 更新上一个1的位置
    }
    n >>= 1;  // 右移一位
    ++pos;
  }

  return maxDist;
}

BinaryGapSolution::BinaryGapSolution() {
  setMetaInfo({.id = 868,
               .title = "Binary Gap",
               .url = "https://leetcode.com/problems/binary-gap/"});
  registerStrategy("Bit Scan", solution);
}

int BinaryGapSolution::binaryGap(int n) {
  return getSolution()(n);
}

}  // namespace problem_868
}  // namespace leetcode
