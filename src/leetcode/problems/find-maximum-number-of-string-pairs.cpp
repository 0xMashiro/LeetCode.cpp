#include "leetcode/problems/find-maximum-number-of-string-pairs.h"

namespace leetcode {
namespace problem_2744 {

// 哈希表解法
// 遍历每个字符串，检查其反转是否已存在于哈希表中
// 时间复杂度: O(n * L)，其中 n 是 words 长度，L 是字符串平均长度
// 空间复杂度: O(n * L)
static int solution1(vector<string>& words) {
  unordered_set<string> seen;  // 存储未配对的字符串
  int pairs = 0;
  
  for (const string& word : words) {
    string reversed = word;
    reverse(reversed.begin(), reversed.end());
    
    if (seen.find(reversed) != seen.end()) {
      // 找到配对
      pairs++;
      seen.erase(reversed);  // 移除已配对的字符串
    } else {
      // 未找到配对，加入集合等待后续配对
      seen.insert(word);
    }
  }
  
  return pairs;
}

FindMaximumNumberOfStringPairsSolution::FindMaximumNumberOfStringPairsSolution() {
  setMetaInfo({.id = 2744,
               .title = "Find Maximum Number of String Pairs",
               .url = "https://leetcode.com/problems/find-maximum-number-of-string-pairs/"});
  registerStrategy("Hash Set", solution1);
}

int FindMaximumNumberOfStringPairsSolution::maximumNumberOfStringPairs(vector<string>& words) {
  return getSolution()(words);
}

}  // namespace problem_2744
}  // namespace leetcode
