#include "leetcode/core.h"

namespace leetcode {
namespace problem_2937 {

using Func = std::function<int(string, string, string)>;

class MakeThreeStringsEqualSolution : public SolutionBase<Func> {
 public:
  //! 2937. Make Three Strings Equal
  //! https://leetcode.com/problems/make-three-strings-equal/
  int findMinimumOperations(string s1, string s2, string s3);

  MakeThreeStringsEqualSolution();
};

}  // namespace problem_2937
}  // namespace leetcode
