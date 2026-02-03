#include "leetcode/core.h"

namespace leetcode {
namespace problem_2185 {

using Func = std::function<int(vector<string>&, string)>;

class CountingWordsWithAGivenPrefixSolution : public SolutionBase<Func> {
 public:
  //! 2185. Counting Words With a Given Prefix
  //! https://leetcode.com/problems/counting-words-with-a-given-prefix/
  int prefixCount(vector<string>& words, string pref);

  CountingWordsWithAGivenPrefixSolution();
};

}  // namespace problem_2185
}  // namespace leetcode
