#include "leetcode/core.h"

namespace leetcode {
namespace problem_2975 {

using Func = std::function<int(int, int, vector<int>&, vector<int>&)>;

class MaximumSquareAreaByRemovingFencesFromAFieldSolution : public SolutionBase<Func> {
 public:
  int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences);

  MaximumSquareAreaByRemovingFencesFromAFieldSolution();
};

}  // namespace problem_2975
}  // namespace leetcode