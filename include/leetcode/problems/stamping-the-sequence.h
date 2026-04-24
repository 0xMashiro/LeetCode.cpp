#include "leetcode/core.h"

namespace leetcode {
namespace problem_936 {

using Func = std::function<vector<int>(string, string)>;

class StampingTheSequenceSolution : public SolutionBase<Func> {
 public:
  //! 936. Stamping The Sequence
  //! https://leetcode.com/problems/stamping-the-sequence/
  vector<int> movesToStamp(string stamp, string target);

  StampingTheSequenceSolution();
};

}  // namespace problem_936
}  // namespace leetcode
