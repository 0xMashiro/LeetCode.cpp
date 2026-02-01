#include "leetcode/problems/escape-a-large-maze.h"

namespace leetcode {
namespace problem_1036 {

class Solution {
 public:
  bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source,
                        vector<int>& target) {
    // 将 blocked 转换为 hash set 以便快速查找
    unordered_set<long long> blockedSet;
    for (const auto& b : blocked) {
      blockedSet.insert(encode(b[0], b[1]));
    }

    // 从 source 出发 BFS，检查能否到达 target 或突破包围
    // 从 target 出发 BFS，检查能否到达 source 或突破包围
    // 如果两者都能突破包围（或相遇），则返回 true
    return bfs(source, target, blockedSet) && bfs(target, source, blockedSet);
  }

 private:
  // 编码坐标为 long long，用于 hash set
  long long encode(int x, int y) {
    return ((long long)x << 32) | (unsigned int)y;
  }

  // BFS 搜索，maxSteps 限制搜索步数
  // 如果能到达终点，或搜索了超过 maxSteps 个格子，返回 true
  bool bfs(vector<int>& start, vector<int>& end,
           unordered_set<long long>& blocked) {
    const int MAX_BLOCKED = 200;
    // 200 个阻挡最多能围住约 200*199/2 = 19900 个格子
    // 取 200*200 = 40000 作为上限足够安全
    const int MAX_VISITED = MAX_BLOCKED * MAX_BLOCKED;
    const int GRID_SIZE = 1000000;

    // 四个方向
    const int dx[4] = {0, 0, 1, -1};
    const int dy[4] = {1, -1, 0, 0};

    unordered_set<long long> visited;
    queue<pair<int, int>> q;

    q.push({start[0], start[1]});
    visited.insert(encode(start[0], start[1]));

    while (!q.empty() && visited.size() <= MAX_VISITED) {
      auto [x, y] = q.front();
      q.pop();

      // 检查是否到达终点
      if (x == end[0] && y == end[1]) {
        return true;
      }

      // 尝试四个方向
      for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 检查边界
        if (nx < 0 || nx >= GRID_SIZE || ny < 0 || ny >= GRID_SIZE) {
          continue;
        }

        long long code = encode(nx, ny);

        // 检查是否被阻挡或已访问
        if (blocked.count(code) || visited.count(code)) {
          continue;
        }

        visited.insert(code);
        q.push({nx, ny});
      }
    }

    // 如果访问的格子数超过 MAX_VISITED，说明突破了包围
    return visited.size() > MAX_VISITED;
  }
};

// 包装函数，适配 SolutionBase 接口
static bool solution1(vector<vector<int>>& blocked, vector<int>& source,
                      vector<int>& target) {
  Solution sol;
  return sol.isEscapePossible(blocked, source, target);
}

EscapeALargeMazeSolution::EscapeALargeMazeSolution() {
  setMetaInfo({.id = 1036,
               .title = "Escape a Large Maze",
               .url = "https://leetcode.com/problems/escape-a-large-maze/"});
  registerStrategy("BFS with Bounded Search", solution1);
}

bool EscapeALargeMazeSolution::isEscapePossible(vector<vector<int>>& blocked,
                                                vector<int>& source,
                                                vector<int>& target) {
  return getSolution()(blocked, source, target);
}

}  // namespace problem_1036
}  // namespace leetcode
