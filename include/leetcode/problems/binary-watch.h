#include "leetcode/core.h"

namespace leetcode {
namespace problem_401 {

using Func = std::function<vector<string>(int)>;

class BinaryWatchSolution : public SolutionBase<Func> {
 public:
  //! 401. Binary Watch
  //! https://leetcode.com/problems/binary-watch/
  vector<string> readBinaryWatch(int turnedOn);

  BinaryWatchSolution();
};

}  // namespace problem_401
}  // namespace leetcode
