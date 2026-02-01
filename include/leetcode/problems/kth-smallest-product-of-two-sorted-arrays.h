#include "leetcode/core.h"

namespace leetcode {
namespace problem_2040 {

using Func = std::function<long long(vector<int>&, vector<int>&, long long)>;

class KthSmallestProductOfTwoSortedArraysSolution : public SolutionBase<Func> {
 public:
  //! 2040. Kth Smallest Product of Two Sorted Arrays
  //! https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/
  long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2,
                               long long k);

  KthSmallestProductOfTwoSortedArraysSolution();
};

}  // namespace problem_2040
}  // namespace leetcode
