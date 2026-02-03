#include "leetcode/core.h"

namespace leetcode {
namespace problem_1643 {

using Func = std::function<string(vector<int>&, int)>;

class KthSmallestInstructionsSolution : public SolutionBase<Func> {
 public:
  string kthSmallestPath(vector<int>& destination, int k);
  KthSmallestInstructionsSolution();
};

}  // namespace problem_1643
}  // namespace leetcode
