#include "leetcode/problems/minimum-deletions-to-make-string-balanced.h"

namespace leetcode {
namespace problem_1653 {

// 前缀和思路：枚举分割点
// 对于平衡的字符串，一定是 "a...ab...b" 的形式
// 枚举分割点 i，表示前 i 个字符全变成 'a'，后面全变成 'b'
// 需要删除的次数 = 前i个字符中'b'的数量 + 后面字符中'a'的数量
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(string s) {
  const int n = s.size();
  
  // rightA[i] 表示 s[i..n-1] 中 'a' 的数量
  vector<int> rightA(n + 1, 0);
  for (int i = n - 1; i >= 0; --i) {
    rightA[i] = rightA[i + 1] + (s[i] == 'a' ? 1 : 0);
  }
  
  // leftB 表示当前位置之前 'b' 的数量（用变量代替数组）
  int leftB = 0;
  int result = n;  // 最多删除所有字符
  
  // 枚举分割点 i（0 到 n）
  // i=0: 全变成 'b'，需要删除所有 'a'
  // i=n: 全变成 'a'，需要删除所有 'b'
  for (int i = 0; i <= n; ++i) {
    // 前 i 个字符中 'b' 的数量是 leftB
    // 后面 s[i..n-1] 中 'a' 的数量是 rightA[i]
    result = min(result, leftB + rightA[i]);
    
    // 更新 leftB，为下一个分割点做准备
    if (i < n && s[i] == 'b') {
      leftB++;
    }
  }
  
  return result;
}

// 优化版本：使用变量代替数组，空间复杂度 O(1)
// 先统计总的 'a' 的数量，然后遍历过程中动态维护
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution2(string s) {
  const int n = s.size();
  
  // 统计总的 'a' 的数量
  int totalA = 0;
  for (char c : s) {
    if (c == 'a') totalA++;
  }
  
  // leftB: 当前位置左边 'b' 的数量
  // rightA: 当前位置右边 'a' 的数量 = totalA - 当前位置及左边 'a' 的数量
  int leftB = 0;
  int leftA = 0;
  int result = n;
  
  // 枚举分割点（在位置 i 之前分割）
  for (int i = 0; i <= n; ++i) {
    int rightA = totalA - leftA;
    result = min(result, leftB + rightA);
    
    if (i < n) {
      if (s[i] == 'a') leftA++;
      else leftB++;
    }
  }
  
  return result;
}

MinimumDeletionsToMakeStringBalancedSolution::MinimumDeletionsToMakeStringBalancedSolution() {
  setMetaInfo({
    .id = 1653,
    .title = "Minimum Deletions to Make String Balanced",
    .url = "https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/"
  });
  registerStrategy("Prefix Sum", solution1);
  registerStrategy("Optimized O(1) Space", solution2);
}

int MinimumDeletionsToMakeStringBalancedSolution::minimumDeletions(string s) {
  return getSolution()(s);
}

}  // namespace problem_1653
}  // namespace leetcode
