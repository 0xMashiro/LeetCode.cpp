#include "leetcode/core.h"

namespace leetcode {
namespace problem_1446 {

using Func = std::function<int(std::string)>;

class ConsecutiveCharactersSolution : public SolutionBase<Func> {
 public:
  //! 1446. Consecutive Characters
  //! https://leetcode.com/problems/consecutive-characters/
  int maxPower(std::string s);

  ConsecutiveCharactersSolution();
};

}  // namespace problem_1446
}  // namespace leetcode
