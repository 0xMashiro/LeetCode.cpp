#include "leetcode/problems/largest-number-after-mutating-substring.h"

namespace leetcode {
namespace problem_1946 {

// 贪心策略：找到最优子串进行变异
// 1. 从左找第一个 change[d] > d 的位置作为起点
// 2. 从起点开始向右，继续变异直到遇到 change[d] < d 的位置
// 3. 如果 change[d] == d，可以继续包含在子串中
// 时间复杂度: O(n), 空间复杂度: O(1)
static std::string solution(std::string& num, std::vector<int>& change) {
  const int n = num.size();
  int start = 0;
  
  // 找到第一个可以变大的位置（跳过那些不会变大的位置）
  while (start < n && change[num[start] - '0'] <= num[start] - '0') {
    start++;
  }
  
  // 如果没有可以变大的位置，直接返回原字符串
  if (start == n) {
    return num;
  }
  
  // 从起点开始变异，直到遇到一个数字变异后变小
  int i = start;
  while (i < n && change[num[i] - '0'] >= num[i] - '0') {
    num[i] = '0' + change[num[i] - '0'];
    i++;
  }
  
  return num;
}

LargestNumberAfterMutatingSubstringSolution::LargestNumberAfterMutatingSubstringSolution() {
  setMetaInfo({
    .id = 1946,
    .title = "Largest Number After Mutating Substring",
    .url = "https://leetcode.com/problems/largest-number-after-mutating-substring/"
  });
  registerStrategy("Greedy", solution);
}

std::string LargestNumberAfterMutatingSubstringSolution::maximumNumber(std::string num, std::vector<int>& change) {
  return getSolution()(num, change);
}

}  // namespace problem_1946
}  // namespace leetcode
