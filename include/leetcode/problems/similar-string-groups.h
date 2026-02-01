#include "leetcode/core.h"

namespace leetcode {
namespace problem_839 {

using Func = std::function<int(vector<string>&)>;

/**
 * 839. Similar String Groups
 * https://leetcode.com/problems/similar-string-groups/
 *
 * 判断两个字符串是否相似（相同或最多两处不同），使用并查集统计组数
 */
class SimilarStringGroupsSolution : public SolutionBase<Func> {
 public:
  //! 计算相似字符串组的数量
  int numSimilarGroups(vector<string>& strs);

  SimilarStringGroupsSolution();
};

}  // namespace problem_839
}  // namespace leetcode
