#include "leetcode/core.h"

namespace leetcode {
namespace problem_1111 {

using Func = std::function<vector<int>(string)>;

class MaximumNestingDepthOfTwoValidParenthesesStringsSolution : public SolutionBase<Func> {
 public:
  vector<int> maxDepthAfterSplit(string seq);

  MaximumNestingDepthOfTwoValidParenthesesStringsSolution();
};

}  // namespace problem_1111
}  // namespace leetcode