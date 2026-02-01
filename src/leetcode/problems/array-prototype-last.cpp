#include "leetcode/problems/array-prototype-last.h"

namespace leetcode {
namespace problem_2619 {

// 简单实现：检查数组是否为空，返回最后一个元素或 -1
// 时间复杂度: O(1), 空间复杂度: O(1)
static int solution1(vector<int>& nums) {
  if (nums.empty()) {
    return -1;
  }
  return nums.back();
}

ArrayPrototypeLastSolution::ArrayPrototypeLastSolution() {
  setMetaInfo({.id = 2619,
               .title = "Array Prototype Last",
               .url = "https://leetcode.com/problems/array-prototype-last/"});
  registerStrategy("Simple", solution1);
}

int ArrayPrototypeLastSolution::last(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2619
}  // namespace leetcode
