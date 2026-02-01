#include "leetcode/core.h"

namespace leetcode {
namespace problem_3291 {

using Func = std::function<int(vector<string>&, string)>;

class MinimumNumberOfValidStringsToFormTargetISolution : public SolutionBase<Func> {
 public:
  int minValidStrings(vector<string>& words, string target);
  MinimumNumberOfValidStringsToFormTargetISolution();
};

}  // namespace problem_3291
}  // namespace leetcode
