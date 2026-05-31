#include "leetcode/problems/destroying-asteroids.h"

namespace leetcode {
namespace problem_2126 {

// 排序 + 贪心：从小到大排序，依次碰撞最小的 asteroid
// 如果当前行星质量 >= asteroid，则吸收质量继续；否则返回 false
// 时间复杂度: O(n log n)，空间复杂度: O(1)（原地排序）
// 注意：累加质量可能超过 32-bit int，需用 long long
static bool solution1(int mass, std::vector<int>& asteroids) {
  std::sort(asteroids.begin(), asteroids.end());
  long long cur = mass;
  for (int a : asteroids) {
    if (cur < a) {
      return false;
    }
    cur += a;
  }
  return true;
}

DestroyingAsteroidsSolution::DestroyingAsteroidsSolution() {
  setMetaInfo({.id = 2126,
               .title = "Destroying Asteroids",
               .url = "https://leetcode.com/problems/destroying-asteroids/"});
  registerStrategy("Sorting + Greedy", solution1);
}

bool DestroyingAsteroidsSolution::asteroidsDestroyed(int mass, std::vector<int>& asteroids) {
  return getSolution()(mass, asteroids);
}

}  // namespace problem_2126
}  // namespace leetcode
