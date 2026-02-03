
#include "leetcode/problems/build-array-from-permutation.h"

namespace leetcode {
namespace problem_1920 {

// 直接遍历：创建新数组，ans[i] = nums[nums[i]]
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution1(vector<int>& nums) {
  const int n = nums.size();
  vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    ans[i] = nums[nums[i]];
  }
  return ans;
}

BuildArrayFromPermutationSolution::BuildArrayFromPermutationSolution() {
  setMetaInfo({.id = 1920,
               .title = "Build Array from Permutation",
               .url = "https://leetcode.com/problems/build-array-from-permutation/"});
  registerStrategy("Direct Traversal", solution1);
}

vector<int> BuildArrayFromPermutationSolution::buildArray(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_1920
}  // namespace leetcode
