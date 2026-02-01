#include "leetcode/core.h"

namespace leetcode {
namespace problem_1317 {

using Func = std::function<vector<int>(int)>;

class ConvertIntegerToTheSumOfTwoNoZeroIntegersSolution : public SolutionBase<Func> {
 public:
  vector<int> getNoZeroIntegers(int n);
  ConvertIntegerToTheSumOfTwoNoZeroIntegersSolution();
};

}  // namespace problem_1317
}  // namespace leetcode
