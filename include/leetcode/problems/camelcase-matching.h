#include "leetcode/core.h"

namespace leetcode {
namespace problem_1023 {

using Func = std::function<vector<bool>(vector<string>&, string)>;

/**
 * 1023. Camelcase Matching
 * https://leetcode.com/problems/camelcase-matching/
 * 
 * 判断 queries 中的每个字符串是否匹配 pattern
 * 匹配规则：可以在 pattern 中插入小写字母得到 query
 */
class CamelcaseMatchingSolution : public SolutionBase<Func> {
 public:
  vector<bool> camelMatch(vector<string>& queries, string pattern);

  CamelcaseMatchingSolution();
};

}  // namespace problem_1023
}  // namespace leetcode
