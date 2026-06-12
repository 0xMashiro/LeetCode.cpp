#include "leetcode/problems/minimum-number-of-operations-to-make-elements-in-array-distinct.h"
#include <unordered_set>

namespace leetcode {
namespace problem_3396 {

static int solution1(vector<int>& nums) {
  unordered_set<int> seen;
  int n = nums.size();
  // Traverse from right to left to find the first duplicate
  for (int i = n - 1; i >= 0; --i) {
    if (seen.count(nums[i])) {
      // Found a duplicate at index i, need to remove elements up to index i
      // Each operation removes 3 elements, so we need ceil((i+1)/3) operations
      return (i + 1 + 2) / 3;  // ceil division
    }
    seen.insert(nums[i]);
  }
  // No duplicates found
  return 0;
}

MinimumNumberOfOperationsToMakeElementsInArrayDistinctSolution::MinimumNumberOfOperationsToMakeElementsInArrayDistinctSolution() {
  setMetaInfo({
      .id = 3396,
      .title = "Minimum Number of Operations to Make Elements in Array Distinct",
      .url = "https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct"
  });
  registerStrategy({.name = "Brute Force"}, solution1);
}

int MinimumNumberOfOperationsToMakeElementsInArrayDistinctSolution::minimumOperations(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3396
}  // namespace leetcode
