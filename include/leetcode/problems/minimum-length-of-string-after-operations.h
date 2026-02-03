#include "leetcode/core.h"

namespace leetcode {
namespace problem_3223 {

using Func = std::function<int(string)>;

/**
 * 3223. Minimum Length of String After Operations
 * https://leetcode.com/problems/minimum-length-of-string-after-operations/
 * 
 * 给定字符串 s，可以进行操作：选择位置 i，删除左右最近的相同字符
 * 返回最终字符串的最小长度
 */
class MinimumLengthOfStringAfterOperationsSolution : public SolutionBase<Func> {
 public:
  int minimumLength(string s);

  MinimumLengthOfStringAfterOperationsSolution();
};

}  // namespace problem_3223
}  // namespace leetcode
