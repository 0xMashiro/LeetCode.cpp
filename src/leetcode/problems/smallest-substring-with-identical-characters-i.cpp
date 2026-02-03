#include "leetcode/problems/smallest-substring-with-identical-characters-i.h"

namespace leetcode {
namespace problem_3398 {

// 计算将 s 变成以 '0' 或 '1' 开头的交替字符串所需的最少操作次数
static int calcOpsForAlternating(const string& s, char start) {
  int ops = 0;
  for (int i = 0; i < s.size(); ++i) {
    char expected = (i % 2 == 0) ? start : (start == '0' ? '1' : '0');
    if (s[i] != expected) {
      ++ops;
    }
  }
  return ops;
}

// 判断：能否通过不超过 maxOps 次操作，使得所有连续相同字符子串长度不超过 maxLen
static bool canAchieve(const string& s, int maxLen, int maxOps) {
  if (maxLen == 1) {
    // 需要变成交替字符串，取两种模式的最小值
    int ops1 = calcOpsForAlternating(s, '0');
    int ops2 = calcOpsForAlternating(s, '1');
    return min(ops1, ops2) <= maxOps;
  }
  
  // maxLen >= 2 的情况
  int ops = 0;
  int i = 0;
  int n = s.size();
  
  while (i < n) {
    char cur = s[i];
    int count = 0;
    // 统计当前连续相同字符的长度
    while (i < n && s[i] == cur) {
      ++count;
      ++i;
    }
    // 需要打断 count / (maxLen + 1) 次
    // 解释：每隔 maxLen 个字符就需要一个翻转点来打断
    // 例如：count=3, maxLen=2，需要 3/(2+1) = 1 次翻转
    ops += count / (maxLen + 1);
  }
  
  return ops <= maxOps;
}

static int solution1(string& s, int numOps) {
  int n = s.size();
  int left = 1, right = n;
  int ans = n;
  
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (canAchieve(s, mid, numOps)) {
      ans = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  
  return ans;
}

SmallestSubstringWithIdenticalCharactersISolution::SmallestSubstringWithIdenticalCharactersISolution() {
  setMetaInfo({
    .id = 3398,
    .title = "Smallest Substring With Identical Characters I",
    .url = "https://leetcode.com/problems/smallest-substring-with-identical-characters-i/"
  });
  registerStrategy("Binary Search + Greedy", solution1);
}

int SmallestSubstringWithIdenticalCharactersISolution::minLength(string s, int numOps) {
  return getSolution()(s, numOps);
}

}  // namespace problem_3398
}  // namespace leetcode