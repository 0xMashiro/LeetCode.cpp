
#include "leetcode/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points.h"

namespace leetcode {
namespace problem_2058 {

// 单次遍历：找到所有临界点，计算最小和最大距离
// 时间复杂度: O(n), 空间复杂度: O(1)
static vector<int> solution1(ListNode* head) {
  if (!head || !head->next || !head->next->next) {
    return {-1, -1};
  }

  int index = 1;  // 当前节点位置（从1开始）
  int first_critical = -1;  // 第一个临界点位置
  int last_critical = -1;   // 最后一个临界点位置
  int min_dist = INT_MAX;   // 最小距离
  
  ListNode* prev = head;
  ListNode* curr = head->next;
  index = 2;  // curr 是第2个节点

  while (curr->next) {
    ListNode* next = curr->next;
    
    // 检查是否为临界点
    bool is_critical = (curr->val > prev->val && curr->val > next->val) ||
                       (curr->val < prev->val && curr->val < next->val);
    
    if (is_critical) {
      if (first_critical == -1) {
        first_critical = index;
      } else {
        // 更新最小距离（相邻临界点之间的距离）
        min_dist = min(min_dist, index - last_critical);
      }
      last_critical = index;
    }
    
    prev = curr;
    curr = next;
    ++index;
  }

  // 如果临界点少于2个
  if (first_critical == -1 || first_critical == last_critical) {
    return {-1, -1};
  }

  // 最大距离 = 最后一个临界点 - 第一个临界点
  int max_dist = last_critical - first_critical;

  return {min_dist, max_dist};
}

FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsSolution::FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsSolution() {
  setMetaInfo({.id = 2058,
               .title = "Find the Minimum and Maximum Number of Nodes Between Critical Points",
               .url = "https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/"});
  registerStrategy("Single Pass", solution1);
}

vector<int> FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsSolution::nodesBetweenCriticalPoints(ListNode* head) {
  return getSolution()(head);
}

}  // namespace problem_2058
}  // namespace leetcode
