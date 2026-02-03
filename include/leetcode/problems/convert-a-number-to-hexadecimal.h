
#include "leetcode/core.h"

namespace leetcode {
namespace problem_405 {

using Func = std::function<string(int)>;

/**
 * 405. Convert a Number to Hexadecimal
 * https://leetcode.com/problems/convert-a-number-to-hexadecimal/
 * 
 * 给定一个 32 位整数，返回其十六进制表示字符串。
 * 负数使用补码表示，字母小写，无前导零。
 */
class ConvertANumberToHexadecimalSolution : public SolutionBase<Func> {
 public:
  string toHex(int num);

  ConvertANumberToHexadecimalSolution();
};

}  // namespace problem_405
}  // namespace leetcode
