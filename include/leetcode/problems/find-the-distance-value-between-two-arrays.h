#include "leetcode/core.h"

namespace leetcode {
namespace problem_1385 {

using Func = std::function<int(vector<int>&, vector<int>&, int)>;

class FindTheDistanceValueBetweenTwoArraysSolution : public SolutionBase<Func> {
 public:
  //! 1385. Find the Distance Value Between Two Arrays
  //! https://leetcode.com/problems/find-the-distance-value-between-two-arrays/
  int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d);

  FindTheDistanceValueBetweenTwoArraysSolution();
};

}  // namespace problem_1385
}  // namespace leetcode
