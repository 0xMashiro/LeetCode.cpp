#include "leetcode/problems/course-schedule-ii.h"

namespace leetcode {
namespace problem_210 {

// Kahn 算法（BFS 拓扑排序）
// 时间复杂度: O(V + E), 空间复杂度: O(V + E)
// V = numCourses, E = prerequisites.length
static vector<int> solution1(int numCourses, vector<vector<int>>& prerequisites) {
  // 构建邻接表和入度数组
  vector<vector<int>> adj(numCourses);  // 邻接表
  vector<int> inDegree(numCourses, 0);   // 入度数组
  
  for (const auto& pre : prerequisites) {
    int a = pre[0];  // 课程 a
    int b = pre[1];  // 先修课程 b
    adj[b].push_back(a);  // 边 b -> a
    inDegree[a]++;        // a 的入度加 1
  }
  
  // BFS：将所有入度为 0 的节点加入队列
  queue<int> q;
  for (int i = 0; i < numCourses; ++i) {
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }
  
  vector<int> result;
  result.reserve(numCourses);
  
  while (!q.empty()) {
    int course = q.front();
    q.pop();
    result.push_back(course);
    
    // 移除该课程，更新其后继课程的入度
    for (int next : adj[course]) {
      inDegree[next]--;
      if (inDegree[next] == 0) {
        q.push(next);
      }
    }
  }
  
  // 如果结果数量等于课程总数，说明可以完成所有课程
  return result.size() == numCourses ? result : vector<int>();
}

// DFS 拓扑排序
// 时间复杂度: O(V + E), 空间复杂度: O(V + E)
static vector<int> solution2(int numCourses, vector<vector<int>>& prerequisites) {
  // 构建邻接表
  vector<vector<int>> adj(numCourses);
  for (const auto& pre : prerequisites) {
    adj[pre[1]].push_back(pre[0]);
  }
  
  // 0: 未访问, 1: 正在访问(在递归栈中), 2: 已访问完成
  vector<int> state(numCourses, 0);
  vector<int> result;
  result.reserve(numCourses);
  
  function<bool(int)> dfs = [&](int course) -> bool {
    if (state[course] == 1) return false;  // 发现环
    if (state[course] == 2) return true;   // 已处理过
    
    state[course] = 1;  // 标记为正在访问
    
    for (int next : adj[course]) {
      if (!dfs(next)) return false;
    }
    
    state[course] = 2;  // 标记为已完成
    result.push_back(course);  // 后序遍历加入结果
    return true;
  };
  
  for (int i = 0; i < numCourses; ++i) {
    if (state[i] == 0) {
      if (!dfs(i)) return {};
    }
  }
  
  // DFS 得到的是逆拓扑序，需要反转
  reverse(result.begin(), result.end());
  return result;
}

CourseScheduleIiSolution::CourseScheduleIiSolution() {
  setMetaInfo({.id = 210,
               .title = "Course Schedule II",
               .url = "https://leetcode.com/problems/course-schedule-ii/"});
  registerStrategy("Kahn BFS", solution1);
  registerStrategy("DFS Post-order", solution2);
}

vector<int> CourseScheduleIiSolution::findOrder(int numCourses, vector<vector<int>>& prerequisites) {
  return getSolution()(numCourses, prerequisites);
}

}  // namespace problem_210
}  // namespace leetcode
