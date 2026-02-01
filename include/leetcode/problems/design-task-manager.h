#include "leetcode/core.h"

namespace leetcode {
namespace problem_3408 {

/**
 * Task Manager 实现
 * 思路：使用 set 维护有序的任务集合，按 priority 降序、taskId 降序排列
 * 配合 unordered_map 实现 O(1) 查找任务
 * - set 存储 tuple<priority, taskId, userId>
 * - unordered_map<taskId, set<...>::iterator> 存储任务位置
 * 时间复杂度：add/edit/rmv/execTop 均为 O(log n)
 * 空间复杂度：O(n)
 */
class TaskManager {
 public:
  TaskManager(vector<vector<int>>& tasks);

  void add(int userId, int taskId, int priority);

  void edit(int taskId, int newPriority);

  void rmv(int taskId);

  int execTop();

 private:
  // 存储 {priority, taskId, userId}，按 priority 降序、taskId 降序
  using Task = tuple<int, int, int>;
  struct TaskCompare {
    bool operator()(const Task& a, const Task& b) const {
      if (get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b);  // priority 降序
      return get<1>(a) > get<1>(b);  // taskId 降序
    }
  };
  
  set<Task, TaskCompare> tasks_;
  // taskId -> {userId, priority}
  unordered_map<int, pair<int, int>> taskInfo_;
};

}  // namespace problem_3408
}  // namespace leetcode