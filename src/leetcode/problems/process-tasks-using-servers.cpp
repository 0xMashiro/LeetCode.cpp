#include "leetcode/problems/process-tasks-using-servers.h"

namespace leetcode {
namespace problem_1882 {

// 使用两个优先队列的贪心算法
// 时间复杂度: O((n+m) * log(n)), 空间复杂度: O(n)
static vector<int> solution1(vector<int>& servers, vector<int>& tasks) {
  const int n = servers.size();
  const int m = tasks.size();
  
  // available: 可用服务器，按 (weight, index) 排序
  // 小顶堆：weight 小的优先，weight 相同则 index 小的优先
  using AvailableServer = pair<int, int>;  // (weight, index)
  priority_queue<AvailableServer, vector<AvailableServer>, greater<AvailableServer>> available;
  
  // busy: 忙碌服务器，按 (release_time, weight, index) 排序
  // 小顶堆：释放时间早的优先
  using BusyServer = pair<long long, AvailableServer>;  // (release_time, (weight, index))
  priority_queue<BusyServer, vector<BusyServer>, greater<BusyServer>> busy;
  
  // 初始化：所有服务器都可用
  for (int i = 0; i < n; ++i) {
    available.push({servers[i], i});
  }
  
  vector<int> ans(m);
  long long currentTime = 0;
  
  for (int j = 0; j < m; ++j) {
    currentTime = max(currentTime, (long long)j);  // 当前时间至少为 j
    
    // 将所有已经释放的服务器从 busy 移到 available
    while (!busy.empty() && busy.top().first <= currentTime) {
      auto [releaseTime, serverInfo] = busy.top();
      busy.pop();
      available.push(serverInfo);
    }
    
    // 如果没有可用服务器，需要等待最早释放的服务器
    if (available.empty()) {
      // 取出最早释放的服务器
      auto [releaseTime, serverInfo] = busy.top();
      busy.pop();
      currentTime = releaseTime;  // 快进到该服务器释放的时间
      available.push(serverInfo);
      
      // 继续检查是否有其他服务器也释放了
      while (!busy.empty() && busy.top().first <= currentTime) {
        auto [rt, si] = busy.top();
        busy.pop();
        available.push(si);
      }
    }
    
    // 现在一定有可用服务器，取出 weight 最小的
    auto [weight, idx] = available.top();
    available.pop();
    
    ans[j] = idx;
    
    // 该服务器将在 currentTime + tasks[j] 后释放
    long long releaseTime = currentTime + tasks[j];
    busy.push({releaseTime, {weight, idx}});
  }
  
  return ans;
}

ProcessTasksUsingServersSolution::ProcessTasksUsingServersSolution() {
  setMetaInfo({.id = 1882,
               .title = "Process Tasks Using Servers",
               .url = "https://leetcode.com/problems/process-tasks-using-servers/"});
  registerStrategy("Two Priority Queues", solution1);
}

vector<int> ProcessTasksUsingServersSolution::assignTasks(vector<int>& servers, vector<int>& tasks) {
  return getSolution()(servers, tasks);
}

}  // namespace problem_1882
}  // namespace leetcode
