#include "leetcode/problems/reverse-words-in-a-string.h"

namespace leetcode {
namespace problem_151 {

// 方法一：使用字符串流分割单词，然后反转拼接
// 时间复杂度: O(n), 空间复杂度: O(n)
static string solution1(string s) {
  // 去除首尾空格
  int left = 0, right = s.size() - 1;
  while (left <= right && s[left] == ' ') left++;
  while (left <= right && s[right] == ' ') right--;
  
  if (left > right) return "";
  
  // 提取有效子串
  string trimmed = s.substr(left, right - left + 1);
  
  // 使用字符串流分割单词
  vector<string> words;
  string word;
  for (char c : trimmed) {
    if (c == ' ') {
      if (!word.empty()) {
        words.push_back(word);
        word.clear();
      }
    } else {
      word += c;
    }
  }
  if (!word.empty()) {
    words.push_back(word);
  }
  
  // 反转单词顺序并拼接
  string result;
  for (int i = words.size() - 1; i >= 0; i--) {
    result += words[i];
    if (i > 0) result += " ";
  }
  
  return result;
}

// 方法二：原地反转（双指针法）
// 1. 去除多余空格
// 2. 整体反转
// 3. 逐个单词反转
// 时间复杂度: O(n), 空间复杂度: O(1)（如果字符串可变）
static string solution2(string s) {
  // 去除多余空格
  int n = s.size();
  int i = 0, j = 0;
  
  // 跳过前导空格
  while (j < n && s[j] == ' ') j++;
  
  // 去除中间多余空格和尾随空格
  bool needSpace = false;
  while (j < n) {
    if (s[j] != ' ') {
      if (needSpace) {
        s[i++] = ' ';
        needSpace = false;
      }
      s[i++] = s[j];
    } else {
      needSpace = true;
    }
    j++;
  }
  
  // 截断有效部分
  s.resize(i);
  
  // 整体反转
  reverse(s.begin(), s.end());
  
  // 逐个单词反转
  int start = 0;
  for (int k = 0; k <= s.size(); k++) {
    if (k == s.size() || s[k] == ' ') {
      reverse(s.begin() + start, s.begin() + k);
      start = k + 1;
    }
  }
  
  return s;
}

ReverseWordsInAStringSolution::ReverseWordsInAStringSolution() {
  setMetaInfo({.id = 151,
               .title = "Reverse Words in a String",
               .url = "https://leetcode.com/problems/reverse-words-in-a-string/"});
  registerStrategy("Split and Reverse", solution1);
  registerStrategy("In-place Reverse", solution2);
}

string ReverseWordsInAStringSolution::reverseWords(string s) {
  return getSolution()(s);
}

}  // namespace problem_151
}  // namespace leetcode
