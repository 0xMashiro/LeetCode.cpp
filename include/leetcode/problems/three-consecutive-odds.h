#include "leetcode/core.h"

namespace leetcode {
namespace problem_1550 {

using Func = std::function<bool(vector<int>&)>;

class ThreeConsecutiveOddsSolution : public SolutionBase<Func> {
 public:
  bool threeConsecutiveOdds(vector<int>& arr);

  ThreeConsecutiveOddsSolution();
};

}  // namespace problem_1550
}  // namespace leetcode
