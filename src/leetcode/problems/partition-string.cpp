#include "leetcode/problems/partition-string.h"

namespace leetcode {
namespace problem_3597 {

// 贪心策略：逐步构建段，直到遇到唯一段
// 使用哈希集合记录已出现的段
// 时间复杂度: O(n * m) 其中 n 是字符串长度，m 是平均段长度
// 空间复杂度: O(n) 存储已出现的段
static vector<string> solution1(string s) {
  vector<string> result;
  unordered_set<string> seen;
  string current;
  
  for (char c : s) {
    current += c;
    // 如果当前段已出现过，继续扩展
    if (seen.find(current) != seen.end()) {
      continue;
    }
    // 当前段是唯一的，加入结果
    result.push_back(current);
    seen.insert(current);
    current.clear();
  }
  
  return result;
}

PartitionStringSolution::PartitionStringSolution() {
  setMetaInfo({.id = 3597,
               .title = "Partition String",
               .url = "https://leetcode.com/problems/partition-string/"});
  registerStrategy("Greedy", solution1);
}

vector<string> PartitionStringSolution::partitionString(string s) {
  return getSolution()(s);
}

}  // namespace problem_3597
}  // namespace leetcode
