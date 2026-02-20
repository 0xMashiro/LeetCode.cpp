#include "leetcode/problems/special-binary-string.h"

namespace leetcode {
namespace problem_761 {

// 递归处理特殊二进制字符串
// 思路：
// 1. 特殊字符串可以分解为多个连续的基本特殊子串
// 2. 对每个基本子串，递归处理其内部
// 3. 将所有处理后的子串按字典序降序排列
// 4. 拼接得到字典序最大的结果
// 时间复杂度: O(n^2 log n) 或 O(n^2)，空间复杂度: O(n)
static string makeLargestSpecialImpl(string s) {
  // 基本情况
  if (s.length() <= 2) {
    return s;
  }
  
  vector<string> components;
  int count = 0;
  int start = 0;
  
  // 分解为顶层基本特殊子串
  // 使用计数法：遇到1加1，遇到0减1，当计数回到0时得到一个基本子串
  for (int i = 0; i < s.length(); ++i) {
    count += (s[i] == '1') ? 1 : -1;
    if (count == 0) {
      // 找到一个基本子串 s[start..i]
      // 递归处理内部（去掉首尾的1和0）
      string inner = s.substr(start + 1, i - start - 1);
      string processed = makeLargestSpecialImpl(inner);
      // 加上首尾的1和0
      components.push_back("1" + processed + "0");
      start = i + 1;
    }
  }
  
  // 按字典序降序排列，得到最大的字符串
  sort(components.begin(), components.end(), greater<string>());
  
  // 拼接结果
  string result;
  for (const auto& comp : components) {
    result += comp;
  }
  
  return result;
}

static string solution1(string s) {
  return makeLargestSpecialImpl(s);
}

SpecialBinaryStringSolution::SpecialBinaryStringSolution() {
  setMetaInfo({.id = 761,
               .title = "Special Binary String",
               .url = "https://leetcode.com/problems/special-binary-string/"});
  registerStrategy("Recursive", solution1);
}

string SpecialBinaryStringSolution::makeLargestSpecial(string s) {
  return getSolution()(s);
}

}  // namespace problem_761
}  // namespace leetcode
