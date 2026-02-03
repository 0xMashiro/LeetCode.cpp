#include "leetcode/problems/keys-and-rooms.h"

namespace leetcode {
namespace problem_841 {

// BFS 解法
// 时间复杂度: O(n + k)，其中 k 是钥匙总数
// 空间复杂度: O(n)
static bool solutionBFS(vector<vector<int>>& rooms) {
  int n = rooms.size();
  vector<bool> visited(n, false);
  queue<int> q;
  
  // 从房间 0 开始
  visited[0] = true;
  q.push(0);
  
  while (!q.empty()) {
    int room = q.front();
    q.pop();
    
    // 遍历当前房间中的所有钥匙
    for (int key : rooms[room]) {
      if (!visited[key]) {
        visited[key] = true;
        q.push(key);
      }
    }
  }
  
  // 检查是否所有房间都被访问
  for (bool v : visited) {
    if (!v) return false;
  }
  return true;
}

// DFS 解法
// 时间复杂度: O(n + k)，其中 k 是钥匙总数
// 空间复杂度: O(n)
static void dfs(vector<vector<int>>& rooms, vector<bool>& visited, int room) {
  visited[room] = true;
  for (int key : rooms[room]) {
    if (!visited[key]) {
      dfs(rooms, visited, key);
    }
  }
}

static bool solutionDFS(vector<vector<int>>& rooms) {
  int n = rooms.size();
  vector<bool> visited(n, false);
  dfs(rooms, visited, 0);
  
  // 检查是否所有房间都被访问
  for (bool v : visited) {
    if (!v) return false;
  }
  return true;
}

KeysAndRoomsSolution::KeysAndRoomsSolution() {
  setMetaInfo({.id = 841,
               .title = "Keys and Rooms",
               .url = "https://leetcode.com/problems/keys-and-rooms/"});
  registerStrategy("BFS", solutionBFS);
  registerStrategy("DFS", solutionDFS);
}

bool KeysAndRoomsSolution::canVisitAllRooms(vector<vector<int>>& rooms) {
  return getSolution()(rooms);
}

}  // namespace problem_841
}  // namespace leetcode
