#include "leetcode/core.h"

namespace leetcode {
namespace problem_1735 {

using Func = std::function<vector<int>(vector<vector<int>> &)>;

class CountWaysToMakeArrayWithProductSolution : public SolutionBase<Func> {
 public:
  vector<int> waysToFillArray(vector<vector<int>> &queries);

  CountWaysToMakeArrayWithProductSolution();
};

}  // namespace problem_1735
}  // namespace leetcode
