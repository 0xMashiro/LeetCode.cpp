#include "leetcode/problems/minimum-processing-time.h"

namespace leetcode {
namespace problem_2895 {

/**
 * 贪心策略：为了最小化最大完成时间
 * 1. 将处理器可用时间按升序排序
 * 2. 将任务按执行时间降序排序
 * 3. 把最长的4个任务分配给最早可用的处理器
 * 4. 计算每个处理器的完成时间，取最大值
 * 
 * 时间复杂度: O(n log n) 主要是排序
 * 空间复杂度: O(1) 或 O(n) 取决于排序实现
 */
static int solution1(vector<int>& processorTime, vector<int>& tasks) {
  // 处理器可用时间升序排序
  sort(processorTime.begin(), processorTime.end());
  
  // 任务执行时间降序排序
  sort(tasks.begin(), tasks.end(), greater<int>());
  
  int n = processorTime.size();
  int maxTime = 0;
  
  // 每个处理器分配4个任务
  for (int i = 0; i < n; ++i) {
    // 第 i 个处理器分配到第 i*4, i*4+1, i*4+2, i*4+3 个任务（最长的4个）
    int startIdx = i * 4;
    int processorFinishTime = processorTime[i] + tasks[startIdx];  // 最长任务
    maxTime = max(maxTime, processorFinishTime);
  }
  
  return maxTime;
}

MinimumProcessingTimeSolution::MinimumProcessingTimeSolution() {
  setMetaInfo({
    .id = 2895,
    .title = "Minimum Processing Time",
    .url = "https://leetcode.com/problems/minimum-processing-time/"
  });
  registerStrategy("Greedy Sort", solution1);
}

int MinimumProcessingTimeSolution::minProcessingTime(vector<int>& processorTime, vector<int>& tasks) {
  return getSolution()(processorTime, tasks);
}

}  // namespace problem_2895
}  // namespace leetcode
