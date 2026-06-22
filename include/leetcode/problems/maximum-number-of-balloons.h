#include "leetcode/core.h"

namespace leetcode {
namespace problem_1189 {

using Func = std::function<int(std::string)>;

class MaximumNumberOfBalloonsSolution : public SolutionBase<Func> {
 public:
  //! 1189. Maximum Number of Balloons
  //! https://leetcode.com/problems/maximum-number-of-balloons/
  int maxNumberOfBalloons(std::string text);

  MaximumNumberOfBalloonsSolution();
};

}  // namespace problem_1189
}  // namespace leetcode
