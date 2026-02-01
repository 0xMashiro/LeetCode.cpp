
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2861 {

using Func = std::function<int(int, int, int, vector<vector<int>>&, vector<int>&, vector<int>&)>;

class MaximumNumberOfAlloysSolution : public SolutionBase<Func> {
 public:
  //! 2861. Maximum Number of Alloys
  //! https://leetcode.com/problems/maximum-number-of-alloys/
  int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, 
                         vector<int>& stock, vector<int>& cost);

  MaximumNumberOfAlloysSolution();
};

}  // namespace problem_2861
}  // namespace leetcode
