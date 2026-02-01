
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3813 {

using Func = std::function<int(std::string)>;

class VowelConsonantScoreSolution : public SolutionBase<Func> {
 public:
  //! 3813. Vowel-Consonant Score
  //! https://leetcode.com/problems/vowel-consonant-score/
  int vowelConsonantScore(std::string s);

  VowelConsonantScoreSolution();
};

}  // namespace problem_3813
}  // namespace leetcode
