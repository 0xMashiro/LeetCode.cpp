
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2442 {

using Func = std::function<int(vector<int>&)>;

class CountNumberOfDistinctIntegersAfterReverseOperationsSolution : public SolutionBase<Func> {
 public:
  //! 2442. Count Number of Distinct Integers After Reverse Operations
  //! https://leetcode.com/problems/count-number-of-distinct-integers-after-reverse-operations/
  int countDistinctIntegers(vector<int>& nums);

  CountNumberOfDistinctIntegersAfterReverseOperationsSolution();

 private:
  //! 反转一个正整数的各位数字
  //! @param num 要反转的正整数
  //! @return 反转后的整数
  int reverse(int num);
};

}  // namespace problem_2442
}  // namespace leetcode
