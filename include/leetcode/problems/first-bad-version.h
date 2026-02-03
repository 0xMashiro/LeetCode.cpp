#include "leetcode/core.h"

namespace leetcode {
namespace problem_278 {

using Func = std::function<int(int)>;

// 模拟 API isBadVersion，由测试框架设置
extern std::function<bool(int)> isBadVersion_api;

class FirstBadVersionSolution : public SolutionBase<Func> {
 public:
  //! 278. First Bad Version
  //! https://leetcode.com/problems/first-bad-version/
  int firstBadVersion(int n);

  FirstBadVersionSolution();
};

}  // namespace problem_278
}  // namespace leetcode
