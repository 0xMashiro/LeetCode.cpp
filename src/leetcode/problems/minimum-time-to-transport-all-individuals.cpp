#include "leetcode/problems/minimum-time-to-transport-all-individuals.h"

namespace leetcode {
namespace problem_3594 {

// Dijkstra 状态图最短路径
// 状态：(mask, side, stage)
//   mask: 已到达目的地的人员位掩码 (0..2^n-1)
//   side: 船的位置 (0=基地, 1=目的地)
//   stage: 当前环境阶段 (0..m-1)
// 状态空间: 2^n * 2 * m ≤ 4096 * 2 * 5 = 40960
// 转移:
//   side=0: 选非空子集 S(≤k人) 从基地→目的地 → 过河时间 + 阶段推进
//   side=1: 选1人从目的地→基地(若还有人未过河) → 返回时间 + 阶段推进
// 终止: mask=ALL 且 side=1
//
// 时间复杂度: O(2^n * (2^n + n) * log(2^n * m))
// 空间复杂度: O(2^n * m)
static double solution1(int n, int k, int m, vector<int>& time, vector<double>& mul) {
    const int ALL = (1 << n) - 1;
    const double INF = numeric_limits<double>::max();
    const double EPS = 1e-12;

    // dist[mask][side][stage]
    vector<vector<vector<double>>> dist(
        1 << n, vector<vector<double>>(2, vector<double>(m, INF)));

    // 预计算所有子集的 popcount
    vector<int> popcnt(1 << n, 0);
    for (int s = 1; s < (1 << n); ++s) {
        popcnt[s] = popcnt[s >> 1] + (s & 1);
    }

    // 预计算所有子集的最大 time 值
    vector<double> subset_max(1 << n, 0.0);
    for (int s = 1; s < (1 << n); ++s) {
        double mx = 0.0;
        for (int i = 0; i < n; ++i) {
            if (s & (1 << i)) mx = max(mx, (double)time[i]);
        }
        subset_max[s] = mx;
    }

    // 最小堆: (当前时间, mask, side, stage)
    using State = tuple<double, int, int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[0][0][0] = 0.0;
    pq.push({0.0, 0, 0, 0});

    while (!pq.empty()) {
        auto [cur_time, mask, side, stage] = pq.top();
        pq.pop();

        // 跳过已过时的状态
        if (cur_time > dist[mask][side][stage] + EPS) continue;

        // 全部到达目的地且船已到目的地 → 成功
        if (mask == ALL && side == 1) {
            return cur_time;
        }

        if (side == 0) {
            // === 船在基地：选择一批人过河（向前） ===
            int avail = ALL & ~mask;  // 还在基地的人
            for (int sub = avail; sub; sub = (sub - 1) & avail) {
                if (popcnt[sub] > k) continue;

                double crossing = subset_max[sub] * mul[stage];
                int floor_time = (int)floor(crossing + 1e-9);
                int ns = (stage + floor_time) % m;
                int nmask = mask | sub;
                double new_time = cur_time + crossing;

                if (new_time < dist[nmask][1][ns] - EPS) {
                    dist[nmask][1][ns] = new_time;
                    pq.push({new_time, nmask, 1, ns});
                }
            }
        } else {
            // === 船在目的地：若还有人没过来，选一人返回 ===
            if (mask == ALL) continue;  // 所有人都到了，无需返回

            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    double return_t = (double)time[i] * mul[stage];
                    int floor_time = (int)floor(return_t + 1e-9);
                    int ns = (stage + floor_time) % m;
                    int nmask = mask & ~(1 << i);
                    double new_time = cur_time + return_t;

                    if (new_time < dist[nmask][0][ns] - EPS) {
                        dist[nmask][0][ns] = new_time;
                        pq.push({new_time, nmask, 0, ns});
                    }
                }
            }
        }
    }

    // 不可达
    return -1.0;
}

MinimumTimeToTransportAllIndividualsSolution::
    MinimumTimeToTransportAllIndividualsSolution() {
    setMetaInfo(
        {.id = 3594,
         .title = "Minimum Time to Transport All Individuals",
         .url = "https://leetcode.com/problems/"
                "minimum-time-to-transport-all-individuals/"});
    // 本题结构唯一合理解为 Dijkstra 状态图最短路，无明显多解
    registerStrategy({.name = "Dijkstra State DP"}, solution1);
}

double MinimumTimeToTransportAllIndividualsSolution::minTime(
    int n, int k, int m, vector<int>& time, vector<double>& mul) {
    return getSolution()(n, k, m, time, mul);
}

}  // namespace problem_3594
}  // namespace leetcode
