#include "leetcode/core.h"

namespace leetcode {
namespace problem_3335 {

using Func = std::function<int(string, int)>;

class TotalCharactersInStringAfterTransformationsISolution : public SolutionBase<Func> {
 public:
  int lengthAfterTransformations(string s, int t);

  TotalCharactersInStringAfterTransformationsISolution();
};

}  // namespace problem_3335
}  // namespace leetcode