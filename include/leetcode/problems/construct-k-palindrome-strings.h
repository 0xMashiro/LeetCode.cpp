
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1400 {

using Func = std::function<bool(string, int)>;

/**
 * @brief Construct K Palindrome Strings
 * @link https://leetcode.com/problems/construct-k-palindrome-strings/
 * 
 * 给定字符串 s 和整数 k，判断是否可以用 s 中所有字符构造 k 个非空回文字符串。
 * 
 * 核心思路：
 * - 统计每个字符出现次数
 * - 计算出现奇数次的字符个数 oddCount
 * - 每个回文串最多一个奇数次字符作为"中间字符"
 * - 条件：oddCount <= k <= s.length()
 */
class ConstructKPalindromeStringsSolution : public SolutionBase<Func> {
 public:
  bool canConstruct(string s, int k);

  ConstructKPalindromeStringsSolution();
};

}  // namespace problem_1400
}  // namespace leetcode
