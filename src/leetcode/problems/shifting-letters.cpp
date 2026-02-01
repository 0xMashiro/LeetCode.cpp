#include "leetcode/problems/shifting-letters.h"

namespace leetcode {
namespace problem_848 {

// 后缀和优化解法
// 观察：第 i 个字符会被 shifts[i], shifts[i+1], ..., shifts[n-1] 影响
// 所以从后往前计算后缀和，每个字符移动 suffixSum[i] % 26 位
// 时间复杂度: O(n), 空间复杂度: O(1)
static string solution1(string s, vector<int>& shifts) {
  const int n = s.size();
  long long suffixSum = 0;  // 使用 long long 避免溢出
  
  for (int i = n - 1; i >= 0; --i) {
    suffixSum += shifts[i];
    // 计算新字符位置：(原位置 + 移动位数) % 26
    int newPos = (s[i] - 'a' + suffixSum) % 26;
    s[i] = 'a' + newPos;
  }
  
  return s;
}

ShiftingLettersSolution::ShiftingLettersSolution() {
  setMetaInfo({.id = 848,
               .title = "Shifting Letters",
               .url = "https://leetcode.com/problems/shifting-letters/"});
  registerStrategy("Suffix Sum", solution1);
}

string ShiftingLettersSolution::shiftingLetters(string s, vector<int>& shifts) {
  return getSolution()(s, shifts);
}

}  // namespace problem_848
}  // namespace leetcode
