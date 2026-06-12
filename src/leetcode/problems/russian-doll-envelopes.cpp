#include "leetcode/problems/russian-doll-envelopes.h"

#include <algorithm>
#include <vector>

namespace leetcode {
namespace problem_354 {

static int solution1(vector<vector<int>>& envelopes) {
  // Sort by width ascending, then by height descending when widths are equal
  sort(envelopes.begin(), envelopes.end(),
       [](const vector<int>& a, const vector<int>& b) {
         if (a[0] != b[0]) return a[0] < b[0];
         return a[1] > b[1];
       });

  // LIS on heights using patience sorting (O(n log n))
  vector<int> tails;
  for (const auto& env : envelopes) {
    int h = env[1];
    auto it = lower_bound(tails.begin(), tails.end(), h);
    if (it == tails.end()) {
      tails.push_back(h);
    } else {
      *it = h;
    }
  }
  return static_cast<int>(tails.size());
}

RussianDollEnvelopesSolution::RussianDollEnvelopesSolution() {
  setMetaInfo({
      .id = 354,
      .title = "Russian Doll Envelopes",
      .url = "https://leetcode.com/problems/russian-doll-envelopes"
  });
  registerStrategy({.name = "Patience Sorting LIS"}, solution1);
}

int RussianDollEnvelopesSolution::maxEnvelopes(vector<vector<int>>& envelopes) {
  return getSolution()(envelopes);
}

}  // namespace problem_354
}  // namespace leetcode
