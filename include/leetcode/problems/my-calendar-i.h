#include "leetcode/core.h"

namespace leetcode {
namespace problem_729 {

/**
 * My Calendar I 实现
 * 思路：使用有序映射（std::map）存储所有预订的区间，key 为开始时间，value 为结束时间
 * - map 按键自动排序，可以高效查找相邻区间
 * - 对于新预订 [start, end)，使用 lower_bound 找到第一个开始时间 >= start 的区间
 * - 检查该区间和前一个区间是否与新区间重叠
 * 时间复杂度：每次 book 操作 O(log n)，n 为已预订的区间数
 * 空间复杂度：O(n)
 * 
 * 重叠判断条件：两个区间 [s1, e1) 和 [s2, e2) 重叠当且仅当 s1 < e2 且 s2 < e1
 * 等价于：非 (e1 <= s2 或 e2 <= s1)
 */
class MyCalendar {
 public:
  MyCalendar() = default;

  /**
   * 尝试预订一个区间 [start, end)
   * @param start 开始时间（包含）
   * @param end 结束时间（不包含）
   * @return 如果无重叠则预订成功返回 true，否则返回 false
   */
  bool book(int start, int end);

 private:
  // 存储 {开始时间, 结束时间}，按开始时间排序
  std::map<int, int> bookings_;
};

}  // namespace problem_729
}  // namespace leetcode
