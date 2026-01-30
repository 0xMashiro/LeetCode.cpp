#include "leetcode/core.h"

namespace leetcode {
namespace problem_2977 {

using Func = std::function<long long(std::string, std::string,
                                     std::vector<std::string>&,
                                     std::vector<std::string>&,
                                     std::vector<int>&)>;

class MinimumCostToConvertStringIiSolution : public SolutionBase<Func> {
 public:
  //! 2977. Minimum Cost to Convert String II
  //! https://leetcode.com/problems/minimum-cost-to-convert-string-ii/
  long long minimumCost(std::string source, std::string target,
                        std::vector<std::string>& original,
                        std::vector<std::string>& changed,
                        std::vector<int>& cost);

  MinimumCostToConvertStringIiSolution();
};

}  // namespace problem_2977
}  // namespace leetcode