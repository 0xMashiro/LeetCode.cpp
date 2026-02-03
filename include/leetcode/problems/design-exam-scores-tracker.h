
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3709 {

/**
 * Exam Scores Tracker 实现
 * 思路：使用前缀和 + 二分查找
 * - times_ 数组存储记录的时间点（严格递增）
 * - prefixSums_ 数组存储到当前时间点为止的分数前缀和
 * - record(): 追加时间和新的前缀和，O(1)
 * - totalScore(): 二分查找左右边界，返回区间和，O(log n)
 * 时间复杂度：record O(1), totalScore O(log n)
 * 空间复杂度：O(n)，n 为 record 调用次数
 */
class ExamTracker {
 public:
  ExamTracker();

  void record(int time, int score);

  long long totalScore(int startTime, int endTime);

 private:
  vector<int> times_;        // 记录的时间点（严格递增）
  vector<long long> prefixSums_;  // 前缀和，prefixSums_[i] 表示 times_[0..i] 的分数总和
};

}  // namespace problem_3709
}  // namespace leetcode
