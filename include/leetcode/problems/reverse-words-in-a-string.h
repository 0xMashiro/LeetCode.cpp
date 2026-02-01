#include "leetcode/core.h"

namespace leetcode {
namespace problem_151 {

using Func = std::function<string(string)>;

class ReverseWordsInAStringSolution : public SolutionBase<Func> {
 public:
  //! 151. Reverse Words in a String
  //! https://leetcode.com/problems/reverse-words-in-a-string/
  string reverseWords(string s);

  ReverseWordsInAStringSolution();
};

}  // namespace problem_151
}  // namespace leetcode
