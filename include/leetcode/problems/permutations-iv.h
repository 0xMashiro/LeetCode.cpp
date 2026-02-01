
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3470 {

using Func = std::function<vector<int>(int, long long)>;

class PermutationsIvSolution : public SolutionBase<Func> {
 public:
  vector<int> permute(int n, long long k);
  PermutationsIvSolution();
};

}  // namespace problem_3470
}  // namespace leetcode
