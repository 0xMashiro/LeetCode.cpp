
#include "leetcode/problems/vowel-consonant-score.h"

namespace leetcode {
namespace problem_3813 {

// 解法：遍历统计元音和辅音
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(std::string s) {
  int vowels = 0;
  int consonants = 0;
  
  for (char ch : s) {
    if (ch >= 'a' && ch <= 'z') {
      if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
        vowels++;
      } else {
        consonants++;
      }
    }
    // 空格和数字跳过
  }
  
  if (consonants == 0) return 0;
  return vowels / consonants;  // 整数除法自动向下取整
}

// 解法2：使用集合判断元音
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution2(std::string s) {
  int vowels = 0;
  int consonants = 0;
  std::unordered_set<char> vowelSet = {'a', 'e', 'i', 'o', 'u'};
  
  for (char ch : s) {
    if (ch >= 'a' && ch <= 'z') {
      if (vowelSet.count(ch)) {
        vowels++;
      } else {
        consonants++;
      }
    }
  }
  
  if (consonants == 0) return 0;
  return vowels / consonants;
}

VowelConsonantScoreSolution::VowelConsonantScoreSolution() {
  setMetaInfo({.id = 3813,
               .title = "Vowel-Consonant Score",
               .url = "https://leetcode.com/problems/vowel-consonant-score/"});
  registerStrategy("Direct Count", solution1);
  registerStrategy("Hash Set", solution2);
}

int VowelConsonantScoreSolution::vowelConsonantScore(std::string s) {
  return getSolution()(s);
}

}  // namespace problem_3813
}  // namespace leetcode
