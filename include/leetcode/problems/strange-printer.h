
#include "leetcode/core.h"

namespace leetcode {
namespace problem_664 {

using Func = std::function<int(string)>;

class StrangePrinterSolution : public SolutionBase<Func> {
 public:
  //! 664. Strange Printer
  //! https://leetcode.com/problems/strange-printer/
  int strangePrinter(string s);

  StrangePrinterSolution();
};

}  // namespace problem_664
}  // namespace leetcode
