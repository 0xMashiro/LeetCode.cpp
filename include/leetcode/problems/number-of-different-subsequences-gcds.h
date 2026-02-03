#include "leetcode/core.h"

namespace leetcode {
namespace problem_1819 {

using Func = std::function<int(vector<int>&)>;

class NumberOfDifferentSubsequencesGcdsSolution : public SolutionBase<Func> {
 public:
  int countDifferentSubsequenceGCDs(vector<int>& nums);

  NumberOfDifferentSubsequencesGcdsSolution();
};

}  // namespace problem_1819
}  // namespace leetcode
