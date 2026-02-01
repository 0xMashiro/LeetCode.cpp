#include "leetcode/problems/my-calendar-i.h"

namespace leetcode {
namespace problem_729 {

bool MyCalendar::book(int start, int end) {
  // 找到第一个开始时间 >= start 的区间
  auto it = bookings_.lower_bound(start);
  
  // 检查后面的区间：it 的开始时间必须 >= end（新区间在 it 之前结束）
  if (it != bookings_.end() && it->first < end) {
    // 后面有区间，且该区间的开始时间 < 新区间的结束时间，重叠
    return false;
  }
  
  // 检查前面的区间：前一个区间的结束时间必须 <= start
  if (it != bookings_.begin()) {
    auto prev = std::prev(it);
    if (prev->second > start) {
      // 前一个区间的结束时间 > 新区间的开始时间，重叠
      return false;
    }
  }
  
  // 无重叠，插入新区间
  bookings_[start] = end;
  return true;
}

}  // namespace problem_729
}  // namespace leetcode
