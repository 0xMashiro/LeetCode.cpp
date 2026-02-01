#include "leetcode/core.h"

namespace leetcode {
namespace problem_2942 {

using Func = std::function<vector<int>(vector<string>&, char)>;

class FindWordsContainingCharacterSolution : public SolutionBase<Func> {
 public:
  vector<int> findWordsContaining(vector<string>& words, char x);

  FindWordsContainingCharacterSolution();
};

}  // namespace problem_2942
}  // namespace leetcode