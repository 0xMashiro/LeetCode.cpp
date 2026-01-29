#include "leetcode/core.h"

namespace leetcode {
namespace problem_2976 {

using Func = std::function<long long(string, string, vector<char>&, vector<char>&, vector<int>&)>;

class MinimumCostToConvertStringISolution : public SolutionBase<Func> {
 public:
  //! 2976. Minimum Cost to Convert String I
  //! https://leetcode.com/problems/minimum-cost-to-convert-string-i/
  long long minimumCost(string source, string target,
                        vector<char>& original, vector<char>& changed,
                        vector<int>& cost);

  MinimumCostToConvertStringISolution();
};

}  // namespace problem_2976
}  // namespace leetcode