
#include "leetcode/problems/lexicographically-smallest-string-after-reverse.h"

namespace leetcode {
namespace problem_3722 {

// 暴力枚举：枚举所有可能的 k，分别尝试反转前 k 个和后 k 个字符
// 时间复杂度: O(n²), 空间复杂度: O(n)
static string solution1(string s) {
  const int n = s.size();
  string result = s;  // 初始化结果为原字符串
  
  // 枚举所有可能的 k
  for (int k = 1; k <= n; ++k) {
    // 尝试反转前 k 个字符
    string temp1 = s;
    reverse(temp1.begin(), temp1.begin() + k);
    if (temp1 < result) {
      result = temp1;
    }
    
    // 尝试反转后 k 个字符
    string temp2 = s;
    reverse(temp2.end() - k, temp2.end());
    if (temp2 < result) {
      result = temp2;
    }
  }
  
  return result;
}

LexicographicallySmallestStringAfterReverseSolution::LexicographicallySmallestStringAfterReverseSolution() {
  setMetaInfo({.id = 3722,
               .title = "Lexicographically Smallest String After Reverse",
               .url = "https://leetcode.com/problems/lexicographically-smallest-string-after-reverse/"});
  registerStrategy("Brute Force", solution1);
}

string LexicographicallySmallestStringAfterReverseSolution::lexSmallest(string s) {
  return getSolution()(s);
}

}  // namespace problem_3722
}  // namespace leetcode
