#include "leetcode/problems/find-words-containing-character.h"

namespace leetcode {
namespace problem_2942 {

// 遍历每个单词，检查是否包含字符 x
// 时间复杂度: O(n * m)，其中 n 是 words 长度，m 是单词平均长度
// 空间复杂度: O(1)，不计结果数组
static vector<int> solution1(vector<string>& words, char x) {
  vector<int> result;
  for (int i = 0; i < words.size(); ++i) {
    if (words[i].find(x) != string::npos) {
      result.push_back(i);
    }
  }
  return result;
}

FindWordsContainingCharacterSolution::FindWordsContainingCharacterSolution() {
  setMetaInfo({.id = 2942,
               .title = "Find Words Containing Character",
               .url = "https://leetcode.com/problems/find-words-containing-character/"});
  registerStrategy("Linear Scan", solution1);
}

vector<int> FindWordsContainingCharacterSolution::findWordsContaining(vector<string>& words, char x) {
  return getSolution()(words, x);
}

}  // namespace problem_2942
}  // namespace leetcode