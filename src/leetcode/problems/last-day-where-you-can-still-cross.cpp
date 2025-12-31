#include "leetcode/problems/last-day-where-you-can-still-cross.h"

namespace leetcode {
namespace problem_1970 {

// 策略1：二分查找 + BFS
static bool canCrossBFS(int row, int col, vector<vector<int>>& cells, int day) {
    vector<vector<bool>> water(row, vector<bool>(col, false));
    for (int i = 0; i < day; ++i) {
        int r = cells[i][0] - 1;
        int c = cells[i][1] - 1;
        water[r][c] = true;
    }
    // BFS
    vector<vector<bool>> visited(row, vector<bool>(col, false));
    queue<pair<int, int>> q;
    // 第一行所有陆地入队
    for (int c = 0; c < col; ++c) {
        if (!water[0][c]) {
            q.push({0, c});
            visited[0][c] = true;
        }
    }
    const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        if (r == row - 1) return true;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dirs[d][0];
            int nc = c + dirs[d][1];
            if (nr >= 0 && nr < row && nc >= 0 && nc < col && !water[nr][nc] && !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    return false;
}

static int solution1(int row, int col, vector<vector<int>>& cells) {
    int left = 0, right = cells.size();  // 注意：right 是最大天数（前 right 天）
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        if (canCrossBFS(row, col, cells, mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

// 策略2：二分查找 + 并查集
class DSU {
public:
    vector<int> parent, size;
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (size[rx] < size[ry]) swap(rx, ry);
        parent[ry] = rx;
        size[rx] += size[ry];
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

static bool canCrossDSU(int row, int col, vector<vector<int>>& cells, int day) {
    vector<vector<bool>> water(row, vector<bool>(col, false));
    for (int i = 0; i < day; ++i) {
        int r = cells[i][0] - 1;
        int c = cells[i][1] - 1;
        water[r][c] = true;
    }
    int total = row * col;
    DSU dsu(total + 2);
    int top = total, bottom = total + 1;
    // 连接第一行和最后一行
    for (int c = 0; c < col; ++c) {
        if (!water[0][c]) dsu.unite(top, 0 * col + c);
        if (!water[row - 1][c]) dsu.unite(bottom, (row - 1) * col + c);
    }
    // 遍历所有陆地单元格，连接相邻陆地（只检查下方和右方，避免重复）
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            if (water[r][c]) continue;
            int id = r * col + c;
            if (r + 1 < row && !water[r + 1][c]) dsu.unite(id, (r + 1) * col + c);
            if (c + 1 < col && !water[r][c + 1]) dsu.unite(id, r * col + c + 1);
        }
    }
    return dsu.connected(top, bottom);
}

static int solution2(int row, int col, vector<vector<int>>& cells) {
    int left = 0, right = cells.size();
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        if (canCrossDSU(row, col, cells, mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

LastDayWhereYouCanStillCrossSolution::LastDayWhereYouCanStillCrossSolution() {
    setMetaInfo({.id = 1970,
                 .title = "Last Day Where You Can Still Cross",
                 .url = "https://leetcode.com/problems/last-day-where-you-can-still-cross"});
    registerStrategy("Binary Search + BFS", solution1);
    registerStrategy("Binary Search + Union Find", solution2);
}

int LastDayWhereYouCanStillCrossSolution::latestDayToCross(int row, int col, vector<vector<int>>& cells) {
    return getSolution()(row, col, cells);
}

}  // namespace problem_1970
}  // namespace leetcode