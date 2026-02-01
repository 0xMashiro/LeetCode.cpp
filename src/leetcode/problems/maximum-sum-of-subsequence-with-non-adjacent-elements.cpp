#include "leetcode/problems/maximum-sum-of-subsequence-with-non-adjacent-elements.h"

namespace leetcode {
namespace problem_3165 {

constexpr int MOD = 1e9 + 7;

// 线段树节点：存储 2x2 矩阵
// mat[i][j] 表示区间左端点状态为 i (0=不选,1=选)，右端点状态为 j 时的最大和
struct SegNode {
  long long mat[2][2];
  SegNode() {
    mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
  }
};

class SegmentTree {
 public:
  SegmentTree(const vector<int>& nums) {
    n = nums.size();
    tree.resize(4 * n);
    build(1, 0, n - 1, nums);
  }

  void update(int pos, int val) {
    update(1, 0, n - 1, pos, val);
  }

  SegNode query() {
    return tree[1];
  }

 private:
  int n;
  vector<SegNode> tree;

  // 合并两个子节点
  // 左子节点 [l,mid]，右子节点 [mid+1,r]
  // 合并时需要考虑 mid 和 mid+1 位置的状态关系
  SegNode merge(const SegNode& left, const SegNode& right) {
    SegNode res;
    // 初始化矩阵为极小值
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        res.mat[i][j] = -(1LL << 60);
      }
    }
    // 枚举合并点的状态：左子树的右端点状态和右子树的左端点状态
    for (int i = 0; i < 2; i++) {      // 左子树左端点状态
      for (int j = 0; j < 2; j++) {    // 左子树右端点状态（即合并点左侧）
        for (int k = 0; k < 2; k++) {  // 右子树左端点状态（即合并点右侧）
          for (int l = 0; l < 2; l++) { // 右子树右端点状态
            // 如果合并点两侧都选，则冲突，跳过
            if (j == 1 && k == 1) continue;
            res.mat[i][l] = max(res.mat[i][l], left.mat[i][j] + right.mat[k][l]);
          }
        }
      }
    }
    return res;
  }

  // 根据单个元素构建叶子节点
  SegNode buildLeaf(int val) {
    SegNode node;
    // mat[i][j] 表示区间左边界外状态为i，右边界外状态为j时的最大和
    // 对于单元素区间 [p,p]，左右边界是同一个位置
    // mat[0][0]: 不选这个元素 -> 0
    // mat[1][1]: 选这个元素 -> val
    // mat[0][1] 和 mat[1][0]: 不可能（边界状态矛盾）-> -inf
    const long long NEG_INF = -(1LL << 60);
    node.mat[0][0] = 0;
    node.mat[0][1] = NEG_INF;
    node.mat[1][0] = NEG_INF;
    node.mat[1][1] = val;
    return node;
  }

  void build(int node_idx, int l, int r, const vector<int>& nums) {
    if (l == r) {
      tree[node_idx] = buildLeaf(nums[l]);
      return;
    }
    int mid = l + (r - l) / 2;
    build(node_idx * 2, l, mid, nums);
    build(node_idx * 2 + 1, mid + 1, r, nums);
    tree[node_idx] = merge(tree[node_idx * 2], tree[node_idx * 2 + 1]);
  }

  void update(int node_idx, int l, int r, int pos, int val) {
    if (l == r) {
      tree[node_idx] = buildLeaf(val);
      return;
    }
    int mid = l + (r - l) / 2;
    if (pos <= mid) {
      update(node_idx * 2, l, mid, pos, val);
    } else {
      update(node_idx * 2 + 1, mid + 1, r, pos, val);
    }
    tree[node_idx] = merge(tree[node_idx * 2], tree[node_idx * 2 + 1]);
  }
};

static int solution(vector<int>& nums, vector<vector<int>>& queries) {
  int n = nums.size();
  SegmentTree seg(nums);
  long long ans = 0;

  for (const auto& q : queries) {
    int pos = q[0];
    int x = q[1];
    seg.update(pos, x);
    SegNode root = seg.query();
    long long maxSum = 0;
    // 取所有状态的最大值
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        maxSum = max(maxSum, root.mat[i][j]);
      }
    }
    ans = (ans + maxSum) % MOD;
  }

  return (int)ans;
}

MaximumSumOfSubsequenceWithNonAdjacentElementsSolution::MaximumSumOfSubsequenceWithNonAdjacentElementsSolution() {
  setMetaInfo({
    .id = 3165,
    .title = "Maximum Sum of Subsequence With Non-adjacent Elements",
    .url = "https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/"
  });
  registerStrategy("Segment Tree", solution);
}

int MaximumSumOfSubsequenceWithNonAdjacentElementsSolution::maximumSumSubsequence(
    vector<int>& nums, vector<vector<int>>& queries) {
  return getSolution()(nums, queries);
}

}  // namespace problem_3165
}  // namespace leetcode
