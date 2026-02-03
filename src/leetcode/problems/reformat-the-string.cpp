#include "leetcode/problems/reformat-the-string.h"

namespace leetcode {
namespace problem_1417 {

// 分离字母和数字，然后交替合并
// 时间复杂度: O(n), 空间复杂度: O(n)
static std::string solution1(std::string s) {
  std::vector<char> letters;
  std::vector<char> digits;
  
  // 分离字母和数字
  for (char c : s) {
    if (isalpha(c)) {
      letters.push_back(c);
    } else {
      digits.push_back(c);
    }
  }
  
  // 检查是否可以重组
  int m = letters.size();
  int n = digits.size();
  if (abs(m - n) > 1) {
    return "";
  }
  
  std::string result;
  result.reserve(s.size());
  
  // 交替合并，数量多的先放
  int i = 0, j = 0;
  if (m >= n) {
    // 字母多或相等，先放字母
    while (i < m || j < n) {
      if (i < m) result += letters[i++];
      if (j < n) result += digits[j++];
    }
  } else {
    // 数字多，先放数字
    while (i < m || j < n) {
      if (j < n) result += digits[j++];
      if (i < m) result += letters[i++];
    }
  }
  
  return result;
}

ReformatTheStringSolution::ReformatTheStringSolution() {
  setMetaInfo({.id = 1417,
               .title = "Reformat The String",
               .url = "https://leetcode.com/problems/reformat-the-string/"});
  registerStrategy("Separate & Merge", solution1);
}

std::string ReformatTheStringSolution::reformat(std::string s) {
  return getSolution()(s);
}

}  // namespace problem_1417
}  // namespace leetcode
