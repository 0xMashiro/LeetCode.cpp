#include "leetcode/problems/maximum-sum-of-edge-values-in-a-graph.h"

namespace leetcode {
namespace problem_3547 {

// =============================================================
// 策略 1：贪心构造（Deque 交替法）
//
// 思路：图是路径或环。将值 1..n 从大到小排序，用双端队列
//       交替从左右放入（最大的放中间），使大值与大值相邻，
//       小值与小值相邻，从而最大化边权乘积和。
//
// 时间复杂度: O(n log n), 空间复杂度: O(n)
// =============================================================
static long long solution1(int n, vector<vector<int>>& edges) {
  // 1. 计算度，确定图类型
  vector<int> degree(n, 0);
  for (auto& e : edges) {
    degree[e[0]]++;
    degree[e[1]]++;
  }

  // 2. 判断是路径还是环
  bool isPath = false;
  for (int d : degree) {
    if (d == 1) {
      isPath = true;
      break;
    }
  }
  // isPath=false ⇒ 所有节点度=2 ⇒ 环

  // 3. 从大到小排序 1..n
  vector<int> values(n);
  iota(values.begin(), values.end(), 1);
  sort(values.rbegin(), values.rend());  // n, n-1, ..., 1

  // 4. 用 deque 交替左右构造最优排列
  deque<int> dq;
  for (int v : values) {
    if (dq.empty()) {
      dq.push_back(v);
    } else {
      // 奇数次 push_front, 偶数次 push_back → 大值聚中间
      if (dq.size() % 2 == 1) {
        dq.push_front(v);
      } else {
        dq.push_back(v);
      }
    }
  }

  // 5. 计算边权和
  vector<int> arr(dq.begin(), dq.end());
  long long sum = 0;
  for (int i = 0; i < n - 1; ++i) {
    sum += (long long)arr[i] * arr[i + 1];
  }

  // 环：加上首尾边
  if (!isPath) {
    sum += (long long)arr[0] * arr[n - 1];
  }

  return sum;
}

// =============================================================
// 策略 2：奇偶分组公式法
//
// 思路：观察 deque 构造的结果，最优排列等价于：
//       所有奇数升序 + 所有偶数降序。
//       直接构造该排列并计算边和，免去 deque 操作。
//
// 时间复杂度: O(n log n), 空间复杂度: O(n)
// =============================================================
static long long solution2(int n, vector<vector<int>>& edges) {
  // 1. 计算度，确定图类型
  vector<int> degree(n, 0);
  for (auto& e : edges) {
    degree[e[0]]++;
    degree[e[1]]++;
  }

  bool isPath = false;
  for (int d : degree) {
    if (d == 1) {
      isPath = true;
      break;
    }
  }

  // 2. 构造奇偶分组排列
  //    排列 = [所有奇数升序] + [所有偶数降序]
  vector<int> arr;
  arr.reserve(n);

  // 所有奇数升序: 1, 3, 5, ...
  for (int v = 1; v <= n; v += 2) {
    arr.push_back(v);
  }
  // 所有偶数降序: (n 或 n-1 的偶数), ..., 6, 4, 2
  int start = (n % 2 == 0) ? n : n - 1;
  for (int v = start; v >= 2; v -= 2) {
    arr.push_back(v);
  }

  // 3. 计算边权和
  long long sum = 0;
  for (int i = 0; i < n - 1; ++i) {
    sum += (long long)arr[i] * arr[i + 1];
  }

  // 环：加上首尾边
  if (!isPath) {
    sum += (long long)arr[0] * arr[n - 1];
  }

  return sum;
}

MaximumSumOfEdgeValuesInAGraphSolution::MaximumSumOfEdgeValuesInAGraphSolution() {
  setMetaInfo({.id = 3547,
               .title = "Maximum Sum of Edge Values in a Graph",
               .url = "https://leetcode.com/problems/maximum-sum-of-edge-values-in-a-graph/"});
  registerStrategy("Deque Greedy Construction", solution1);
  registerStrategy("Parity Grouping Formula", solution2);
}

long long MaximumSumOfEdgeValuesInAGraphSolution::maxScore(int n, vector<vector<int>>& edges) {
  return getSolution()(n, edges);
}

}  // namespace problem_3547
}  // namespace leetcode
