#include "leetcode/problems/delete-greatest-value-in-each-row.h"

namespace leetcode {
namespace problem_2500 {

// 对每行排序后逐列取最大值
// 时间复杂度: O(m * n * log(n)), 空间复杂度: O(1)
static int solution1(vector<vector<int>>& grid) {
  int m = grid.size();
  if (m == 0) return 0;
  int n = grid[0].size();
  
  // 对每一行进行降序排序
  for (int i = 0; i < m; ++i) {
    sort(grid[i].rbegin(), grid[i].rend());
  }
  
  int answer = 0;
  // 逐列遍历，每列取最大值
  for (int j = 0; j < n; ++j) {
    int colMax = grid[0][j];
    for (int i = 1; i < m; ++i) {
      colMax = max(colMax, grid[i][j]);
    }
    answer += colMax;
  }
  
  return answer;
}

// 使用优先队列（大根堆）的版本
// 时间复杂度: O(m * n * log(n)), 空间复杂度: O(m * n)
static int solution2(vector<vector<int>>& grid) {
  int m = grid.size();
  if (m == 0) return 0;
  int n = grid[0].size();
  
  // 为每一行创建一个优先队列
  vector<priority_queue<int>> heaps(m);
  for (int i = 0; i < m; ++i) {
    for (int val : grid[i]) {
      heaps[i].push(val);
    }
  }
  
  int answer = 0;
  // 执行 n 次操作
  for (int j = 0; j < n; ++j) {
    int roundMax = 0;
    for (int i = 0; i < m; ++i) {
      roundMax = max(roundMax, heaps[i].top());
      heaps[i].pop();
    }
    answer += roundMax;
  }
  
  return answer;
}

DeleteGreatestValueInEachRowSolution::DeleteGreatestValueInEachRowSolution() {
  setMetaInfo({.id = 2500,
               .title = "Delete Greatest Value in Each Row",
               .url = "https://leetcode.com/problems/delete-greatest-value-in-each-row/"});
  registerStrategy("Sort Rows", solution1);
  registerStrategy("Priority Queue", solution2);
}

int DeleteGreatestValueInEachRowSolution::deleteGreatestValue(vector<vector<int>>& grid) {
  return getSolution()(grid);
}

}  // namespace problem_2500
}  // namespace leetcode
