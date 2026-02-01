#include "leetcode/problems/my-calendar-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_729 {

TEST(LeetCode, MyCalendarI_Example1) {
  MyCalendar myCalendar;
  EXPECT_TRUE(myCalendar.book(10, 20));   // 预订成功
  EXPECT_FALSE(myCalendar.book(15, 25));  // 与 [10, 20) 重叠，预订失败
  EXPECT_TRUE(myCalendar.book(20, 30));   // [20, 30) 与 [10, 20) 不重叠（20 不包含在 [10, 20) 中），预订成功
}

TEST(LeetCode, MyCalendarI_SingleBooking) {
  MyCalendar myCalendar;
  EXPECT_TRUE(myCalendar.book(5, 10));
}

TEST(LeetCode, MyCalendarI_NoOverlap) {
  MyCalendar myCalendar;
  EXPECT_TRUE(myCalendar.book(10, 20));
  EXPECT_TRUE(myCalendar.book(20, 30));  // 刚好相接，无重叠
  EXPECT_TRUE(myCalendar.book(5, 10));   // 刚好相接，无重叠
}

TEST(LeetCode, MyCalendarI_CompleteOverlap) {
  MyCalendar myCalendar;
  EXPECT_TRUE(myCalendar.book(10, 20));
  EXPECT_FALSE(myCalendar.book(10, 20));  // 完全重叠
  EXPECT_FALSE(myCalendar.book(11, 19));  // 被包含
  EXPECT_FALSE(myCalendar.book(5, 15));   // 部分重叠（前面）
  EXPECT_FALSE(myCalendar.book(15, 25));  // 部分重叠（后面）
}

TEST(LeetCode, MyCalendarI_MultipleBookings) {
  MyCalendar myCalendar;
  EXPECT_TRUE(myCalendar.book(10, 20));
  EXPECT_TRUE(myCalendar.book(30, 40));
  EXPECT_TRUE(myCalendar.book(50, 60));
  EXPECT_FALSE(myCalendar.book(15, 35));  // 与 [10, 20) 和 [30, 40) 都重叠
  EXPECT_TRUE(myCalendar.book(20, 30));   // 刚好在 [10, 20) 和 [30, 40) 之间
  EXPECT_FALSE(myCalendar.book(25, 35));  // 与 [30, 40) 不重叠？等等，25 < 30，所以不重叠...实际上 25 < 30 且 35 > 30，所以与 [30, 40) 重叠
}

TEST(LeetCode, MyCalendarI_EdgeCase_ZeroDuration) {
  // 虽然题目保证 start < end，但测试边界情况
  MyCalendar myCalendar;
  EXPECT_TRUE(myCalendar.book(10, 20));
  // [20, 20) 是无效区间，不考虑
}

TEST(LeetCode, MyCalendarI_LargeNumbers) {
  MyCalendar myCalendar;
  EXPECT_TRUE(myCalendar.book(0, 1000000000));
  EXPECT_FALSE(myCalendar.book(1, 2));
}

TEST(LeetCode, MyCalendarI_AlternatingBookings) {
  MyCalendar myCalendar;
  // 交替预订成功和失败
  EXPECT_TRUE(myCalendar.book(10, 20));
  EXPECT_TRUE(myCalendar.book(20, 30));
  EXPECT_FALSE(myCalendar.book(25, 35));  // 与 [20, 30) 重叠
  EXPECT_TRUE(myCalendar.book(30, 40));
  EXPECT_FALSE(myCalendar.book(5, 15));   // 与 [10, 20) 重叠
  EXPECT_TRUE(myCalendar.book(40, 50));
}

}  // namespace problem_729
}  // namespace leetcode
