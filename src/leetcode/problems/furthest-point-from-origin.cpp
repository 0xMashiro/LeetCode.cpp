#include "leetcode/problems/furthest-point-from-origin.h"

namespace leetcode {
namespace problem_2833 {

static int solution1(string& moves) {
  int countL = 0, countR = 0, countUnderscore = 0;
  for (char c : moves) {
    if (c == 'L') ++countL;
    else if (c == 'R') ++countR;
    else ++countUnderscore;  // c == '_'
  }
  // 最远距离 = |countL - countR| + countUnderscore
  return abs(countL - countR) + countUnderscore;
}

FurthestPointFromOriginSolution::FurthestPointFromOriginSolution() {
  setMetaInfo({.id = 2833,
               .title = "Furthest Point From Origin",
               .url = "https://leetcode.com/problems/furthest-point-from-origin"});
  registerStrategy("Count Absolute Diff", solution1);
}

int FurthestPointFromOriginSolution::furthestDistanceFromOrigin(string& moves) {
  return getSolution()(moves);
}

}  // namespace problem_2833
}  // namespace leetcode
