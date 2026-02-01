#include "leetcode/core.h"

namespace leetcode {
namespace problem_378 {

using Func = std::function<int(vector<vector<int>>&, int)>;

class KthSmallestElementInASortedMatrixSolution : public SolutionBase<Func> {
 public:
  int kthSmallest(vector<vector<int>>& matrix, int k);

  KthSmallestElementInASortedMatrixSolution();
};

}  // namespace problem_378
}  // namespace leetcode
