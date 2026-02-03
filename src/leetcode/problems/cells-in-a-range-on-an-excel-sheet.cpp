#include "leetcode/problems/cells-in-a-range-on-an-excel-sheet.h"

namespace leetcode {
namespace problem_2194 {

// 直接模拟：遍历范围内的所有单元格
// 时间复杂度: O((c2-c1+1)*(r2-r1+1)), 空间复杂度: O(1)（不包括结果存储）
static vector<string> solution1(string s) {
  // 解析输入字符串，格式: "<col1><row1>:<col2><row2>"
  char col1 = s[0];
  char row1 = s[1];
  char col2 = s[3];
  char row2 = s[4];
  
  vector<string> result;
  // 按列优先遍历
  for (char c = col1; c <= col2; ++c) {
    for (char r = row1; r <= row2; ++r) {
      result.push_back(string(1, c) + string(1, r));
    }
  }
  
  return result;
}

CellsInARangeOnAnExcelSheetSolution::CellsInARangeOnAnExcelSheetSolution() {
  setMetaInfo({.id = 2194,
               .title = "Cells in a Range on an Excel Sheet",
               .url = "https://leetcode.com/problems/cells-in-a-range-on-an-excel-sheet/"});
  registerStrategy("Direct Simulation", solution1);
}

vector<string> CellsInARangeOnAnExcelSheetSolution::cellsInRange(string s) {
  return getSolution()(s);
}

}  // namespace problem_2194
}  // namespace leetcode
