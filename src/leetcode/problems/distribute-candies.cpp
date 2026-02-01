
#include "leetcode/problems/distribute-candies.h"

namespace leetcode {
namespace problem_575 {

// 哈希集合统计种类数
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<int>& candyType) {
  unordered_set<int> uniqueTypes(candyType.begin(), candyType.end());
  return min(uniqueTypes.size(), candyType.size() / 2);
}

DistributeCandiesSolution::DistributeCandiesSolution() {
  setMetaInfo({.id = 575,
               .title = "Distribute Candies",
               .url = "https://leetcode.com/problems/distribute-candies/"});
  registerStrategy("Hash Set", solution1);
}

int DistributeCandiesSolution::distributeCandies(vector<int>& candyType) {
  return getSolution()(candyType);
}

}  // namespace problem_575
}  // namespace leetcode
