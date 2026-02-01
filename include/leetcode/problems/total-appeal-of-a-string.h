#include "leetcode/core.h"

namespace leetcode {
namespace problem_2262 {

using Func = std::function<long long(string&)>;

/**
 * 2262. Total Appeal of A String
 * https://leetcode.com/problems/total-appeal-of-a-string/
 *
 * 思路：计算每个位置字符的贡献
 * 对于位置 i 的字符 s[i]，它在一个子串中产生贡献当且仅当它是该子串中
 * 该字符的最左出现。
 * 
 * 设 last[s[i]] 为字符 s[i] 上次出现的位置（没有则为 -1）：
 * - 起始位置可选范围：[last[s[i]]+1, i]，共 i - last[s[i]] 种
 * - 结束位置可选范围：[i, n-1]，共 n - i 种
 * - 该位置贡献 = (i - last[s[i]]) * (n - i)
 * 
 * 时间复杂度：O(n)，空间复杂度：O(1)
 */
class TotalAppealOfAStringSolution : public SolutionBase<Func> {
 public:
  long long appealSum(string s);

  TotalAppealOfAStringSolution();
};

}  // namespace problem_2262
}  // namespace leetcode
