#include "leetcode/core.h"

namespace leetcode {
namespace problem_3093 {

using Func = std::function<vector<int>(vector<string>&, vector<string>&)>;

class LongestCommonSuffixQueriesSolution : public SolutionBase<Func> {
 public:
  vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery);

  LongestCommonSuffixQueriesSolution();
};

}  // namespace problem_3093
}  // namespace leetcode
