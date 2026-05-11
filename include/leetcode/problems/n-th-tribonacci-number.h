#include "leetcode/core.h"

namespace leetcode {
namespace problem_1137 {

using Func = std::function<int(int)>;

class NThTribonacciNumberSolution : public SolutionBase<Func> {
 public:
  //! 1137. N-th Tribonacci Number
  //! https://leetcode.com/problems/n-th-tribonacci-number/
  int tribonacci(int n);

  NThTribonacciNumberSolution();
};

}  // namespace problem_1137
}  // namespace leetcode
