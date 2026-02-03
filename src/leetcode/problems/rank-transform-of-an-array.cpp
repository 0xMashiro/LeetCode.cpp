#include "leetcode/problems/rank-transform-of-an-array.h"

namespace leetcode {
namespace problem_1331 {

// 排序 + 哈希表
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static vector<int> solution1(vector<int>& arr) {
  const int n = arr.size();
  if (n == 0) return {};
  
  // 复制并排序
  vector<int> sorted = arr;
  sort(sorted.begin(), sorted.end());
  
  // 建立值到排名的映射（去重）
  unordered_map<int, int> rankMap;
  int rank = 1;
  for (int num : sorted) {
    if (rankMap.find(num) == rankMap.end()) {
      rankMap[num] = rank++;
    }
  }
  
  // 构建结果
  vector<int> result;
  result.reserve(n);
  for (int num : arr) {
    result.push_back(rankMap[num]);
  }
  
  return result;
}

RankTransformOfAnArraySolution::RankTransformOfAnArraySolution() {
  setMetaInfo({.id = 1331,
               .title = "Rank Transform of an Array",
               .url = "https://leetcode.com/problems/rank-transform-of-an-array/"});
  registerStrategy("Sorting + HashMap", solution1);
}

vector<int> RankTransformOfAnArraySolution::arrayRankTransform(vector<int>& arr) {
  return getSolution()(arr);
}

}  // namespace problem_1331
}  // namespace leetcode