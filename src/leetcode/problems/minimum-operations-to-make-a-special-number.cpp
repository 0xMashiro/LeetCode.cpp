#include "leetcode/problems/minimum-operations-to-make-a-special-number.h"

namespace leetcode {
namespace problem_2844 {

/**
 * 思路：枚举所有能被25整除的后缀
 * 一个数能被25整除，当且仅当它以 00, 25, 50, 或 75 结尾
 * 我们需要从字符串末尾开始，找到这些模式之一
 * 对于每种模式，从后往前找对应的两个字符，计算需要删除的字符数
 * 时间复杂度: O(n), 空间复杂度: O(1)
 */
static int solution(string num) {
  int n = num.size();
  int ans = n;  // 最坏情况：删除所有字符变成 "0"
  
  // 需要匹配的4种后缀模式
  const vector<string> patterns = {"00", "25", "50", "75"};
  
  for (const string& pat : patterns) {
    // 从后往前找第二个字符 pat[1]
    int j = n - 1;
    while (j >= 0 && num[j] != pat[1]) {
      j--;
    }
    if (j < 0) continue;  // 没找到第二个字符
    
    // 从 j-1 往前找第一个字符 pat[0]
    int i = j - 1;
    while (i >= 0 && num[i] != pat[0]) {
      i--;
    }
    if (i < 0) continue;  // 没找到第一个字符
    
    // 找到了模式，计算删除次数：删除 (j-i-1) 个中间字符 + 删除 (n-1-j) 个后缀字符
    // = n - j - 1 + j - i - 1 = n - i - 2
    // 或者直接算：需要保留 i 和 j 位置的字符，删除其他 (n - 2) 个以外的
    ans = min(ans, n - i - 2);
  }
  
  // 特殊情况：如果字符串中有 '0'，可以只保留这个 '0'，删除其他 n-1 个字符
  for (char c : num) {
    if (c == '0') {
      ans = min(ans, n - 1);
      break;
    }
  }
  
  return ans;
}

MinimumOperationsToMakeASpecialNumberSolution::MinimumOperationsToMakeASpecialNumberSolution() {
  setMetaInfo({
    .id = 2844,
    .title = "Minimum Operations to Make a Special Number",
    .url = "https://leetcode.com/problems/minimum-operations-to-make-a-special-number/"
  });
  registerStrategy("Greedy", solution);
}

int MinimumOperationsToMakeASpecialNumberSolution::minimumOperations(string num) {
  return getSolution()(num);
}

}  // namespace problem_2844
}  // namespace leetcode
