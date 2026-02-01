#include "leetcode/core.h"

namespace leetcode {
namespace problem_992 {

using Func = std::function<int(vector<int>&, int)>;

/**
 * 992. Subarrays with K Different Integers
 * https://leetcode.com/problems/subarrays-with-k-different-integers/
 *
 * Given an integer array nums and an integer k, return the number of good
 * subarrays of nums.
 *
 * A good array is an array where the number of different integers in that
 * array is exactly k.
 */
class SubarraysWithKDifferentIntegersSolution : public SolutionBase<Func> {
 public:
  int subarraysWithKDistinct(vector<int>& nums, int k);

  SubarraysWithKDifferentIntegersSolution();
};

}  // namespace problem_992
}  // namespace leetcode
