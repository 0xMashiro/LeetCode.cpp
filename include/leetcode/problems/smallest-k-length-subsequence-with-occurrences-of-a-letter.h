#include "leetcode/core.h"

namespace leetcode {
namespace problem_2030 {

using Func = std::function<string(string, int, char, int)>;

class SmallestKLengthSubsequenceWithOccurrencesOfALetterSolution : public SolutionBase<Func> {
 public:
  string smallestSubsequence(string s, int k, char letter, int repetition);
  SmallestKLengthSubsequenceWithOccurrencesOfALetterSolution();
};

}  // namespace problem_2030
}  // namespace leetcode
