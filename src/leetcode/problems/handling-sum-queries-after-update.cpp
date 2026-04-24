#include "leetcode/problems/handling-sum-queries-after-update.h"

namespace leetcode {
namespace problem_2569 {

// 本题结构唯一合理解为线段树 + 懒标记区间翻转，无明显多解
//
// 核心思路：
//   - 用线段树维护 nums1 的区间翻转（type 1）和总 1 的个数查询
//   - 类型 2 查询：sum2 += p * totalOnes(nums1)
//   - 类型 3 查询：直接返回 sum2
// 时间复杂度：O((n + q) * log n)，空间复杂度：O(n)

class SegTree {
 private:
  int n_;
  vector<int> cnt_;     // 节点区间内 1 的个数
  vector<bool> lazy_;   // 懒标记：是否需要翻转

  void build(const vector<int>& arr, int node, int l, int r) {
    if (l == r) {
      cnt_[node] = arr[l];
      return;
    }
    int mid = (l + r) / 2;
    build(arr, node * 2, l, mid);
    build(arr, node * 2 + 1, mid + 1, r);
    cnt_[node] = cnt_[node * 2] + cnt_[node * 2 + 1];
  }

  // 对节点 node 代表的区间 [l, r] 应用翻转
  void apply(int node, int l, int r) {
    cnt_[node] = (r - l + 1) - cnt_[node];
    lazy_[node] = !lazy_[node];
  }

  // 下推懒标记
  void push(int node, int l, int r) {
    if (!lazy_[node]) return;
    int mid = (l + r) / 2;
    apply(node * 2, l, mid);
    apply(node * 2 + 1, mid + 1, r);
    lazy_[node] = false;
  }

  void rangeFlip(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
      apply(node, l, r);
      return;
    }
    push(node, l, r);
    int mid = (l + r) / 2;
    rangeFlip(node * 2, l, mid, ql, qr);
    rangeFlip(node * 2 + 1, mid + 1, r, ql, qr);
    cnt_[node] = cnt_[node * 2] + cnt_[node * 2 + 1];
  }

 public:
  explicit SegTree(const vector<int>& arr) : n_(arr.size()) {
    if (n_ == 0) return;
    cnt_.resize(4 * n_);
    lazy_.resize(4 * n_, false);
    build(arr, 1, 0, n_ - 1);
  }

  void flipRange(int l, int r) {
    if (l > r || n_ == 0) return;
    rangeFlip(1, 0, n_ - 1, l, r);
  }

  int totalOnes() const { return n_ > 0 ? cnt_[1] : 0; }
};

static vector<long long> solution1(vector<int>& nums1, vector<int>& nums2,
                                    vector<vector<int>>& queries) {
  const int n = nums1.size();
  long long sum2 = 0;
  for (int x : nums2) sum2 += x;

  SegTree seg(nums1);
  vector<long long> ans;
  ans.reserve(queries.size());

  for (auto& q : queries) {
    const int type = q[0];
    if (type == 1) {
      seg.flipRange(q[1], q[2]);
    } else if (type == 2) {
      sum2 += static_cast<long long>(seg.totalOnes()) * q[1];
    } else {  // type == 3
      ans.push_back(sum2);
    }
  }
  return ans;
}

HandlingSumQueriesAfterUpdateSolution::HandlingSumQueriesAfterUpdateSolution() {
  setMetaInfo({.id = 2569,
               .title = "Handling Sum Queries After Update",
               .url = "https://leetcode.com/problems/handling-sum-queries-after-update/"});
  registerStrategy("Segment Tree With Lazy Propagation", solution1);
}

vector<long long> HandlingSumQueriesAfterUpdateSolution::handleQuery(
    vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
  return getSolution()(nums1, nums2, queries);
}

}  // namespace problem_2569
}  // namespace leetcode
