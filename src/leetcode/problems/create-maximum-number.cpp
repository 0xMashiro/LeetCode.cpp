#include "leetcode/problems/create-maximum-number.h"

namespace leetcode {
namespace problem_321 {

// Helper: find the maximum subsequence of length `len` from nums (preserving order)
static vector<int> maxSubArray(const vector<int>& nums, int len) {
  vector<int> res;
  int n = nums.size();
  int drop = n - len;  // how many elements we can discard
  for (int i = 0; i < n; ++i) {
    while (!res.empty() && drop > 0 && res.back() < nums[i]) {
      res.pop_back();
      --drop;
    }
    res.push_back(nums[i]);
  }
  res.resize(len);
  return res;
}

// Helper: merge two subsequences into the largest possible result
static vector<int> merge(const vector<int>& a, const vector<int>& b) {
  vector<int> res;
  int i = 0, j = 0;
  int na = a.size(), nb = b.size();
  while (i < na && j < nb) {
    // Compare the remaining suffixes lexicographically
    if (lexicographical_compare(a.begin() + i, a.end(),
                                b.begin() + j, b.end())) {
      // b's suffix is larger, take from b
      res.push_back(b[j++]);
    } else {
      // a's suffix is larger or equal
      res.push_back(a[i++]);
    }
  }
  while (i < na) res.push_back(a[i++]);
  while (j < nb) res.push_back(b[j++]);
  return res;
}

static vector<int> solution1(vector<int>& nums1, vector<int>& nums2, int k) {
  int n1 = nums1.size(), n2 = nums2.size();
  vector<int> best;
  for (int i = max(0, k - n2); i <= min(k, n1); ++i) {
    vector<int> sub1 = maxSubArray(nums1, i);
    vector<int> sub2 = maxSubArray(nums2, k - i);
    vector<int> candidate = merge(sub1, sub2);
    if (candidate > best) {
      best = move(candidate);
    }
  }
  return best;
}

CreateMaximumNumberSolution::CreateMaximumNumberSolution() {
  setMetaInfo({
      .id = 321,
      .title = "Create Maximum Number",
      .url = "https://leetcode.com/problems/create-maximum-number"
  });
  registerStrategy("Brute Force", solution1);
}

vector<int> CreateMaximumNumberSolution::maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
  return getSolution()(nums1, nums2, k);
}

}  // namespace problem_321
}  // namespace leetcode
