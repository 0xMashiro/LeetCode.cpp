#include "leetcode/core.h"

namespace leetcode {
namespace problem_848 {

using Func = std::function<string(string, vector<int>&)>;

class ShiftingLettersSolution : public SolutionBase<Func> {
 public:
  //! 848. Shifting Letters
  //! https://leetcode.com/problems/shifting-letters/
  string shiftingLetters(string s, vector<int>& shifts);

  ShiftingLettersSolution();
};

}  // namespace problem_848
}  // namespace leetcode
