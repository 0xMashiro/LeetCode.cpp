#include "leetcode/problems/find-all-people-with-secret.h"

namespace leetcode {
namespace problem_2092 {

// 方法1：按时间分组 + BFS
// 时间复杂度: O(m log m + m * α(n))，其中 m 是会议数量
// 空间复杂度: O(n + m)
static vector<int> solution1(int n, vector<vector<int>>& meetings,
                             int firstPerson) {
  // 按时间对会议进行排序和分组
  sort(meetings.begin(), meetings.end(),
       [](const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; });

  // 初始化知道秘密的人
  vector<bool> knowsSecret(n, false);
  knowsSecret[0] = true;
  knowsSecret[firstPerson] = true;

  // 按时间处理会议
  int m = meetings.size();
  for (int i = 0; i < m;) {
    int currentTime = meetings[i][2];

    // 收集当前时间的所有会议
    unordered_map<int, vector<int>> graph;
    while (i < m && meetings[i][2] == currentTime) {
      int x = meetings[i][0];
      int y = meetings[i][1];
      graph[x].push_back(y);
      graph[y].push_back(x);
      i++;
    }

    // 使用 BFS 传播秘密
    queue<int> q;
    unordered_set<int> visited;

    // 将所有当前知道秘密的人加入队列
    for (const auto& [person, neighbors] : graph) {
      if (knowsSecret[person] && !visited.count(person)) {
        q.push(person);
        visited.insert(person);
      }
    }

    // BFS 传播
    while (!q.empty()) {
      int current = q.front();
      q.pop();

      for (int neighbor : graph[current]) {
        if (!visited.count(neighbor)) {
          visited.insert(neighbor);
          knowsSecret[neighbor] = true;
          q.push(neighbor);
        }
      }
    }

    // 对于当前时间处理过的人，如果不知道秘密，需要重置他们的连接状态
    // 因为他们在下一个时间点需要重新建立连接
    // 这里我们不需要显式重置，因为 graph 是每个时间点重新构建的
  }

  // 收集所有知道秘密的人
  vector<int> result;
  for (int i = 0; i < n; i++) {
    if (knowsSecret[i]) {
      result.push_back(i);
    }
  }
  return result;
}

// 方法2：按时间分组 + 并查集
// 时间复杂度: O(m log m + m * α(n))
// 空间复杂度: O(n + m)
static vector<int> solution2(int n, vector<vector<int>>& meetings,
                             int firstPerson) {
  // 按时间对会议进行排序和分组
  sort(meetings.begin(), meetings.end(),
       [](const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; });

  // 初始化并查集
  vector<int> parent(n);
  iota(parent.begin(), parent.end(), 0);

  // 初始化知道秘密的人
  vector<bool> knowsSecret(n, false);
  knowsSecret[0] = true;
  knowsSecret[firstPerson] = true;

  // 并查集查找函数
  function<int(int)> find = [&](int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  };

  // 按时间处理会议
  int m = meetings.size();
  for (int i = 0; i < m;) {
    int currentTime = meetings[i][2];

    // 收集当前时间的所有会议
    vector<pair<int, int>> edges;
    unordered_set<int> participants;

    while (i < m && meetings[i][2] == currentTime) {
      int x = meetings[i][0];
      int y = meetings[i][1];
      edges.emplace_back(x, y);
      participants.insert(x);
      participants.insert(y);
      i++;
    }

    // 为当前时间的参与者建立连接
    for (const auto& [x, y] : edges) {
      int rootX = find(x);
      int rootY = find(y);
      if (rootX != rootY) {
        parent[rootY] = rootX;
      }
    }

    // 传播秘密：如果某个连通分量中有人知道秘密，那么整个连通分量都知道
    unordered_map<int, bool> componentHasSecret;
    for (int person : participants) {
      int root = find(person);
      if (knowsSecret[person]) {
        componentHasSecret[root] = true;
      }
    }

    // 标记所有知道秘密的连通分量
    for (int person : participants) {
      int root = find(person);
      if (componentHasSecret[root]) {
        knowsSecret[person] = true;
      }
    }

    // 重置当前时间参与者的并查集状态（为下一个时间点做准备）
    for (int person : participants) {
      parent[person] = person;
    }
  }

  // 收集所有知道秘密的人
  vector<int> result;
  for (int i = 0; i < n; i++) {
    if (knowsSecret[i]) {
      result.push_back(i);
    }
  }
  return result;
}

// 方法3：优化的 BFS 方法
// 时间复杂度: O(m log m + m)
// 空间复杂度: O(n + m)
static vector<int> solution3(int n, vector<vector<int>>& meetings,
                             int firstPerson) {
  // 按时间对会议进行排序和分组
  sort(meetings.begin(), meetings.end(),
       [](const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; });

  // 构建时间到会议的映射
  vector<vector<pair<int, int>>> timeMeetings;
  int m = meetings.size();

  for (int i = 0; i < m;) {
    int currentTime = meetings[i][2];
    unordered_map<int, vector<int>> graph;

    while (i < m && meetings[i][2] == currentTime) {
      int x = meetings[i][0];
      int y = meetings[i][1];
      graph[x].push_back(y);
      graph[y].push_back(x);
      i++;
    }

    // 存储当前时间的图
    vector<pair<int, int>> edges;
    for (const auto& [person, neighbors] : graph) {
      for (int neighbor : neighbors) {
        if (person < neighbor) {  // 避免重复
          edges.emplace_back(person, neighbor);
        }
      }
    }
    timeMeetings.push_back(edges);
  }

  // 初始化知道秘密的人
  vector<bool> knowsSecret(n, false);
  knowsSecret[0] = true;
  knowsSecret[firstPerson] = true;

  // 按时间处理
  for (const auto& edges : timeMeetings) {
    // 构建当前时间的图
    unordered_map<int, vector<int>> graph;
    unordered_set<int> participants;

    for (const auto& [x, y] : edges) {
      graph[x].push_back(y);
      graph[y].push_back(x);
      participants.insert(x);
      participants.insert(y);
    }

    // BFS 传播秘密
    queue<int> q;
    unordered_set<int> visited;

    // 将所有当前知道秘密的参与者加入队列
    for (int person : participants) {
      if (knowsSecret[person] && !visited.count(person)) {
        q.push(person);
        visited.insert(person);
      }
    }

    // BFS
    while (!q.empty()) {
      int current = q.front();
      q.pop();

      for (int neighbor : graph[current]) {
        if (!visited.count(neighbor)) {
          visited.insert(neighbor);
          knowsSecret[neighbor] = true;
          q.push(neighbor);
        }
      }
    }
  }

  // 收集结果
  vector<int> result;
  for (int i = 0; i < n; i++) {
    if (knowsSecret[i]) {
      result.push_back(i);
    }
  }
  return result;
}

FindAllPeopleWithSecretSolution::FindAllPeopleWithSecretSolution() {
  setMetaInfo(
      {.id = 2092,
       .title = "Find All People With Secret",
       .url = "https://leetcode.com/problems/find-all-people-with-secret/"});
  registerStrategy({.name = "Time Grouping + BFS"}, solution1);
  registerStrategy({.name = "Time Grouping + Union Find"}, solution2);
  registerStrategy({.name = "Optimized BFS"}, solution3);
}

vector<int> FindAllPeopleWithSecretSolution::findAllPeople(
    int n, vector<vector<int>>& meetings, int firstPerson) {
  return getSolution()(n, meetings, firstPerson);
}

}  // namespace problem_2092
}  // namespace leetcode