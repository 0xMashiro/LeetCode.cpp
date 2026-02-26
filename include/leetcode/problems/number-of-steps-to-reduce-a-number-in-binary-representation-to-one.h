#include "leetcode/core.h"

namespace leetcode {
namespace problem_1404 {

using Func = std::function<int(string)>;

class NumberOfStepsToReduceANumberInBinaryRepresentationToOneSolution : public SolutionBase<Func> {
 public:
  //! 1404. Number of Steps to Reduce a Number in Binary Representation to One
  //! https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/
  int numSteps(string s);

  NumberOfStepsToReduceANumberInBinaryRepresentationToOneSolution();
};

}  // namespace problem_1404
}  // namespace leetcode
