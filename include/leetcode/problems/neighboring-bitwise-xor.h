#include "leetcode/core.h"

namespace leetcode {
namespace problem_2683 {

using Func = std::function<bool(vector<int>&)>;

/**
 * 2683. Neighboring Bitwise XOR
 * https://leetcode.com/problems/neighboring-bitwise-xor/
 *
 * Problem: Given derived array, determine if there exists a valid binary
 * original array such that derived[i] = original[i] XOR original[i+1]
 * (with circular condition: derived[n-1] = original[n-1] XOR original[0])
 *
 * Key Insight: XOR all elements of derived. Each original[i] appears exactly
 * twice in the expansion, and a XOR a = 0. So XOR of all derived must be 0.
 */
class NeighboringBitwiseXorSolution : public SolutionBase<Func> {
 public:
  bool doesValidArrayExist(vector<int>& derived);

  NeighboringBitwiseXorSolution();
};

}  // namespace problem_2683
}  // namespace leetcode
