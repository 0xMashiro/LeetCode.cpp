#include "leetcode/core.h"

namespace leetcode {
namespace problem_916 {

using Func = std::function<vector<string>(vector<string>&, vector<string>&)>;

class WordSubsetsSolution : public SolutionBase<Func> {
 public:
  vector<string> wordSubsets(vector<string>& words1, vector<string>& words2);

  WordSubsetsSolution();
};

}  // namespace problem_916
}  // namespace leetcode
