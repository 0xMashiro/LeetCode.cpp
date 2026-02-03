#include "leetcode/core.h"

namespace leetcode {
namespace problem_3006 {

using Func = std::function<vector<int>(string, string, string, int)>;

class FindBeautifulIndicesInTheGivenArrayISolution : public SolutionBase<Func> {
 public:
  vector<int> beautifulIndices(string s, string a, string b, int k);

  FindBeautifulIndicesInTheGivenArrayISolution();
};

}  // namespace problem_3006
}  // namespace leetcode
