#include "leetcode/core.h"

namespace leetcode {
namespace problem_2201 {

using Func = std::function<int(int, vector<vector<int>>&, vector<vector<int>>&)>;

class CountArtifactsThatCanBeExtractedSolution : public SolutionBase<Func> {
 public:
  int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig);

  CountArtifactsThatCanBeExtractedSolution();
};

}  // namespace problem_2201
}  // namespace leetcode
