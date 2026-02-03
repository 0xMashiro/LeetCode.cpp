#include "leetcode/problems/number-of-rectangles-that-can-form-the-largest-square.h"

namespace leetcode {
namespace problem_1725 {

// 单次遍历：先找最大边长，再统计个数
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(vector<vector<int>>& rectangles) {
  int maxLen = 0;
  int count = 0;
  
  for (const auto& rect : rectangles) {
    int side = min(rect[0], rect[1]);
    if (side > maxLen) {
      maxLen = side;
      count = 1;
    } else if (side == maxLen) {
      count++;
    }
  }
  
  return count;
}

NumberOfRectanglesThatCanFormTheLargestSquareSolution::NumberOfRectanglesThatCanFormTheLargestSquareSolution() {
  setMetaInfo({.id = 1725,
               .title = "Number Of Rectangles That Can Form The Largest Square",
               .url = "https://leetcode.com/problems/number-of-rectangles-that-can-form-the-largest-square/"});
  registerStrategy("One Pass", solution1);
}

int NumberOfRectanglesThatCanFormTheLargestSquareSolution::countGoodRectangles(vector<vector<int>>& rectangles) {
  return getSolution()(rectangles);
}

}  // namespace problem_1725
}  // namespace leetcode
