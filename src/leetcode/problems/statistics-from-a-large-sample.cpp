#include "leetcode/problems/statistics-from-a-large-sample.h"

namespace leetcode {
namespace problem_1093 {

/**
 * 解题思路：
 * 1. minimum：找到 count[k] > 0 的最小 k
 * 2. maximum：找到 count[k] > 0 的最大 k
 * 3. mean：计算 sum(k * count[k]) / total_count
 * 4. median：找到中间位置的值
 *    - 奇数：找第 (total+1)/2 个元素
 *    - 偶数：找第 total/2 和第 total/2 + 1 个元素的平均
 * 5. mode：找到 count[k] 最大的 k
 * 
 * 时间复杂度：O(256) = O(1)
 * 空间复杂度：O(1)
 */
static vector<double> solution1(vector<int>& count) {
  double minimum = -1, maximum = -1;
  double mean = 0, median = 0;
  double mode = 0;
  
  long long total_sum = 0;  // 用 long long 防溢出
  long long total_count = 0;
  long long max_count = 0;
  
  // 遍历所有可能的值 0-255
  for (int k = 0; k < 256; ++k) {
    if (count[k] > 0) {
      // 更新最小值（第一次遇到非0）
      if (minimum == -1) {
        minimum = k;
      }
      // 最大值不断更新
      maximum = k;
      
      // 计算总和和总个数
      total_sum += static_cast<long long>(k) * count[k];
      total_count += count[k];
      
      // 更新众数
      if (count[k] > max_count) {
        max_count = count[k];
        mode = k;
      }
    }
  }
  
  mean = static_cast<double>(total_sum) / total_count;
  
  // 计算中位数
  long long target1 = (total_count + 1) / 2;  // 奇数时是中间，偶数时是左中间
  long long target2 = (total_count % 2 == 0) ? target1 + 1 : target1;  // 奇数时相同
  
  long long cur_count = 0;
  double median_val1 = 0, median_val2 = 0;
  
  for (int k = 0; k < 256; ++k) {
    if (count[k] == 0) continue;
    
    cur_count += count[k];
    
    if (median_val1 == 0 && cur_count >= target1) {
      median_val1 = k;
    }
    if (median_val2 == 0 && cur_count >= target2) {
      median_val2 = k;
      break;
    }
  }
  
  median = (median_val1 + median_val2) / 2.0;
  
  return {minimum, maximum, mean, median, mode};
}

StatisticsFromALargeSampleSolution::StatisticsFromALargeSampleSolution() {
  setMetaInfo({
    .id = 1093,
    .title = "Statistics from a Large Sample",
    .url = "https://leetcode.com/problems/statistics-from-a-large-sample/"
  });
  registerStrategy("Single Pass", solution1);
}

vector<double> StatisticsFromALargeSampleSolution::sampleStats(vector<int>& count) {
  return getSolution()(count);
}

}  // namespace problem_1093
}  // namespace leetcode
