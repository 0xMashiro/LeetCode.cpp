#include "leetcode/problems/number-of-substrings-containing-all-three-characters.h"

namespace leetcode {
namespace problem_1358 {

// 滑动窗口：记录每个字符最后出现的位置
// 对于位置 i，如果三种字符都出现过，则 min_pos = min(last_a, last_b, last_c)
// 所有起始位置在 [0, min_pos] 的子字符串都满足条件，数量为 min_pos + 1
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(string s) {
  const int n = s.size();
  int last_a = -1, last_b = -1, last_c = -1;
  long long result = 0;
  
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'a') last_a = i;
    else if (s[i] == 'b') last_b = i;
    else last_c = i;
    
    // 如果三种字符都已经出现
    if (last_a != -1 && last_b != -1 && last_c != -1) {
      int min_pos = min({last_a, last_b, last_c});
      result += min_pos + 1;
    }
  }
  
  return static_cast<int>(result);
}

// 另一种实现：使用数组存储最后位置
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution2(string s) {
  const int n = s.size();
  int last[3] = {-1, -1, -1};  // 分别记录 'a', 'b', 'c' 的最后位置
  long long result = 0;
  
  for (int i = 0; i < n; ++i) {
    last[s[i] - 'a'] = i;
    // 如果三种字符都已经出现
    if (last[0] != -1 && last[1] != -1 && last[2] != -1) {
      result += min({last[0], last[1], last[2]}) + 1;
    }
  }
  
  return static_cast<int>(result);
}

NumberOfSubstringsContainingAllThreeCharactersSolution::NumberOfSubstringsContainingAllThreeCharactersSolution() {
  setMetaInfo({
    .id = 1358,
    .title = "Number of Substrings Containing All Three Characters",
    .url = "https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/"
  });
  registerStrategy("Sliding Window (Variables)", solution1);
  registerStrategy("Sliding Window (Array)", solution2);
}

int NumberOfSubstringsContainingAllThreeCharactersSolution::numberOfSubstrings(string s) {
  return getSolution()(s);
}

}  // namespace problem_1358
}  // namespace leetcode
