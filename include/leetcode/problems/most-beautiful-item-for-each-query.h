#include "leetcode/core.h"

namespace leetcode {
namespace problem_2070 {

using Func = std::function<vector<int>(vector<vector<int>>&, vector<int>&)>;

class MostBeautifulItemForEachQuerySolution : public SolutionBase<Func> {
 public:
  //! 2070. Most Beautiful Item for Each Query
  //! https://leetcode.com/problems/most-beautiful-item-for-each-query/
  vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries);

  MostBeautifulItemForEachQuerySolution();
};

}  // namespace problem_2070
}  // namespace leetcode
