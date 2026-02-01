#include "leetcode/core.h"

namespace leetcode {
namespace problem_3433 {

using Func = std::function<vector<int>(int, vector<vector<string>>&)>;

class CountMentionsPerUserSolution : public SolutionBase<Func> {
 public:
  vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events);

  CountMentionsPerUserSolution();
};

}  // namespace problem_3433
}  // namespace leetcode
