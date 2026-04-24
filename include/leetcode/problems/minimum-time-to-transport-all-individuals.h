#include "leetcode/core.h"

namespace leetcode {
namespace problem_3594 {

using Func = std::function<double(int, int, int, vector<int>&, vector<double>&)>;

class MinimumTimeToTransportAllIndividualsSolution : public SolutionBase<Func> {
 public:
  double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul);
  MinimumTimeToTransportAllIndividualsSolution();
};

}  // namespace problem_3594
}  // namespace leetcode
