#include "leetcode/core.h"

namespace leetcode {
namespace problem_91 {

using Func = std::function<int(string)>;

class DecodeWaysSolution : public SolutionBase<Func> {
 public:
  //! 91. Decode Ways
  //! https://leetcode.com/problems/decode-ways/
  int numDecodings(string s);

  DecodeWaysSolution();
};

}  // namespace problem_91
}  // namespace leetcode
