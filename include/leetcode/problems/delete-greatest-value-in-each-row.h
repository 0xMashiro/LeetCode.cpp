#include "leetcode/core.h"

namespace leetcode {
namespace problem_2500 {

using Func = std::function<int(vector<vector<int>>&)>;

class DeleteGreatestValueInEachRowSolution : public SolutionBase<Func> {
 public:
  //! 2500. Delete Greatest Value in Each Row
  //! https://leetcode.com/problems/delete-greatest-value-in-each-row/
  int deleteGreatestValue(vector<vector<int>>& grid);

  DeleteGreatestValueInEachRowSolution();
};

}  // namespace problem_2500
}  // namespace leetcode
