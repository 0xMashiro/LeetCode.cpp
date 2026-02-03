#include "leetcode/core.h"

namespace leetcode {
namespace problem_1534 {

using Func = std::function<int(vector<int>&, int, int, int)>;

class CountGoodTripletsSolution : public SolutionBase<Func> {
 public:
  int countGoodTriplets(vector<int>& arr, int a, int b, int c);

  CountGoodTripletsSolution();
};

}  // namespace problem_1534
}  // namespace leetcode
