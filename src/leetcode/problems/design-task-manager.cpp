#include "leetcode/problems/design-task-manager.h"

namespace leetcode {
namespace problem_3408 {

TaskManager::TaskManager(vector<vector<int>>& tasks) {
  for (const auto& task : tasks) {
    int userId = task[0];
    int taskId = task[1];
    int priority = task[2];
    tasks_.insert({priority, taskId, userId});
    taskInfo_[taskId] = {userId, priority};
  }
}

void TaskManager::add(int userId, int taskId, int priority) {
  tasks_.insert({priority, taskId, userId});
  taskInfo_[taskId] = {userId, priority};
}

void TaskManager::edit(int taskId, int newPriority) {
  auto it = taskInfo_.find(taskId);
  int userId = it->second.first;
  int oldPriority = it->second.second;
  
  // 删除旧任务
  tasks_.erase({oldPriority, taskId, userId});
  
  // 插入新任务
  tasks_.insert({newPriority, taskId, userId});
  
  // 更新映射
  taskInfo_[taskId] = {userId, newPriority};
}

void TaskManager::rmv(int taskId) {
  auto it = taskInfo_.find(taskId);
  int userId = it->second.first;
  int priority = it->second.second;
  
  tasks_.erase({priority, taskId, userId});
  taskInfo_.erase(taskId);
}

int TaskManager::execTop() {
  if (tasks_.empty()) {
    return -1;
  }
  
  const auto& top = *tasks_.begin();
  int priority = get<0>(top);
  int taskId = get<1>(top);
  int userId = get<2>(top);
  
  tasks_.erase(tasks_.begin());
  taskInfo_.erase(taskId);
  
  return userId;
}

}  // namespace problem_3408
}  // namespace leetcode