#include "leetcode/problems/maximize-happiness-of-selected-children.h"

namespace leetcode {
namespace problem_3075 {

// 策略1：排序贪心（降序排序）
// 时间复杂度: O(n log n), 空间复杂度: O(1)
static long long solution1(vector<int>& happiness, int k) {
  // 降序排序
  sort(happiness.begin(), happiness.end(), greater<int>());
  long long ans = 0;
  for (int i = 0; i < k; ++i) {
    // 由于数组已降序，当当前值小于等于 i 时，后续值都会小于等于 i
    // 因为 happiness[i] <= i 且 happiness 非递增，i 递增
    if (happiness[i] <= i) break;
    ans += happiness[i] - i;
  }
  return ans;
}

// 策略2：使用最大堆（优先队列）
// 时间复杂度: O(n + k log n), 空间复杂度: O(n)
static long long solution2(vector<int>& happiness, int k) {
  // 建立最大堆
  priority_queue<int> pq;
  for (int h : happiness) {
    pq.push(h);
  }
  long long ans = 0;
  for (int i = 0; i < k; ++i) {
    if (pq.empty()) break;
    int val = pq.top();
    pq.pop();
    int actual = val - i;
    if (actual <= 0) break;  // 后续值也会 <= 0
    ans += actual;
  }
  return ans;
}

// 策略3：排序贪心（升序排序，从后往前取）
// 时间复杂度: O(n log n), 空间复杂度: O(1)
static long long solution3(vector<int>& happiness, int k) {
  // 升序排序
  sort(happiness.begin(), happiness.end());
  long long ans = 0;
  int n = happiness.size();
  for (int i = 0; i < k; ++i) {
    // 从后往前取第 i 大的元素，下标为 n-1-i
    int idx = n - 1 - i;
    // 实际贡献为 happiness[idx] - i，但不能为负
    if (happiness[idx] <= i) break;
    ans += happiness[idx] - i;
  }
  return ans;
}

MaximizeHappinessOfSelectedChildrenSolution::MaximizeHappinessOfSelectedChildrenSolution() {
  setMetaInfo({.id = 3075,
               .title = "Maximize Happiness of Selected Children",
               .url = "https://leetcode.com/problems/maximize-happiness-of-selected-children/"});
  registerStrategy({.name = "Sort Descending"}, solution1);
  registerStrategy({.name = "Max Heap"}, solution2);
  registerStrategy({.name = "Sort Ascending"}, solution3);
}

long long MaximizeHappinessOfSelectedChildrenSolution::maximumHappinessSum(vector<int>& happiness, int k) {
  return getSolution()(happiness, k);
}

}  // namespace problem_3075
}  // namespace leetcode