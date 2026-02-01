
#include "leetcode/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii.h"

namespace leetcode {
namespace problem_3298 {

/**
 * Sliding Window Solution
 * 
 * For each left endpoint l, find the minimum right endpoint r such that
 * word1[l:r] contains all characters in word2 with sufficient counts.
 * Then all substrings word1[l:r'], where r' >= r, are also valid.
 * 
 * Time Complexity: O(n), where n = word1.length
 * Space Complexity: O(1) - fixed size array of 26 characters
 */
static long long solution1(const string& word1, const string& word2) {
  const int n = word1.size();
  const int m = word2.size();
  
  // If word2 is longer than word1, no valid substring exists
  if (m > n) return 0;
  
  // Count required characters in word2
  int need[26] = {0};
  for (char c : word2) {
    need[c - 'a']++;
  }
  
  // Count how many distinct characters we need to satisfy
  int requiredTypes = 0;
  for (int i = 0; i < 26; i++) {
    if (need[i] > 0) requiredTypes++;
  }
  
  long long result = 0;
  int count[26] = {0};  // Count of characters in current window
  int satisfied = 0;    // Number of character types that meet the requirement
  int r = 0;            // Right pointer
  
  // For each left endpoint
  for (int l = 0; l < n; l++) {
    // Extend right pointer until window is valid or reach end
    while (r < n && satisfied < requiredTypes) {
      int idx = word1[r] - 'a';
      count[idx]++;
      // If this character is needed and we just met the requirement
      if (need[idx] > 0 && count[idx] == need[idx]) {
        satisfied++;
      }
      r++;
    }
    
    // If window is valid, all substrings starting at l with length >= (r-l) are valid
    if (satisfied == requiredTypes) {
      result += n - r + 1;
    }
    
    // Shrink window from left
    int idx = word1[l] - 'a';
    // If this character is needed and we're about to break the requirement
    if (need[idx] > 0 && count[idx] == need[idx]) {
      satisfied--;
    }
    count[idx]--;
  }
  
  return result;
}

CountSubstringsThatCanBeRearrangedToContainAStringIiSolution::CountSubstringsThatCanBeRearrangedToContainAStringIiSolution() {
  setMetaInfo({.id = 3298,
               .title = "Count Substrings That Can Be Rearranged to Contain a String II",
               .url = "https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/"});
  registerStrategy("Sliding Window", solution1);
}

long long CountSubstringsThatCanBeRearrangedToContainAStringIiSolution::validSubstringCount(
    const string& word1, const string& word2) {
  return getSolution()(word1, word2);
}

}  // namespace problem_3298
}  // namespace leetcode
