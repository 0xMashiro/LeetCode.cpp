#include "leetcode/core.h"

namespace leetcode {
namespace problem_2619 {

using Func = std::function<int(vector<int>&)>;

/**
 * @brief 数组原型最后一个元素
 * 
 * 实现一个函数，返回数组的最后一个元素。
 * 如果数组为空，返回 -1。
 * 
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */
class ArrayPrototypeLastSolution : public SolutionBase<Func> {
 public:
  //! 2619. Array Prototype Last
  //! https://leetcode.com/problems/array-prototype-last/
  int last(vector<int>& nums);

  ArrayPrototypeLastSolution();
};

}  // namespace problem_2619
}  // namespace leetcode
