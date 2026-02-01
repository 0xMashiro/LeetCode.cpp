#include "leetcode/core.h"

namespace leetcode {
namespace problem_443 {

using Func = std::function<int(vector<char>&)>;

class StringCompressionSolution : public SolutionBase<Func> {
 public:
  int compress(vector<char>& chars);

  StringCompressionSolution();
};

}  // namespace problem_443
}  // namespace leetcode
