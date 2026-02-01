#include "leetcode/core.h"

namespace leetcode {
namespace problem_420 {

using Func = std::function<int(string)>;

class StrongPasswordCheckerSolution : public SolutionBase<Func> {
 public:
  //! 420. Strong Password Checker
  //! https://leetcode.com/problems/strong-password-checker/
  int strongPasswordChecker(string password);

  StrongPasswordCheckerSolution();
};

}  // namespace problem_420
}  // namespace leetcode
