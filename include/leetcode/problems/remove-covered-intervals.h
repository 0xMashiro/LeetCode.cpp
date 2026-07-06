#include "leetcode/core.h"

namespace leetcode {
namespace problem_1288 {

using Func = std::function<int(std::vector<std::vector<int>>&)>;

class RemoveCoveredIntervalsSolution : public SolutionBase<Func> {
 public:
  int removeCoveredIntervals(std::vector<std::vector<int>>& intervals);

  RemoveCoveredIntervalsSolution();
};

}  // namespace problem_1288
}  // namespace leetcode
