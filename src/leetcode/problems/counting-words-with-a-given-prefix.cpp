#include "leetcode/problems/counting-words-with-a-given-prefix.h"

namespace leetcode {
namespace problem_2185 {

// 使用 string::compare 检查前缀
// 时间复杂度: O(n * m), 其中 n 是 words 长度，m 是 pref 长度
// 空间复杂度: O(1)
static int solution1(vector<string>& words, string pref) {
  int count = 0;
  size_t prefLen = pref.size();
  for (const auto& word : words) {
    // 只有当 word 长度 >= pref 长度时才可能是前缀
    if (word.size() >= prefLen && word.compare(0, prefLen, pref) == 0) {
      ++count;
    }
  }
  return count;
}

// 使用 string::substr 检查前缀（另一种实现方式）
// 时间复杂度: O(n * m)
// 空间复杂度: O(m) - substr 会创建临时字符串
static int solution2(vector<string>& words, string pref) {
  int count = 0;
  size_t prefLen = pref.size();
  for (const auto& word : words) {
    if (word.size() >= prefLen && word.substr(0, prefLen) == pref) {
      ++count;
    }
  }
  return count;
}

CountingWordsWithAGivenPrefixSolution::CountingWordsWithAGivenPrefixSolution() {
  setMetaInfo({.id = 2185,
               .title = "Counting Words With a Given Prefix",
               .url = "https://leetcode.com/problems/counting-words-with-a-given-prefix/"});
  registerStrategy("Compare Method", solution1);
  registerStrategy("Substring Method", solution2);
}

int CountingWordsWithAGivenPrefixSolution::prefixCount(vector<string>& words, string pref) {
  return getSolution()(words, pref);
}

}  // namespace problem_2185
}  // namespace leetcode
