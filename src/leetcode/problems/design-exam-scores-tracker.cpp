
#include "leetcode/problems/design-exam-scores-tracker.h"

namespace leetcode {
namespace problem_3709 {

ExamTracker::ExamTracker() {
  // 初始化空数组
}

void ExamTracker::record(int time, int score) {
  times_.push_back(time);
  long long newSum = prefixSums_.empty() ? score : prefixSums_.back() + score;
  prefixSums_.push_back(newSum);
}

long long ExamTracker::totalScore(int startTime, int endTime) {
  // 边界检查：如果没有记录，返回 0
  if (times_.empty()) return 0;
  
  // 找到第一个 >= startTime 的位置（左边界）
  auto leftIt = lower_bound(times_.begin(), times_.end(), startTime);
  if (leftIt == times_.end()) return 0;  // 所有时间都小于 startTime
  int leftIdx = leftIt - times_.begin();
  
  // 找到最后一个 <= endTime 的位置（右边界）
  auto rightIt = upper_bound(times_.begin(), times_.end(), endTime);
  if (rightIt == times_.begin()) return 0;  // 所有时间都大于 endTime
  int rightIdx = rightIt - times_.begin() - 1;
  
  // 如果左边界在右边界的右侧，说明没有交集
  if (leftIdx > rightIdx) return 0;
  
  // 计算区间和：prefixSums_[rightIdx] - (leftIdx > 0 ? prefixSums_[leftIdx - 1] : 0)
  long long result = prefixSums_[rightIdx];
  if (leftIdx > 0) {
    result -= prefixSums_[leftIdx - 1];
  }
  return result;
}

}  // namespace problem_3709
}  // namespace leetcode
