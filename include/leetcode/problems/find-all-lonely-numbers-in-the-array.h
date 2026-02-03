#include "leetcode/core.h"

namespace leetcode {
namespace problem_2150 {

using Func = std::function<vector<int>(vector<int>&)>;

class FindAllLonelyNumbersInTheArraySolution : public SolutionBase<Func> {
 public:
  //! 2150. Find All Lonely Numbers in the Array
  //! https://leetcode.com/problems/find-all-lonely-numbers-in-the-array/
  vector<int> findLonely(vector<int>& nums);

  FindAllLonelyNumbersInTheArraySolution();
};

}  // namespace problem_2150
}  // namespace leetcode
