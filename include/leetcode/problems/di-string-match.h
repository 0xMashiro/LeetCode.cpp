#include "leetcode/core.h"

namespace leetcode {
namespace problem_942 {

using Func = std::function<vector<int>(string)>;

class DiStringMatchSolution : public SolutionBase<Func> {
 public:
  //! 942. DI String Match
  //! https://leetcode.com/problems/di-string-match/
  vector<int> diStringMatch(string s);

  DiStringMatchSolution();
};

}  // namespace problem_942
}  // namespace leetcode
