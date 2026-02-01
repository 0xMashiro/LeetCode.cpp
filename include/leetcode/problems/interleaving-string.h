#include "leetcode/core.h"

namespace leetcode {
namespace problem_97 {

using Func = std::function<bool(string, string, string)>;

class InterleavingStringSolution : public SolutionBase<Func> {
 public:
  //! 97. Interleaving String
  //! https://leetcode.com/problems/interleaving-string/
  bool isInterleave(string s1, string s2, string s3);

  InterleavingStringSolution();
};

}  // namespace problem_97
}  // namespace leetcode
