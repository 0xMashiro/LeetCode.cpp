
#include "leetcode/problems/convert-1d-array-into-2d-array.h"

namespace leetcode {
namespace problem_2022 {

// 直接转换法
// 时间复杂度: O(m*n), 空间复杂度: O(1)（不包括返回值）
static vector<vector<int>> solution1(vector<int>& original, int m, int n) {
  // 检查元素数量是否匹配
  if (m * n != static_cast<int>(original.size())) {
    return {};
  }
  
  vector<vector<int>> result(m, vector<int>(n));
  for (int i = 0; i < m * n; ++i) {
    result[i / n][i % n] = original[i];
  }
  return result;
}

Convert1dArrayInto2dArraySolution::Convert1dArrayInto2dArraySolution() {
  setMetaInfo({.id = 2022,
               .title = "Convert 1D Array Into 2D Array",
               .url = "https://leetcode.com/problems/convert-1d-array-into-2d-array/"});
  registerStrategy("Direct Conversion", solution1);
}

vector<vector<int>> Convert1dArrayInto2dArraySolution::construct2DArray(vector<int>& original, int m, int n) {
  return getSolution()(original, m, n);
}

}  // namespace problem_2022
}  // namespace leetcode
