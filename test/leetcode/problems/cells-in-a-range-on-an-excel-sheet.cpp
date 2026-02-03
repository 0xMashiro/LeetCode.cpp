#include "leetcode/problems/cells-in-a-range-on-an-excel-sheet.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2194 {

class CellsInARangeOnAnExcelSheetTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CellsInARangeOnAnExcelSheetSolution solution;
};

TEST_P(CellsInARangeOnAnExcelSheetTest, Example1) {
  string s = "K1:L2";
  vector<string> expected = {"K1", "K2", "L1", "L2"};
  EXPECT_EQ(expected, solution.cellsInRange(s));
}

TEST_P(CellsInARangeOnAnExcelSheetTest, Example2) {
  string s = "A1:F1";
  vector<string> expected = {"A1", "B1", "C1", "D1", "E1", "F1"};
  EXPECT_EQ(expected, solution.cellsInRange(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CellsInARangeOnAnExcelSheetTest,
    ::testing::ValuesIn(CellsInARangeOnAnExcelSheetSolution().getStrategyNames()));

}  // namespace problem_2194
}  // namespace leetcode
