#include "leetcode/core.h"

namespace leetcode {
namespace problem_2520 {

using Func = std::function<int(int)>;

class CountTheDigitsThatDivideANumberSolution : public SolutionBase<Func> {
 public:
  int countDigits(int num);

  CountTheDigitsThatDivideANumberSolution();
};

}  // namespace problem_2520
}  // namespace leetcode
