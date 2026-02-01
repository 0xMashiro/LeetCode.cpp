#include "leetcode/core.h"

namespace leetcode {
namespace problem_2611 {

using Func = std::function<int(vector<int>&, vector<int>&, int)>;

class MiceAndCheeseSolution : public SolutionBase<Func> {
 public:
  //! 2611. Mice and Cheese
  //! https://leetcode.com/problems/mice-and-cheese/
  int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k);

  MiceAndCheeseSolution();
};

}  // namespace problem_2611
}  // namespace leetcode
