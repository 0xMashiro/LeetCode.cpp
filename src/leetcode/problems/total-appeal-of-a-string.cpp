#include "leetcode/problems/total-appeal-of-a-string.h"

namespace leetcode {
namespace problem_2262 {

/**
 * 计算字符串所有子串的吸引力之和
 * 
 * 算法：对于每个位置 i，计算 s[i] 作为最左出现时能贡献多少个子串
 * - 起始位置必须在 (last_pos, i] 范围内，使得 s[i] 是该子串中该字符的最左出现
 * - 结束位置可以是 [i, n-1] 中的任意位置
 */
static long long solution1(string& s) {
  const int n = s.size();
  long long total = 0;
  
  // 记录每个字符（'a'-'z'）上次出现的位置，初始为 -1
  int lastPos[26];
  std::fill(std::begin(lastPos), std::end(lastPos), -1);
  
  for (int i = 0; i < n; ++i) {
    int idx = s[i] - 'a';
    // 起始位置可选数量：i - lastPos[idx]
    // 结束位置可选数量：n - i
    long long startChoices = i - lastPos[idx];
    long long endChoices = n - i;
    total += startChoices * endChoices;
    // 更新最后出现位置
    lastPos[idx] = i;
  }
  
  return total;
}

/**
 * 另一种实现：使用 long long 数组避免类型转换
 */
static long long solution2(string& s) {
  const int n = static_cast<int>(s.size());
  long long total = 0;
  
  // 记录每个字符上次出现的位置，初始为 -1
  vector<long long> lastPos(26, -1);
  
  for (int i = 0; i < n; ++i) {
    int idx = s[i] - 'a';
    // 计算该位置字符的贡献
    long long leftCount = i - lastPos[idx];  // 起始位置选择数
    long long rightCount = n - i;             // 结束位置选择数
    total += leftCount * rightCount;
    lastPos[idx] = i;
  }
  
  return total;
}

TotalAppealOfAStringSolution::TotalAppealOfAStringSolution() {
  setMetaInfo({
    .id = 2262,
    .title = "Total Appeal of A String",
    .url = "https://leetcode.com/problems/total-appeal-of-a-string/"
  });
  registerStrategy("Array-based", solution1);
  registerStrategy("Vector-based", solution2);
}

long long TotalAppealOfAStringSolution::appealSum(string s) {
  return getSolution()(s);
}

}  // namespace problem_2262
}  // namespace leetcode
