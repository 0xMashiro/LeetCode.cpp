#include "leetcode/problems/earliest-finish-time-for-land-and-water-rides-ii.h"

namespace leetcode {
namespace problem_3635 {

// ============================================================
// Solution 1: Brute Force — 枚举所有 (i,j) 对 + 两种顺序
// 时间复杂度: O(n*m), 空间复杂度: O(1)
// 对于 n,m ≤ 5*10^4, 最坏 2.5×10^9 次操作, 一定会 TLE
// 仅用于教学演示
// ============================================================
static int solution1(vector<int>& landStartTime, vector<int>& landDuration,
                     vector<int>& waterStartTime, vector<int>& waterDuration) {
  const int n = landStartTime.size();
  const int m = waterStartTime.size();
  int ans = INT_MAX;
  for (int i = 0; i < n; ++i) {
    int landEnd = landStartTime[i] + landDuration[i];
    for (int j = 0; j < m; ++j) {
      int waterEnd = waterStartTime[j] + waterDuration[j];
      // Case 1: land first -> water second
      int finish1 = max(landEnd, waterStartTime[j]) + waterDuration[j];
      // Case 2: water first -> land second
      int finish2 = max(waterEnd, landStartTime[i]) + landDuration[i];
      ans = min({ans, finish1, finish2});
    }
  }
  return ans;
}

// ============================================================
// Solution 2: Greedy + Binary Search  O((n+m) log (n+m))
//
// 核心观察：
// 对于"陆->水"顺序, 选陆地设施 i, 设 t = ls[i] + ld[i] 为陆地完成时间。
// 对水上设施 j, 完成时间 = max(t, ws[j]) + wd[j]
//   - 若 ws[j] ≤ t:  完成 = t + wd[j]  → 选 wd 最小的
//   - 若 ws[j] > t:  完成 = ws[j] + wd[j] → 选 ws+wd 最小的
// 对 ws 排序后, 预计算前缀最小 wd 和后缀最小 ws+wd, 二分查找分界点 O(log m)。
// "水->陆"顺序同理。
// ============================================================
static int solution2(vector<int>& landStartTime, vector<int>& landDuration,
                     vector<int>& waterStartTime, vector<int>& waterDuration) {
  const int n = landStartTime.size();
  const int m = waterStartTime.size();

  auto solveOneDirection = [](const vector<int>& startA, const vector<int>& durA,
                               const vector<int>& startB, const vector<int>& durB) -> int {
    // A -> B: pick one from A first, then one from B
    // Returns min finish time for this direction
    const int na = startA.size();
    const int nb = startB.size();
    if (na == 0 || nb == 0) return INT_MAX;

    // Build array of (startB, durB) sorted by startB
    vector<pair<int, int>> bSorted(nb);
    for (int j = 0; j < nb; ++j) {
      bSorted[j] = {startB[j], durB[j]};
    }
    sort(bSorted.begin(), bSorted.end());

    // Prefix min of durB
    vector<int> prefixMinDurB(nb);
    prefixMinDurB[0] = bSorted[0].second;
    for (int j = 1; j < nb; ++j) {
      prefixMinDurB[j] = min(prefixMinDurB[j - 1], bSorted[j].second);
    }

    // Suffix min of (startB + durB)
    vector<int> suffixMinSumB(nb);
    suffixMinSumB[nb - 1] = bSorted[nb - 1].first + bSorted[nb - 1].second;
    for (int j = nb - 2; j >= 0; --j) {
      suffixMinSumB[j] = min(suffixMinSumB[j + 1], bSorted[j].first + bSorted[j].second);
    }

    auto extractWs = [&](int idx) { return bSorted[idx].first; };

    int best = INT_MAX;
    for (int i = 0; i < na; ++i) {
      int t = startA[i] + durA[i];  // finish time of ride A

      // Binary search for the last B with startB <= t
      // upper_bound returns first > t, so we want index = pos - 1
      auto it = upper_bound(bSorted.begin(), bSorted.end(), make_pair(t, INT_MAX));
      int pos = it - bSorted.begin();  // first index with startB > t

      // Case: B rides with startB <= t: value = t + durB, minimize durB
      if (pos > 0) {
        best = min(best, t + prefixMinDurB[pos - 1]);
      }

      // Case: B rides with startB > t: value = startB + durB
      if (pos < nb) {
        best = min(best, suffixMinSumB[pos]);
      }
    }
    return best;
  };

  // Direction 1: Land -> Water
  int ans1 = solveOneDirection(landStartTime, landDuration, waterStartTime, waterDuration);
  // Direction 2: Water -> Land
  int ans2 = solveOneDirection(waterStartTime, waterDuration, landStartTime, landDuration);

  return min(ans1, ans2);
}

EarliestFinishTimeForLandAndWaterRidesIiSolution::EarliestFinishTimeForLandAndWaterRidesIiSolution() {
  setMetaInfo({.id = 3635,
               .title = "Earliest Finish Time for Land and Water Rides II",
               .url = "https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-ii/"});
  registerStrategy({.name = "Brute Force", .expected = "TLE"}, solution1);
  registerStrategy({.name = "Greedy + Binary Search"}, solution2);
}

int EarliestFinishTimeForLandAndWaterRidesIiSolution::earliestFinishTime(
    vector<int>& landStartTime, vector<int>& landDuration,
    vector<int>& waterStartTime, vector<int>& waterDuration) {
  return getSolution()(landStartTime, landDuration, waterStartTime, waterDuration);
}

}  // namespace problem_3635
}  // namespace leetcode
