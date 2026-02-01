#include "leetcode/core.h"

namespace leetcode {
namespace problem_619 {

/**
 * 619. Biggest Single Number
 * https://leetcode.com/problems/biggest-single-number/
 *
 * 找出数组中只出现一次的数字中的最大值。
 * 如果没有只出现一次的数字，返回 null（用 optional<int> 表示）。
 *
 * 思路：
 * 1. 使用哈希表统计每个数字出现的次数
 * 2. 遍历哈希表，找出出现次数为 1 的数字
 * 3. 返回这些数字中的最大值
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
 */

using Func = std::function<std::optional<int>(const vector<int>&)>;

class BiggestSingleNumberSolution : public SolutionBase<Func> {
 public:
  //! 619. Biggest Single Number
  //! https://leetcode.com/problems/biggest-single-number/
  std::optional<int> biggestSingleNumber(const vector<int>& nums);

  BiggestSingleNumberSolution();
};

}  // namespace problem_619
}  // namespace leetcode
