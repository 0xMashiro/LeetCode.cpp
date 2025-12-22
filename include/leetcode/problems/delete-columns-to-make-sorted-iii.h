#include "leetcode/core.h"

namespace leetcode {
namespace problem_960 {

using Func = std::function<int(vector<string>&)>;

class DeleteColumnsToMakeSortedIiiSolution : public SolutionBase<Func> {
 public:
  //! 960. Delete Columns to Make Sorted III
  //! https://leetcode.com/problems/delete-columns-to-make-sorted-iii/
  int minDeletionSize(vector<string>& strs);

  DeleteColumnsToMakeSortedIiiSolution();
};

}  // namespace problem_960
}  // namespace leetcode