#include "leetcode/problems/string-compression.h"

namespace leetcode {
namespace problem_443 {

// 双指针原地压缩
// write: 写入位置，read: 读取位置
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(vector<char>& chars) {
  const int n = chars.size();
  if (n <= 1) return n;

  int write = 0;  // 写入位置
  int read = 0;   // 读取位置

  while (read < n) {
    char current = chars[read];
    int count = 0;

    // 统计当前字符连续出现的次数
    while (read < n && chars[read] == current) {
      ++read;
      ++count;
    }

    // 写入字符
    chars[write++] = current;

    // 如果次数大于1，写入次数（注意：次数可能有多位）
    if (count > 1) {
      string countStr = to_string(count);
      for (char c : countStr) {
        chars[write++] = c;
      }
    }
  }

  return write;
}

StringCompressionSolution::StringCompressionSolution() {
  setMetaInfo({.id = 443,
               .title = "String Compression",
               .url = "https://leetcode.com/problems/string-compression/"});
  registerStrategy("Two Pointers", solution1);
}

int StringCompressionSolution::compress(vector<char>& chars) {
  return getSolution()(chars);
}

}  // namespace problem_443
}  // namespace leetcode
