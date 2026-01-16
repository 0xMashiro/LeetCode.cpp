#include "leetcode/problems/maximum-square-area-by-removing-fences-from-a-field.h"

namespace leetcode {
namespace problem_2975 {

static int solution1(int m, int n, vector<int>& hFences, vector<int>& vFences) {
  const long long MOD = 1e9 + 7;
  
  // Collect all vertical positions (columns) including boundaries
  vector<int> vert = vFences;
  vert.push_back(1);
  vert.push_back(n);
  sort(vert.begin(), vert.end());
  vert.erase(unique(vert.begin(), vert.end()), vert.end());
  
  // Collect all horizontal positions (rows) including boundaries
  vector<int> horiz = hFences;
  horiz.push_back(1);
  horiz.push_back(m);
  sort(horiz.begin(), horiz.end());
  horiz.erase(unique(horiz.begin(), horiz.end()), horiz.end());
  
  // Compute all possible vertical distances
  unordered_set<int> vDiffs;
  for (size_t i = 0; i < vert.size(); ++i) {
    for (size_t j = i + 1; j < vert.size(); ++j) {
      vDiffs.insert(vert[j] - vert[i]);
    }
  }
  
  // Compute all possible horizontal distances
  unordered_set<int> hDiffs;
  for (size_t i = 0; i < horiz.size(); ++i) {
    for (size_t j = i + 1; j < horiz.size(); ++j) {
      hDiffs.insert(horiz[j] - horiz[i]);
    }
  }
  
  // Find the maximum common length
  int maxLen = 0;
  for (int diff : vDiffs) {
    if (hDiffs.count(diff)) {
      maxLen = max(maxLen, diff);
    }
  }
  
  if (maxLen == 0) return -1;
  return static_cast<int>((static_cast<long long>(maxLen) * maxLen) % MOD);
}

MaximumSquareAreaByRemovingFencesFromAFieldSolution::MaximumSquareAreaByRemovingFencesFromAFieldSolution() {
  setMetaInfo({.id = 2975,
               .title = "Maximum Square Area by Removing Fences From a Field",
               .url = "https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/"});
  registerStrategy("Set Intersection", solution1);
}

int MaximumSquareAreaByRemovingFencesFromAFieldSolution::maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
  return getSolution()(m, n, hFences, vFences);
}

}  // namespace problem_2975
}  // namespace leetcode