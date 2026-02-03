#include "leetcode/problems/minimum-amount-of-time-to-fill-cups.h"

namespace leetcode {
namespace problem_2335 {

/**
 * 贪心策略：每秒尽量接满 2 杯不同类型的水
 * 
 * 设排序后 a >= b >= c
 * 情况1：如果 a >= b + c，答案为 a
 *        因为最大的一种水太多，其他两种全部用来配对也不够，
 *        配对完后还需要单独接 a - (b+c) 杯水，总共需要 a 秒
 * 
 * 情况2：如果 a < b + c，答案为 ceil((a+b+c) / 2)
 *        三种水可以较好地配对，总杯数决定了最少秒数
 *        由于每秒最多接 2 杯，所以最少需要 (总和+1)/2 秒
 * 
 * 时间复杂度: O(1)，只需排序 3 个元素
 * 空间复杂度: O(1)
 */
static int solution1(vector<int>& amount) {
  // 排序，使 amount[0] <= amount[1] <= amount[2]
  sort(amount.begin(), amount.end());
  
  int a = amount[2];  // 最大
  int b = amount[1];  // 中间
  int c = amount[0];  // 最小
  
  // 情况1：最大数量 >= 另外两种之和
  if (a >= b + c) {
    return a;
  }
  
  // 情况2：最大数量 < 另外两种之和
  // 需要 ceil((a+b+c)/2) = (总和 + 1) / 2
  return (a + b + c + 1) / 2;
}

MinimumAmountOfTimeToFillCupsSolution::MinimumAmountOfTimeToFillCupsSolution() {
  setMetaInfo({
    .id = 2335,
    .title = "Minimum Amount of Time to Fill Cups",
    .url = "https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/"
  });
  registerStrategy("Greedy Sort", solution1);
}

int MinimumAmountOfTimeToFillCupsSolution::fillCups(vector<int>& amount) {
  return getSolution()(amount);
}

}  // namespace problem_2335
}  // namespace leetcode