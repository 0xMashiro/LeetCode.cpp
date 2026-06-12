#include "leetcode/problems/earliest-finish-time-for-land-and-water-rides-i.h"

namespace leetcode {
namespace problem_3633 {

// ---------------------------------------------------------------
// Solution 1: Brute Force — 枚举所有 (land, water) 对，尝试两个顺序
// 时间复杂度: O(n*m), 空间复杂度: O(1)
// n,m ≤ 100 → 最多 10,000 对，足够快
// ---------------------------------------------------------------
static int solution1(vector<int>& landStartTime, vector<int>& landDuration,
                     vector<int>& waterStartTime, vector<int>& waterDuration) {
  int n = (int)landStartTime.size(), m = (int)waterStartTime.size();
  int best = INT_MAX;
  for (int i = 0; i < n; ++i) {
    int landFinish = landStartTime[i] + landDuration[i];
    for (int j = 0; j < m; ++j) {
      // 陆 → 水
      int finish1 = max(landFinish, waterStartTime[j]) + waterDuration[j];
      // 水 → 陆
      int waterFinish = waterStartTime[j] + waterDuration[j];
      int finish2 = max(waterFinish, landStartTime[i]) + landDuration[i];
      best = min(best, min(finish1, finish2));
    }
  }
  return best;
}

// ---------------------------------------------------------------
// Solution 2: Sorting + Binary Search
// 将 second-category rides 按 start 排序，预计算前缀最小值（duration）
// 和后缀最小值（start+duration），对每个 first ride 二分查找最优 second。
// 时间复杂度: O((n+m) log(n+m)), 空间复杂度: O(n+m)
// 匹配官方标签：Sorting, Binary Search, Two Pointers, Greedy
// ---------------------------------------------------------------

// 辅助函数：给定 first ride 结束时间 firstFinish，
// 从已按 start 排序的 secondRides 中选出最优 follow-up 完成时间
static int bestFollowUp(int firstFinish,
                        const vector<pair<int,int>>& sortedSecond,
                        const vector<int>& prefMinDur,
                        const vector<int>& suffMinSum) {
  int m = (int)sortedSecond.size();
  // 二分查找第一个 start >= firstFinish 的位置
  int lo = 0, hi = m;
  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (sortedSecond[mid].first >= firstFinish)
      hi = mid;
    else
      lo = mid + 1;
  }
  int split = lo;  // [0, split) 是 start < firstFinish 的

  int best = INT_MAX;
  // 组 A：start < firstFinish，需等到 firstFinish 才开始
  if (split > 0) {
    best = min(best, firstFinish + prefMinDur[split - 1]);
  }
  // 组 B：start >= firstFinish，可立即开始 at start time
  if (split < m) {
    best = min(best, suffMinSum[split]);
  }
  return best;
}

static int solution2(vector<int>& landStartTime, vector<int>& landDuration,
                     vector<int>& waterStartTime, vector<int>& waterDuration) {
  int n = (int)landStartTime.size(), m = (int)waterStartTime.size();

  // 构建并排序 water rides
  vector<pair<int,int>> waterRides(m);
  for (int j = 0; j < m; ++j)
    waterRides[j] = {waterStartTime[j], waterDuration[j]};
  sort(waterRides.begin(), waterRides.end());

  // 构建并排序 land rides
  vector<pair<int,int>> landRides(n);
  for (int i = 0; i < n; ++i)
    landRides[i] = {landStartTime[i], landDuration[i]};
  sort(landRides.begin(), landRides.end());

  // 预计算 water rides 的前缀最小 duration 和后缀最小 (start+duration)
  vector<int> waterPrefMinDur(m), waterSuffMinSum(m);
  if (m > 0) {
    waterPrefMinDur[0] = waterRides[0].second;
    for (int k = 1; k < m; ++k)
      waterPrefMinDur[k] = min(waterPrefMinDur[k - 1], waterRides[k].second);
    waterSuffMinSum[m - 1] = waterRides[m - 1].first + waterRides[m - 1].second;
    for (int k = m - 2; k >= 0; --k)
      waterSuffMinSum[k] = min(waterSuffMinSum[k + 1],
                               waterRides[k].first + waterRides[k].second);
  }

  // 预计算 land rides 的前缀最小 duration 和后缀最小 (start+duration)
  vector<int> landPrefMinDur(n), landSuffMinSum(n);
  if (n > 0) {
    landPrefMinDur[0] = landRides[0].second;
    for (int k = 1; k < n; ++k)
      landPrefMinDur[k] = min(landPrefMinDur[k - 1], landRides[k].second);
    landSuffMinSum[n - 1] = landRides[n - 1].first + landRides[n - 1].second;
    for (int k = n - 2; k >= 0; --k)
      landSuffMinSum[k] = min(landSuffMinSum[k + 1],
                              landRides[k].first + landRides[k].second);
  }

  int best = INT_MAX;

  // 陆 → 水：每项陆上项目作为 first，从水上项目中选最优 follow-up
  for (int i = 0; i < n; ++i) {
    int landFinish = landStartTime[i] + landDuration[i];
    best = min(best, bestFollowUp(landFinish, waterRides,
                                  waterPrefMinDur, waterSuffMinSum));
  }

  // 水 → 陆：每项水上项目作为 first，从陆上项目中选最优 follow-up
  for (int j = 0; j < m; ++j) {
    int waterFinish = waterStartTime[j] + waterDuration[j];
    best = min(best, bestFollowUp(waterFinish, landRides,
                                  landPrefMinDur, landSuffMinSum));
  }

  return best;
}

// ---------------------------------------------------------------
// Constructor: 注册元数据与策略
// ---------------------------------------------------------------
EarliestFinishTimeForLandAndWaterRidesISolution::EarliestFinishTimeForLandAndWaterRidesISolution() {
  setMetaInfo({.id = 3633,
               .title = "Earliest Finish Time for Land and Water Rides I",
               .url = "https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-i/"});
  registerStrategy({.name = "Brute Force"}, solution1);
  registerStrategy({.name = "Sorting + Binary Search"}, solution2);
}

int EarliestFinishTimeForLandAndWaterRidesISolution::earliestFinishTime(
    vector<int>& landStartTime, vector<int>& landDuration,
    vector<int>& waterStartTime, vector<int>& waterDuration) {
  return getSolution()(landStartTime, landDuration, waterStartTime, waterDuration);
}

}  // namespace problem_3633
}  // namespace leetcode
