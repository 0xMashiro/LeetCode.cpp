#include "leetcode/problems/jump-game-ix.h"

namespace leetcode {
namespace problem_3660 {

// 逆序图连通分量解法
//
// 跳跃规则定义了一个无向图：i < j 时，i 和 j 之间有边当且仅当 nums[i] > nums[j]
// （因为：从 i 右跳到 j 需要 nums[j] < nums[i]；从 j 左跳到 i 需要 nums[i] > nums[j]）
//
// 因此从 i 出发能到达的最大值 = i 所在连通分量中的最大值。
// 连通分量可以通过从左到右的单调栈合并得到：
// 相邻的两个区间 [l1,r1] 和 [l2,r2] (r1 < l2) 合并当且仅当 max([l1,r1]) > min([l2,r2])。
//
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution1(vector<int>& nums) {
  const int n = nums.size();

  // 栈中每个元素代表一个连通分量：{min_val, max_val, start_idx}
  // 分量的右边界由下一个分量的 start_idx 或 n 确定
  struct Component {
    int min_val;
    int max_val;
    int start;
  };
  vector<Component> comps;
  comps.reserve(n);

  for (int i = 0; i < n; ++i) {
    int v = nums[i];
    int cur_min = v;
    int cur_max = v;
    int cur_start = i;

    // 合并条件：左边分量的最大值 > 当前分量的最小值
    while (!comps.empty() && comps.back().max_val > cur_min) {
      cur_min = min(cur_min, comps.back().min_val);
      cur_max = max(cur_max, comps.back().max_val);
      cur_start = comps.back().start;
      comps.pop_back();
    }

    comps.push_back({cur_min, cur_max, cur_start});
  }

  vector<int> ans(n);
  for (int ci = 0; ci < (int)comps.size(); ++ci) {
    int start = comps[ci].start;
    int end = (ci + 1 < (int)comps.size()) ? comps[ci + 1].start : n;
    int comp_max = comps[ci].max_val;
    for (int j = start; j < end; ++j) {
      ans[j] = comp_max;
    }
  }

  return ans;
}

JumpGameIxSolution::JumpGameIxSolution() {
  setMetaInfo({.id = 3660,
               .title = "Jump Game IX",
               .url = "https://leetcode.com/problems/jump-game-ix"});
  // 本题结构唯一合理解为 O(n) 扫描连通分量，无明显多解
  registerStrategy({.name = "Connected Components"}, solution1);
}

vector<int> JumpGameIxSolution::maxValue(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3660
}  // namespace leetcode
