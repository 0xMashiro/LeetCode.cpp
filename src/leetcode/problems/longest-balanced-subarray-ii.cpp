#include "leetcode/problems/longest-balanced-subarray-ii.h"

namespace leetcode {
namespace problem_3721 {

// 线段树，支持区间加和查找值为0的最小下标
class SegmentTree {
 public:
  SegmentTree(int n) : n(n) {
    minv.assign(4 * n, 0);
    maxv.assign(4 * n, 0);
    lazy.assign(4 * n, 0);
  }
  
  // 区间加
  void range_add(int l, int r, int val) {
    range_add(1, 0, n - 1, l, r, val);
  }
  
  // 查找值为0的最小下标，如果不存在返回-1
  int find_zero() {
    if (maxv[1] < 0 || minv[1] > 0) return -1;
    return find_zero(1, 0, n - 1);
  }
  
 private:
  int n;
  vector<int> minv, maxv, lazy;
  
  void push_down(int node) {
    if (lazy[node] != 0) {
      int v = lazy[node];
      minv[node * 2] += v;
      maxv[node * 2] += v;
      lazy[node * 2] += v;
      minv[node * 2 + 1] += v;
      maxv[node * 2 + 1] += v;
      lazy[node * 2 + 1] += v;
      lazy[node] = 0;
    }
  }
  
  void pull_up(int node) {
    minv[node] = min(minv[node * 2], minv[node * 2 + 1]);
    maxv[node] = max(maxv[node * 2], maxv[node * 2 + 1]);
  }
  
  void range_add(int node, int l, int r, int ql, int qr, int val) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
      minv[node] += val;
      maxv[node] += val;
      lazy[node] += val;
      return;
    }
    push_down(node);
    int mid = (l + r) / 2;
    range_add(node * 2, l, mid, ql, qr, val);
    range_add(node * 2 + 1, mid + 1, r, ql, qr, val);
    pull_up(node);
  }
  
  int find_zero(int node, int l, int r) {
    if (maxv[node] < 0 || minv[node] > 0) return -1;
    if (l == r) return l;
    push_down(node);
    int mid = (l + r) / 2;
    int res = find_zero(node * 2, l, mid);
    if (res != -1) return res;
    return find_zero(node * 2 + 1, mid + 1, r);
  }
};

// 核心算法实现
static int solve(vector<int>& nums) {
  const int n = nums.size();
  if (n < 2) return 0;
  
  // 需要维护 diff[0..n]，其中 diff[l] 表示子数组 [l, r-1] 的 even_count - odd_count
  // 线段树大小为 n+1（l 的范围是 0 到 n）
  SegmentTree st(n + 1);
  
  unordered_map<int, int> last_occurrence;
  int ans = 0;
  
  for (int r = 0; r < n; r++) {
    int val = nums[r];
    int last = -1;
    if (last_occurrence.count(val)) {
      last = last_occurrence[val];
    }
    
    // 在区间 [last+1, r] 上更新
    // 对于左边界 l 在这个区间内，val 是子数组 [l, r] 中的新 distinct 值
    int delta = (val % 2 == 0) ? 1 : -1;
    st.range_add(last + 1, r, delta);
    
    // 查找使 diff[l] = 0 的最小 l
    int l = st.find_zero();
    if (l != -1 && l <= r) {
      ans = max(ans, r - l + 1);
    }
    
    last_occurrence[val] = r;
  }
  
  return ans;
}

// LeetCode 兼容的 Solution 类实现
int Solution::longestBalanced(vector<int>& nums) {
  return solve(nums);
}

// SolutionBase 实现
static int solution1(vector<int>& nums) {
  return solve(nums);
}

LongestBalancedSubarrayIiSolution::LongestBalancedSubarrayIiSolution() {
  setMetaInfo({.id = 3721,
               .title = "Longest Balanced Subarray II",
               .url = "https://leetcode.com/problems/longest-balanced-subarray-ii/"});
  registerStrategy("Segment Tree", solution1);
}

int LongestBalancedSubarrayIiSolution::longestBalanced(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3721
}  // namespace leetcode
