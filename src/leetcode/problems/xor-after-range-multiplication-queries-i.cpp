#include "leetcode/problems/xor-after-range-multiplication-queries-i.h"

namespace leetcode {
namespace problem_3653 {

static const int MOD = 1000000007;

// 直接模拟：按顺序处理每个查询
// 时间复杂度: O(q * n/k)，最坏 O(q * n) = 10^6
// 空间复杂度: O(1)
static int solution1(vector<int>& nums, vector<vector<int>>& queries) {
  // 处理每个查询
  for (const auto& query : queries) {
    int l = query[0];
    int r = query[1];
    int k = query[2];
    int v = query[3];
    
    // 从 l 开始，步长为 k，更新到 r
    for (int idx = l; idx <= r; idx += k) {
      nums[idx] = (static_cast<long long>(nums[idx]) * v) % MOD;
    }
  }
  
  // 计算所有元素的 XOR
  int result = 0;
  for (int num : nums) {
    result ^= num;
  }
  
  return result;
}

XorAfterRangeMultiplicationQueriesISolution::XorAfterRangeMultiplicationQueriesISolution() {
  setMetaInfo({
    .id = 3653,
    .title = "XOR After Range Multiplication Queries I",
    .url = "https://leetcode.com/problems/xor-after-range-multiplication-queries-i/"
  });
  registerStrategy("Direct Simulation", solution1);
}

int XorAfterRangeMultiplicationQueriesISolution::xorAfterQueries(
    vector<int>& nums, vector<vector<int>>& queries) {
  return getSolution()(nums, queries);
}

}  // namespace problem_3653
}  // namespace leetcode
