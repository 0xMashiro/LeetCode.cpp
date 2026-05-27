#include "leetcode/problems/count-the-number-of-special-characters-ii.h"

namespace leetcode {
namespace problem_3121 {

// 状态机一次扫描：记录每个字母的状态
// 状态定义：0=未见过, 1=仅见过小写, 2=先见过大写(invalid), 3=先小写后大写(special)
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(std::string word) {
  // state[i]: 0=unseen, 1=only lowercase seen, 2=uppercase first (invalid), 3=lowercase then uppercase (special)
  int state[26] = {0};
  int ans = 0;

  for (char ch : word) {
    if (ch >= 'a' && ch <= 'z') {
      int idx = ch - 'a';
      if (state[idx] == 0) {
        state[idx] = 1;  // first time seeing lowercase
      }
      // state 1: already lowercase seen, stay
      // state 2: uppercase already seen before any lowercase -> invalid, stay invalid
      // state 3: already special, but seeing another lowercase after uppercase -> invalid!
      // Actually re-read the problem: "every lowercase occurrence of c appears before the first uppercase occurrence of c"
      // If we already had state 3 (lowercase -> uppercase), and then we see another lowercase,
      // that lowercase appears AFTER the first uppercase! So it invalidates.
      else if (state[idx] == 3) {
        state[idx] = 2;  // invalidate: found lowercase after uppercase
        --ans;
      }
    } else {  // uppercase
      int idx = ch - 'A';
      if (state[idx] == 0) {
        state[idx] = 2;  // uppercase first -> invalid
      } else if (state[idx] == 1) {
        state[idx] = 3;  // lowercase then uppercase -> special!
        ++ans;
      }
      // state 2: already invalid, stay
      // state 3: already special, another uppercase is fine (stays special)
    }
  }

  return ans;
}

// 预处理位置法：记录每个字母最后一个小写位置和第一个大写位置
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution2(std::string word) {
  int lastLower[26];
  int firstUpper[26];
  // 初始化
  for (int i = 0; i < 26; ++i) {
    lastLower[i] = -1;
    firstUpper[i] = INT_MAX;
  }

  const int n = word.size();
  for (int i = 0; i < n; ++i) {
    char ch = word[i];
    if (ch >= 'a' && ch <= 'z') {
      int idx = ch - 'a';
      lastLower[idx] = i;  // 不断更新到最后一个小写位置
    } else {
      int idx = ch - 'A';
      if (firstUpper[idx] == INT_MAX) {
        firstUpper[idx] = i;  // 只记录第一个大写位置
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < 26; ++i) {
    if (lastLower[i] != -1 && firstUpper[i] != INT_MAX && lastLower[i] < firstUpper[i]) {
      ++ans;
    }
  }
  return ans;
}

CountTheNumberOfSpecialCharactersIiSolution::CountTheNumberOfSpecialCharactersIiSolution() {
  setMetaInfo({.id = 3121,
               .title = "Count the Number of Special Characters II",
               .url = "https://leetcode.com/problems/count-the-number-of-special-characters-ii/"});
  // 方案1 是最优解（状态机一次扫描），方案2 是另一种思路（预处理位置法）
  registerStrategy("State Machine", solution1);
  registerStrategy("Position Tracking", solution2);
}

int CountTheNumberOfSpecialCharactersIiSolution::numberOfSpecialChars(std::string word) {
  return getSolution()(word);
}

}  // namespace problem_3121
}  // namespace leetcode
