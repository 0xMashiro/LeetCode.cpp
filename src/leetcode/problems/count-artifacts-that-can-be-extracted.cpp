#include "leetcode/problems/count-artifacts-that-can-be-extracted.h"

namespace leetcode {
namespace problem_2201 {

// 哈希集合法：记录所有被挖掘的格子，然后检查每个文物
// 时间复杂度: O(|dig| + |artifacts| * 每个文物的格子数)
// 空间复杂度: O(|dig|)
static int solution1(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
  // 记录所有被挖掘的格子，编码为 r * n + c
  unordered_set<long long> dug;
  for (const auto& d : dig) {
    long long key = static_cast<long long>(d[0]) * n + d[1];
    dug.insert(key);
  }

  int count = 0;
  for (const auto& art : artifacts) {
    int r1 = art[0], c1 = art[1], r2 = art[2], c2 = art[3];
    bool canExtract = true;
    // 检查该文物覆盖的所有格子是否都被挖掘
    for (int r = r1; r <= r2 && canExtract; ++r) {
      for (int c = c1; c <= c2; ++c) {
        long long key = static_cast<long long>(r) * n + c;
        if (dug.find(key) == dug.end()) {
          canExtract = false;
          break;
        }
      }
    }
    if (canExtract) {
      ++count;
    }
  }
  return count;
}

CountArtifactsThatCanBeExtractedSolution::CountArtifactsThatCanBeExtractedSolution() {
  setMetaInfo({.id = 2201,
               .title = "Count Artifacts That Can Be Extracted",
               .url = "https://leetcode.com/problems/count-artifacts-that-can-be-extracted/"});
  registerStrategy("Hash Set", solution1);
}

int CountArtifactsThatCanBeExtractedSolution::digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
  return getSolution()(n, artifacts, dig);
}

}  // namespace problem_2201
}  // namespace leetcode
