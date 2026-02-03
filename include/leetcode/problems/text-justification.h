#include "leetcode/core.h"

namespace leetcode {
namespace problem_68 {

using Func = std::function<vector<string>(vector<string>&, int)>;

class TextJustificationSolution : public SolutionBase<Func> {
 public:
  //! 68. Text Justification
  //! https://leetcode.com/problems/text-justification/
  vector<string> fullJustify(vector<string>& words, int maxWidth);

  TextJustificationSolution();
};

}  // namespace problem_68
}  // namespace leetcode
