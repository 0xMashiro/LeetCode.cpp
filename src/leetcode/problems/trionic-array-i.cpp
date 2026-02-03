#include "leetcode/problems/trionic-array-i.h"

namespace leetcode {
namespace problem_3637 {

// 单遍扫描：先找到峰值点 p，再找谷底点 q，最后验证第三段递增
// 时间复杂度: O(n), 空间复杂度: O(1)
static bool solution1(vector<int>& nums) {
  const int n = nums.size();
  if (n < 3) return false;
  
  int i = 0;
  
  // 找第一段严格递增的终点 p（峰值）
  // 必须至少有一个递增，所以 p >= 1
  while (i + 1 < n && nums[i] < nums[i + 1]) {
    ++i;
  }
  
  // 如果 i == 0，说明没有递增段
  // 如果 i == n-1，说明整个数组递增，没有递减段
  if (i == 0 || i == n - 1) return false;
  
  int p = i;
  
  // 找第二段严格递减的终点 q（谷底）
  // 必须至少有一个递减，所以 q > p
  while (i + 1 < n && nums[i] > nums[i + 1]) {
    ++i;
  }
  
  // 如果没有递减段，或者 i 到了数组末尾（没有第三段）
  if (i == p || i == n - 1) return false;
  
  int q = i;
  
  // 验证第三段严格递增
  while (i + 1 < n && nums[i] < nums[i + 1]) {
    ++i;
  }
  
  // 必须走到数组末尾
  return i == n - 1;
}

TrionicArrayISolution::TrionicArrayISolution() {
  setMetaInfo({.id = 3637,
               .title = "Trionic Array I",
               .url = "https://leetcode.com/problems/trionic-array-i/"});
  registerStrategy("Single Pass", solution1);
}

bool TrionicArrayISolution::isTrionic(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3637
}  // namespace leetcode
