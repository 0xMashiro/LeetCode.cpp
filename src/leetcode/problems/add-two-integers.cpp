
#include "leetcode/problems/add-two-integers.h"

namespace leetcode {
namespace problem_2235 {

// 简单加法：直接返回两数之和
// 时间复杂度: O(1), 空间复杂度: O(1)
static int solution1(int num1, int num2) {
  return num1 + num2;
}

AddTwoIntegersSolution::AddTwoIntegersSolution() {
  setMetaInfo({.id = 2235,
               .title = "Add Two Integers",
               .url = "https://leetcode.com/problems/add-two-integers/"});
  registerStrategy("Simple Addition", solution1);
}

int AddTwoIntegersSolution::sum(int num1, int num2) {
  return getSolution()(num1, num2);
}

}  // namespace problem_2235
}  // namespace leetcode
