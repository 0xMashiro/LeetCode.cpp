#include "leetcode/problems/minimum-number-of-operations-to-make-array-empty.h"

namespace leetcode {
namespace problem_2870 {

// 统计频率 + 贪心
// 对于每个出现次数 f：
// - f = 1 时无法操作，返回 -1
// - f > 1 时，最少操作数为 ceil(f/3) = (f + 2) / 3
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<int>& nums) {
  unordered_map<int, int> freq;
  for (int num : nums) {
    ++freq[num];
  }
  
  int operations = 0;
  for (const auto& [num, count] : freq) {
    if (count == 1) {
      return -1;
    }
    operations += (count + 2) / 3;
  }
  
  return operations;
}

MinimumNumberOfOperationsToMakeArrayEmptySolution::MinimumNumberOfOperationsToMakeArrayEmptySolution() {
  setMetaInfo({.id = 2870,
               .title = "Minimum Number of Operations to Make Array Empty",
               .url = "https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/"});
  registerStrategy("Hash Count + Greedy", solution1);
}

int MinimumNumberOfOperationsToMakeArrayEmptySolution::minOperations(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2870
}  // namespace leetcode
