#include "leetcode/core.h"

namespace leetcode {
namespace problem_2601 {

using Func = std::function<bool(vector<int>&)>;

class PrimeSubtractionOperationSolution : public SolutionBase<Func> {
 public:
  bool primeSubOperation(vector<int>& nums);
  
  PrimeSubtractionOperationSolution();
};

}  // namespace problem_2601
}  // namespace leetcode
