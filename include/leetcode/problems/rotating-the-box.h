#ifndef LEETCODE_PROBLEMS_ROTATING_THE_BOX_H__
#define LEETCODE_PROBLEMS_ROTATING_THE_BOX_H__

#include "leetcode/core.h"

namespace leetcode {
namespace problem_1861 {

using Func = std::function<vector<vector<char>>(vector<vector<char>>&)>;

class RotatingTheBoxSolution : public SolutionBase<Func> {
 public:
  //! 1861. Rotating the Box
  //! https://leetcode.com/problems/rotating-the-box/
  vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid);

  RotatingTheBoxSolution();
};

}  // namespace problem_1861
}  // namespace leetcode

#endif  // LEETCODE_PROBLEMS_ROTATING_THE_BOX_H__
