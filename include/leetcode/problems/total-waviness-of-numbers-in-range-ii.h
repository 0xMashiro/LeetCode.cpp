#include "leetcode/core.h"

namespace leetcode {
namespace problem_3753 {

using Func = std::function<long long(long long, long long)>;

class TotalWavinessOfNumbersInRangeIiSolution : public SolutionBase<Func> {
 public:
  //! 3753. Total Waviness of Numbers in Range II
  //! https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/
  long long totalWaviness(long long num1, long long num2);

  TotalWavinessOfNumbersInRangeIiSolution();
};

}  // namespace problem_3753
}  // namespace leetcode
