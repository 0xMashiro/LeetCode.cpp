#include "leetcode/problems/maximum-consecutive-floors-without-special-floors.h"

namespace leetcode {
namespace problem_2274 {

/**
 * 解题思路：
 * 1. 对 special 数组排序
 * 2. 计算 bottom 到第一个 special 楼层之间的间隔
 * 3. 计算相邻 special 楼层之间的间隔（中间无特殊楼层的数量）
 * 4. 计算最后一个 special 楼层到 top 之间的间隔
 * 5. 返回上述所有间隔的最大值
 * 
 * 时间复杂度: O(n log n)，主要来自排序
 * 空间复杂度: O(1) 或 O(n)（取决于排序实现）
 */
static int solution1(int bottom, int top, vector<int>& special) {
  // 对特殊楼层排序
  sort(special.begin(), special.end());
  
  int maxConsecutive = 0;
  
  // 计算 bottom 到第一个 special 楼层之间的连续楼层数
  maxConsecutive = max(maxConsecutive, special[0] - bottom);
  
  // 计算相邻 special 楼层之间的间隔
  for (size_t i = 1; i < special.size(); ++i) {
    // special[i-1] 和 special[i] 之间的楼层数（不包括两端）
    maxConsecutive = max(maxConsecutive, special[i] - special[i - 1] - 1);
  }
  
  // 计算最后一个 special 楼层到 top 之间的连续楼层数
  maxConsecutive = max(maxConsecutive, top - special.back());
  
  return maxConsecutive;
}

MaximumConsecutiveFloorsWithoutSpecialFloorsSolution::MaximumConsecutiveFloorsWithoutSpecialFloorsSolution() {
  setMetaInfo({.id = 2274,
               .title = "Maximum Consecutive Floors Without Special Floors",
               .url = "https://leetcode.com/problems/maximum-consecutive-floors-without-special-floors/"});
  registerStrategy("Sorting", solution1);
}

int MaximumConsecutiveFloorsWithoutSpecialFloorsSolution::maxConsecutive(int bottom, int top, vector<int>& special) {
  return getSolution()(bottom, top, special);
}

}  // namespace problem_2274
}  // namespace leetcode
