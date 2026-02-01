#include "leetcode/problems/redistribute-characters-to-make-all-strings-equal.h"

namespace leetcode {
namespace problem_1897 {

/**
 * 核心思路：
 * 要使所有字符串相等，需要每个字符在所有字符串中出现的总次数能被 n 整除
 * 这样每个字符串才能分配到相同数量的该字符
 * 
 * 时间复杂度: O(N * L)，其中 N 是 words 长度，L 是平均字符串长度
 * 空间复杂度: O(1)，只使用固定大小的计数数组（26个字母）
 */
static bool solution1(vector<string>& words) {
  int n = words.size();
  if (n <= 1) return true;  // 0个或1个字符串，本身就是相等的
  
  // 统计每个字符出现的总次数
  int count[26] = {0};
  for (const string& word : words) {
    for (char c : word) {
      count[c - 'a']++;
    }
  }
  
  // 检查每个字符的总次数是否能被 n 整除
  for (int i = 0; i < 26; i++) {
    if (count[i] % n != 0) {
      return false;
    }
  }
  
  return true;
}

RedistributeCharactersToMakeAllStringsEqualSolution::RedistributeCharactersToMakeAllStringsEqualSolution() {
  setMetaInfo({.id = 1897,
               .title = "Redistribute Characters to Make All Strings Equal",
               .url = "https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/"});
  registerStrategy("Counting", solution1);
}

bool RedistributeCharactersToMakeAllStringsEqualSolution::makeEqual(vector<string>& words) {
  return getSolution()(words);
}

}  // namespace problem_1897
}  // namespace leetcode
