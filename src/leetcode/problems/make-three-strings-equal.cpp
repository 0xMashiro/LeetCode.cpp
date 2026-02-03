#include "leetcode/problems/make-three-strings-equal.h"

namespace leetcode {
namespace problem_2937 {

// 解法：寻找最长公共前缀
// 每次操作只能删除字符串末尾的字符，所以最终三个字符串会变成某个公共前缀
// 1. 找到三个字符串的最长公共前缀长度
// 2. 如果公共前缀长度为0，返回-1（无法使它们相等）
// 3. 操作次数 = (len1 - common) + (len2 - common) + (len3 - common)
// 时间复杂度: O(min(len1, len2, len3)), 空间复杂度: O(1)
static int solution1(string s1, string s2, string s3) {
  int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
  
  // 找到三个字符串的最小长度
  int min_len = min({n1, n2, n3});
  
  // 寻找最长公共前缀长度
  int common = 0;
  while (common < min_len && s1[common] == s2[common] && s2[common] == s3[common]) {
    ++common;
  }
  
  // 如果没有公共前缀，无法使它们相等
  if (common == 0) {
    return -1;
  }
  
  // 计算需要的操作次数
  return (n1 - common) + (n2 - common) + (n3 - common);
}

MakeThreeStringsEqualSolution::MakeThreeStringsEqualSolution() {
  setMetaInfo({.id = 2937,
               .title = "Make Three Strings Equal",
               .url = "https://leetcode.com/problems/make-three-strings-equal/"});
  registerStrategy("Longest Common Prefix", solution1);
}

int MakeThreeStringsEqualSolution::findMinimumOperations(string s1, string s2, string s3) {
  return getSolution()(s1, s2, s3);
}

}  // namespace problem_2937
}  // namespace leetcode
