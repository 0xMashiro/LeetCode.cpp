#include "leetcode/core.h"

namespace leetcode {
namespace problem_3398 {

using Func = std::function<int(string&, int)>;

class SmallestSubstringWithIdenticalCharactersISolution : public SolutionBase<Func> {
 public:
  int minLength(string s, int numOps);
  SmallestSubstringWithIdenticalCharactersISolution();
};

}  // namespace problem_3398
}  // namespace leetcode