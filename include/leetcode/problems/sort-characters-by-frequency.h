
#include "leetcode/core.h"

namespace leetcode {
namespace problem_451 {

using Func = std::function<string(string)>;

class SortCharactersByFrequencySolution : public SolutionBase<Func> {
 public:
  //! 451. Sort Characters By Frequency
  //! https://leetcode.com/problems/sort-characters-by-frequency/
  string frequencySort(string s);

  SortCharactersByFrequencySolution();
};

}  // namespace problem_451
}  // namespace leetcode
