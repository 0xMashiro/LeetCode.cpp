#include "leetcode/core.h"

namespace leetcode {
namespace problem_1662 {

using Func = std::function<bool(vector<string>&, vector<string>&)>;

class CheckIfTwoStringArraysAreEquivalentSolution : public SolutionBase<Func> {
 public:
  bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2);

  CheckIfTwoStringArraysAreEquivalentSolution();
};

}  // namespace problem_1662
}  // namespace leetcode
