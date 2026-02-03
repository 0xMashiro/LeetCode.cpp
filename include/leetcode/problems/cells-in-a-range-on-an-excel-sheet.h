#include "leetcode/core.h"

namespace leetcode {
namespace problem_2194 {

using Func = std::function<vector<string>(string)>;

class CellsInARangeOnAnExcelSheetSolution : public SolutionBase<Func> {
 public:
  vector<string> cellsInRange(string s);
  CellsInARangeOnAnExcelSheetSolution();
};

}  // namespace problem_2194
}  // namespace leetcode
