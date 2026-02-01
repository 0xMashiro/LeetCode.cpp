#include "leetcode/problems/check-if-word-equals-summation-of-two-words.h"

namespace leetcode {
namespace problem_1880 {

/**
 * 将单词转换为数值
 * 每个字母 a-j 对应数字 0-9
 */
static int wordToNum(const string& word) {
  int result = 0;
  for (char c : word) {
    result = result * 10 + (c - 'a');
  }
  return result;
}

/**
 * 主解法：将三个单词都转为数值，然后判断前两个之和是否等于第三个
 * 时间复杂度：O(L)，L 为字符串总长度（最大 24）
 * 空间复杂度：O(1)
 */
static bool solution1(string firstWord, string secondWord, string targetWord) {
  int num1 = wordToNum(firstWord);
  int num2 = wordToNum(secondWord);
  int target = wordToNum(targetWord);
  return num1 + num2 == target;
}

CheckIfWordEqualsSummationOfTwoWordsSolution::CheckIfWordEqualsSummationOfTwoWordsSolution() {
  setMetaInfo({
    .id = 1880,
    .title = "Check if Word Equals Summation of Two Words",
    .url = "https://leetcode.com/problems/check-if-word-equals-summation-of-two-words/"
  });
  registerStrategy("Convert to Numbers", solution1);
}

bool CheckIfWordEqualsSummationOfTwoWordsSolution::isSumEqual(string firstWord, string secondWord, string targetWord) {
  return getSolution()(firstWord, secondWord, targetWord);
}

}  // namespace problem_1880
}  // namespace leetcode
