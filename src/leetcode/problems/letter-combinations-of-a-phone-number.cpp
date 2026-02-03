
#include "leetcode/problems/letter-combinations-of-a-phone-number.h"

namespace leetcode {
namespace problem_17 {

// 回溯法生成所有组合
// 时间复杂度: O(3^n * 4^m)，n是映射到3个字母的数字个数，m是映射到4个字母的数字个数
// 空间复杂度: O(n)，递归栈深度
static vector<string> solution1(string digits) {
  if (digits.empty()) return {};
  
  // 数字到字母的映射
  const vector<string> phoneMap = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
  };
  
  vector<string> result;
  string current;
  
  function<void(int)> backtrack = [&](int index) {
    // 如果已经处理完所有数字，将当前组合加入结果
    if (index == digits.size()) {
      result.push_back(current);
      return;
    }
    
    // 获取当前数字对应的字母
    int digit = digits[index] - '0';
    const string& letters = phoneMap[digit];
    
    // 遍历当前数字对应的所有字母
    for (char c : letters) {
      current.push_back(c);
      backtrack(index + 1);
      current.pop_back();  // 回溯
    }
  };
  
  backtrack(0);
  return result;
}

// 迭代法：使用队列
// 时间复杂度: O(3^n * 4^m)
// 空间复杂度: O(3^n * 4^m)，存储所有组合
static vector<string> solution2(string digits) {
  if (digits.empty()) return {};
  
  const vector<string> phoneMap = {
    "",
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
  };
  
  vector<string> result;
  result.push_back("");
  
  for (char d : digits) {
    int digit = d - '0';
    const string& letters = phoneMap[digit];
    vector<string> newResult;
    
    for (const string& s : result) {
      for (char c : letters) {
        newResult.push_back(s + c);
      }
    }
    
    result = std::move(newResult);
  }
  
  return result;
}

LetterCombinationsOfAPhoneNumberSolution::LetterCombinationsOfAPhoneNumberSolution() {
  setMetaInfo({.id = 17,
               .title = "Letter Combinations of a Phone Number",
               .url = "https://leetcode.com/problems/letter-combinations-of-a-phone-number/"});
  registerStrategy("Backtracking", solution1);
  registerStrategy("Iterative", solution2);
}

vector<string> LetterCombinationsOfAPhoneNumberSolution::letterCombinations(string digits) {
  return getSolution()(digits);
}

}  // namespace problem_17
}  // namespace leetcode
