#include "leetcode/core.h"

namespace leetcode {
namespace problem_1897 {

using Func = std::function<bool(vector<string>&)>;

class RedistributeCharactersToMakeAllStringsEqualSolution : public SolutionBase<Func> {
 public:
  //! 1897. Redistribute Characters to Make All Strings Equal
  //! https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/
  bool makeEqual(vector<string>& words);

  RedistributeCharactersToMakeAllStringsEqualSolution();
};

}  // namespace problem_1897
}  // namespace leetcode
