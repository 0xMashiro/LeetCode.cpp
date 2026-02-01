#include "leetcode/core.h"

namespace leetcode {
namespace problem_2418 {

using Func = std::function<vector<string>(vector<string>&, vector<int>&)>;

class SortThePeopleSolution : public SolutionBase<Func> {
 public:
  //! 2418. Sort the People
  //! https://leetcode.com/problems/sort-the-people/
  vector<string> sortPeople(vector<string>& names, vector<int>& heights);

  SortThePeopleSolution();
};

}  // namespace problem_2418
}  // namespace leetcode
