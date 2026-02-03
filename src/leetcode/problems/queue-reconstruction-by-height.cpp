
#include "leetcode/problems/queue-reconstruction-by-height.h"

namespace leetcode {
namespace problem_406 {

/**
 * 贪心算法：先按身高降序排序，再按 k 值插入
 * 
 * 思路：
 * 1. 按身高降序排序（身高相同则按 k 升序）
 *    - 高的人先处理，因为矮的人不会影响高的人的 k 值
 *    - 身高相同时，k 值小的在前（因为前面需要更少的人）
 * 2. 依次将每个人插入到结果队列的 k 位置
 *    - 由于先插入高的人，后插入的矮的人对高的人的相对位置无影响
 * 
 * 时间复杂度: O(n log n + n^2) = O(n^2)，插入操作是 O(n)
 * 空间复杂度: O(n)，结果队列
 */
static vector<vector<int>> solution1(vector<vector<int>>& people) {
  // 按身高降序排序，身高相同则按 k 升序排序
  sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
    if (a[0] != b[0]) {
      return a[0] > b[0];  // 身高降序
    }
    return a[1] < b[1];  // k 值升序
  });

  vector<vector<int>> result;
  // 依次插入到 k 位置
  for (const auto& person : people) {
    result.insert(result.begin() + person[1], person);
  }

  return result;
}

QueueReconstructionByHeightSolution::QueueReconstructionByHeightSolution() {
  setMetaInfo({.id = 406,
               .title = "Queue Reconstruction by Height",
               .url = "https://leetcode.com/problems/queue-reconstruction-by-height/"});
  registerStrategy("Greedy Sort & Insert", solution1);
}

vector<vector<int>> QueueReconstructionByHeightSolution::reconstructQueue(vector<vector<int>>& people) {
  return getSolution()(people);
}

}  // namespace problem_406
}  // namespace leetcode
