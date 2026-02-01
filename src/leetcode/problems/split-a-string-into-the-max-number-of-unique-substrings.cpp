#include "leetcode/problems/split-a-string-into-the-max-number-of-unique-substrings.h"

namespace leetcode {
namespace problem_1593 {

// 回溯法：枚举所有可能的拆分方案
// 时间复杂度: O(2^n * n)，空间复杂度: O(n)
static int solution1(string s) {
  int n = s.size();
  int maxCount = 0;
  unordered_set<string> used;
  
  function<void(int, int)> dfs = [&](int start, int count) {
    // 如果已经遍历完所有字符，更新最大数量
    if (start == n) {
      maxCount = max(maxCount, count);
      return;
    }
    
    // 尝试所有可能的结束位置
    for (int end = start + 1; end <= n; ++end) {
      string substr = s.substr(start, end - start);
      // 如果子字符串未被使用过，尝试使用它
      if (used.find(substr) == used.end()) {
        used.insert(substr);
        dfs(end, count + 1);
        used.erase(substr);  // 回溯
      }
    }
  };
  
  dfs(0, 0);
  return maxCount;
}

SplitAStringIntoTheMaxNumberOfUniqueSubstringsSolution::SplitAStringIntoTheMaxNumberOfUniqueSubstringsSolution() {
  setMetaInfo({.id = 1593,
               .title = "Split a String Into the Max Number of Unique Substrings",
               .url = "https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/"});
  registerStrategy("Backtracking", solution1);
}

int SplitAStringIntoTheMaxNumberOfUniqueSubstringsSolution::maxUniqueSplit(string s) {
  return getSolution()(s);
}

}  // namespace problem_1593
}  // namespace leetcode
