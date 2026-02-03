
#include "leetcode/problems/design-exam-scores-tracker.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3709 {

TEST(LeetCode, DesignExamScoresTrackerExample) {
  // 示例 1
  ExamTracker examTracker;
  
  examTracker.record(1, 98);  // 时间 1，分数 98
  EXPECT_EQ(examTracker.totalScore(1, 1), 98);  // [1,1] 区间，只有时间 1，总分 98
  
  examTracker.record(5, 99);  // 时间 5，分数 99
  EXPECT_EQ(examTracker.totalScore(1, 3), 98);  // [1,3] 区间，只有时间 1，总分 98
  EXPECT_EQ(examTracker.totalScore(1, 5), 197); // [1,5] 区间，时间 1 和 5，总分 98+99=197
  EXPECT_EQ(examTracker.totalScore(3, 4), 0);   // [3,4] 区间，没有考试，总分 0
  EXPECT_EQ(examTracker.totalScore(2, 5), 99);  // [2,5] 区间，只有时间 5，总分 99
}

TEST(LeetCode, DesignExamScoresTrackerEmpty) {
  // 空记录测试
  ExamTracker examTracker;
  // 注意：根据约束，第一个调用必须是 record，所以这里不测空 totalScore
}

}  // namespace problem_3709
}  // namespace leetcode
