#include "leetcode/problems/design-task-manager.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3408 {

TEST(LeetCode, DesignTaskManagerTest) {
  // Example 1 from problem description
  vector<vector<int>> init = {{1, 101, 10}, {2, 102, 20}, {3, 103, 15}};
  TaskManager taskManager(init);
  
  taskManager.add(4, 104, 5);  // Adds task 104 with priority 5 for User 4
  taskManager.edit(102, 8);    // Updates priority of task 102 to 8
  EXPECT_EQ(taskManager.execTop(), 3);  // return 3. Executes task 103 for User 3
  taskManager.rmv(101);        // Removes task 101 from the system
  taskManager.add(5, 105, 15); // Adds task 105 with priority 15 for User 5
  EXPECT_EQ(taskManager.execTop(), 5);  // return 5. Executes task 105 for User 5
}

}  // namespace problem_3408
}  // namespace leetcode