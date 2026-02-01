#include "leetcode/problems/total-score-of-dungeon-runs.h"

namespace leetcode {
namespace problem_3771 {

// 树状数组（Fenwick Tree）
class FenwickTree {
 public:
  FenwickTree(int n) : n_(n), tree_(n + 1, 0) {}

  // 在位置 i 增加 delta（i 是 1-indexed）
  void add(int i, long long delta) {
    for (; i <= n_; i += i & -i) {
      tree_[i] += delta;
    }
  }

  // 查询前缀和 [1..i]
  long long query(int i) const {
    long long sum = 0;
    for (; i > 0; i -= i & -i) {
      sum += tree_[i];
    }
    return sum;
  }

  // 查询 [l..r] 的和
  long long query(int l, int r) const {
    if (l > r) return 0;
    return query(r) - query(l - 1);
  }

 private:
  int n_;
  vector<long long> tree_;
};

// 树状数组 + 离散化
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static long long solution(int hp, vector<int>& damage, vector<int>& requirement) {
  int n = damage.size();
  
  // 计算前缀和 prefix[i] = damage[0] + ... + damage[i-1]
  vector<long long> prefix(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    prefix[i] = prefix[i - 1] + damage[i - 1];
  }
  
  // 离散化：需要离散化 prefix[0..n-1]
  vector<long long> sorted;
  sorted.reserve(n);
  for (int i = 0; i < n; ++i) {
    sorted.push_back(prefix[i]);
  }
  sort(sorted.begin(), sorted.end());
  sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
  
  auto getId = [&](long long x) -> int {
    return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin() + 1;  // 1-indexed
  };
  
  FenwickTree ft(sorted.size());
  
  // 先加入 prefix[0]
  ft.add(getId(prefix[0]), 1);
  
  long long ans = 0;
  
  for (int k = 1; k <= n; ++k) {
    // 计算 need = prefix[k] + requirement[k-1] - hp
    long long need = prefix[k] + requirement[k - 1] - hp;
    
    // 找满足 prefix[i] >= need 的个数 (i 从 0 到 k-1)
    // 即找 sorted 中 >= need 的元素个数
    auto it = lower_bound(sorted.begin(), sorted.end(), need);
    if (it != sorted.end()) {
      int pos = it - sorted.begin() + 1;  // 1-indexed
      // 查询 [pos, sorted.size()] 的和
      ans += ft.query(pos, sorted.size());
    }
    // 如果 it == sorted.end()，说明所有 prefix 都 < need，贡献为 0
    
    // 将 prefix[k] 加入树状数组（为后续的 k+1 做准备）
    if (k < n) {
      ft.add(getId(prefix[k]), 1);
    }
  }
  
  return ans;
}

TotalScoreOfDungeonRunsSolution::TotalScoreOfDungeonRunsSolution() {
  setMetaInfo({.id = 3771,
               .title = "Total Score of Dungeon Runs",
               .url = "https://leetcode.com/problems/total-score-of-dungeon-runs/"});
  registerStrategy("Fenwick Tree", solution);
}

long long TotalScoreOfDungeonRunsSolution::totalScore(int hp, vector<int>& damage, vector<int>& requirement) {
  return getSolution()(hp, damage, requirement);
}

}  // namespace problem_3771
}  // namespace leetcode
