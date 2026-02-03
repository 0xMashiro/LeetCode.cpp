#include "leetcode/problems/neighboring-bitwise-xor.h"

namespace leetcode {
namespace problem_2683 {

/**
 * Solution: Check if XOR of all elements in derived is 0
 *
 * Mathematical proof:
 * derived[0] = original[0] XOR original[1]
 * derived[1] = original[1] XOR original[2]
 * ...
 * derived[n-1] = original[n-1] XOR original[0]
 *
 * XOR all derived[i]:
 * = (original[0] XOR original[1]) XOR (original[1] XOR original[2]) XOR ... XOR (original[n-1] XOR original[0])
 * = original[0] XOR original[0] XOR original[1] XOR original[1] XOR ... XOR original[n-1] XOR original[n-1]
 * = 0 XOR 0 XOR ... XOR 0
 * = 0
 *
 * So a valid original exists iff XOR of all derived elements is 0.
 */
static bool solution1(vector<int>& derived) {
  int xor_sum = 0;
  for (int val : derived) {
    xor_sum ^= val;
  }
  return xor_sum == 0;
}

NeighboringBitwiseXorSolution::NeighboringBitwiseXorSolution() {
  setMetaInfo({.id = 2683,
               .title = "Neighboring Bitwise XOR",
               .url = "https://leetcode.com/problems/neighboring-bitwise-xor/"});
  registerStrategy("XOR Sum Check", solution1);
}

bool NeighboringBitwiseXorSolution::doesValidArrayExist(vector<int>& derived) {
  return getSolution()(derived);
}

}  // namespace problem_2683
}  // namespace leetcode
