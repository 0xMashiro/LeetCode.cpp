
#include "leetcode/problems/find-the-difference-of-two-arrays.h"

namespace leetcode {
namespace problem_2215 {

// 哈希集合方法
// 时间复杂度: O(n + m), 空间复杂度: O(n + m)
static vector<vector<int>> solution1(vector<int>& nums1, vector<int>& nums2) {
  unordered_set<int> set1(nums1.begin(), nums1.end());
  unordered_set<int> set2(nums2.begin(), nums2.end());
  
  vector<vector<int>> answer(2);
  
  // 在 set1 但不在 set2 中的元素
  for (int num : set1) {
    if (set2.find(num) == set2.end()) {
      answer[0].push_back(num);
    }
  }
  
  // 在 set2 但不在 set1 中的元素
  for (int num : set2) {
    if (set1.find(num) == set1.end()) {
      answer[1].push_back(num);
    }
  }
  
  return answer;
}

FindTheDifferenceOfTwoArraysSolution::FindTheDifferenceOfTwoArraysSolution() {
  setMetaInfo({.id = 2215,
               .title = "Find the Difference of Two Arrays",
               .url = "https://leetcode.com/problems/find-the-difference-of-two-arrays/"});
  registerStrategy("Hash Set", solution1);
}

vector<vector<int>> FindTheDifferenceOfTwoArraysSolution::findDifference(
    vector<int>& nums1, vector<int>& nums2) {
  return getSolution()(nums1, nums2);
}

}  // namespace problem_2215
}  // namespace leetcode
