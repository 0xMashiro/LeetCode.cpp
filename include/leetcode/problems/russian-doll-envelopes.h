#include "leetcode/core.h"

namespace leetcode {
namespace problem_354 {

using Func = std::function<int(vector<vector<int>>&)>;

class RussianDollEnvelopesSolution : public SolutionBase<Func> {
 public:
  //! 354. Russian Doll Envelopes
  //! https://leetcode.com/problems/russian-doll-envelopes/
  int maxEnvelopes(vector<vector<int>>& envelopes);

  RussianDollEnvelopesSolution();
};

}  // namespace problem_354
}  // namespace leetcode
