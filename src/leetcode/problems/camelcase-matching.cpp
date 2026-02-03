#include "leetcode/problems/camelcase-matching.h"

namespace leetcode {
namespace problem_1023 {

/**
 * 双指针法判断单个 query 是否匹配 pattern
 * 
 * 思路：
 * - 用 i 遍历 query，j 遍历 pattern
 * - 如果字符相等，两个指针都前进
 * - 如果 query[i] 是小写字母但不等于 pattern[j]，跳过 query[i]（相当于插入）
 * - 如果 query[i] 是大写字母但不等于 pattern[j]，匹配失败
 * - 最后检查 pattern 是否完全匹配，且 query 剩余字符中没有额外大写字母
 */
static bool matchSingle(const string& query, const string& pattern) {
  int i = 0, j = 0;
  int n = query.size(), m = pattern.size();
  
  while (i < n && j < m) {
    if (query[i] == pattern[j]) {
      // 字符匹配，两个指针都前进
      i++;
      j++;
    } else if (islower(query[i])) {
      // query[i] 是小写字母，可以插入，跳过
      i++;
    } else {
      // query[i] 是大写字母但不匹配 pattern[j]，匹配失败
      return false;
    }
  }
  
  // pattern 必须完全匹配
  if (j != m) {
    return false;
  }
  
  // query 剩余字符必须都是小写字母
  while (i < n) {
    if (isupper(query[i])) {
      return false;
    }
    i++;
  }
  
  return true;
}

/**
 * 主函数：处理所有 queries
 * 时间复杂度: O(n * m)，其中 n 是 queries 长度，m 是平均 query 长度
 * 空间复杂度: O(1)，不包括返回结果
 */
static vector<bool> solution1(vector<string>& queries, string pattern) {
  vector<bool> result;
  result.reserve(queries.size());
  
  for (const auto& query : queries) {
    result.push_back(matchSingle(query, pattern));
  }
  
  return result;
}

CamelcaseMatchingSolution::CamelcaseMatchingSolution() {
  setMetaInfo({
    .id = 1023,
    .title = "Camelcase Matching",
    .url = "https://leetcode.com/problems/camelcase-matching/"
  });
  registerStrategy("Two Pointers", solution1);
}

vector<bool> CamelcaseMatchingSolution::camelMatch(vector<string>& queries, string pattern) {
  return getSolution()(queries, pattern);
}

}  // namespace problem_1023
}  // namespace leetcode
