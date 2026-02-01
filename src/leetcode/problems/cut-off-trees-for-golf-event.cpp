#include "leetcode/problems/cut-off-trees-for-golf-event.h"

namespace leetcode {
namespace problem_675 {

// BFS 计算从起点到终点的最短距离
static int bfs(vector<vector<int>> &forest, int sx, int sy, int ex, int ey) {
  if (sx == ex && sy == ey) return 0;

  int m = forest.size();
  int n = forest[0].size();

  const int dx[4] = {-1, 1, 0, 0};
  const int dy[4] = {0, 0, -1, 1};

  vector<vector<bool>> visited(m, vector<bool>(n, false));
  queue<pair<int, int>> q;

  q.push({sx, sy});
  visited[sx][sy] = true;
  int steps = 0;

  while (!q.empty()) {
    int size = q.size();
    steps++;
    for (int i = 0; i < size; ++i) {
      auto [x, y] = q.front();
      q.pop();

      for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
        if (forest[nx][ny] == 0) continue;
        if (visited[nx][ny]) continue;

        if (nx == ex && ny == ey) return steps;

        visited[nx][ny] = true;
        q.push({nx, ny});
      }
    }
  }

  return -1;  // 无法到达
}

static int solution1(vector<vector<int>> &forest) {
  int m = forest.size();
  int n = forest[0].size();

  // 如果起点被阻塞，直接返回 -1
  if (forest[0][0] == 0) return -1;

  // 收集所有树的位置
  vector<tuple<int, int, int>> trees;  // (height, x, y)
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (forest[i][j] > 1) {
        trees.push_back({forest[i][j], i, j});
      }
    }
  }

  // 按高度排序
  sort(trees.begin(), trees.end());

  // 从起点开始，依次砍每棵树
  int totalSteps = 0;
  int curX = 0, curY = 0;

  for (auto &[h, tx, ty] : trees) {
    int steps = bfs(forest, curX, curY, tx, ty);
    if (steps == -1) return -1;  // 无法到达这棵树

    totalSteps += steps;
    curX = tx;
    curY = ty;
    // 砍树后变成空地
    forest[curX][curY] = 1;
  }

  return totalSteps;
}

CutOffTreesForGolfEventSolution::CutOffTreesForGolfEventSolution() {
  setMetaInfo({.id = 675,
               .title = "Cut Off Trees for Golf Event",
               .url = "https://leetcode.com/problems/cut-off-trees-for-golf-event/"});
  registerStrategy("BFS", solution1);
}

int CutOffTreesForGolfEventSolution::cutOffTree(vector<vector<int>> &forest) {
  return getSolution()(forest);
}

}  // namespace problem_675
}  // namespace leetcode
