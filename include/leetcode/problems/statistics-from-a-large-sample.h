#include "leetcode/core.h"

namespace leetcode {
namespace problem_1093 {

using Func = std::function<vector<double>(vector<int>&)>;

class StatisticsFromALargeSampleSolution : public SolutionBase<Func> {
 public:
  //! 1093. Statistics from a Large Sample
  //! https://leetcode.com/problems/statistics-from-a-large-sample/
  vector<double> sampleStats(vector<int>& count);

  StatisticsFromALargeSampleSolution();
};

}  // namespace problem_1093
}  // namespace leetcode
