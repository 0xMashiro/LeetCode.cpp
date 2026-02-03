#include "leetcode/core.h"

namespace leetcode {
namespace problem_609 {

using Func = std::function<vector<vector<string>>(vector<string>&)>;

class FindDuplicateFileInSystemSolution : public SolutionBase<Func> {
 public:
  vector<vector<string>> findDuplicate(vector<string>& paths);

  FindDuplicateFileInSystemSolution();
};

}  // namespace problem_609
}  // namespace leetcode
