#include "leetcode/core.h"

namespace leetcode {
namespace problem_2451 {

using Func = std::function<string(vector<string>&)>;

class OddStringDifferenceSolution : public SolutionBase<Func> {
 public:
  string oddString(vector<string>& words);
  OddStringDifferenceSolution();
};

}  // namespace problem_2451
}  // namespace leetcode
