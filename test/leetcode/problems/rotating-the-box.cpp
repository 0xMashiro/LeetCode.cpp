#include "leetcode/problems/rotating-the-box.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1861 {

class RotatingTheBoxTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RotatingTheBoxSolution solution;
};

TEST_P(RotatingTheBoxTest, Example1) {
  vector<vector<char>> boxGrid = {{'#', '.', '#'}};
  vector<vector<char>> expected = {
      {'.'},
      {'#'},
      {'#'}};
  EXPECT_EQ(expected, solution.rotateTheBox(boxGrid));
}

TEST_P(RotatingTheBoxTest, Example2) {
  vector<vector<char>> boxGrid = {
      {'#', '.', '*', '.'},
      {'#', '#', '*', '.'}};
  vector<vector<char>> expected = {
      {'#', '.'},
      {'#', '#'},
      {'*', '*'},
      {'.', '.'}};
  EXPECT_EQ(expected, solution.rotateTheBox(boxGrid));
}

TEST_P(RotatingTheBoxTest, Example3) {
  vector<vector<char>> boxGrid = {
      {'#', '#', '*', '.', '*', '.'},
      {'#', '#', '#', '*', '.', '.'},
      {'#', '#', '#', '.', '#', '.'}};
  vector<vector<char>> expected = {
      {'.', '#', '#'},
      {'.', '#', '#'},
      {'#', '#', '*'},
      {'#', '*', '.'},
      {'#', '.', '*'},
      {'#', '.', '.'}};
  EXPECT_EQ(expected, solution.rotateTheBox(boxGrid));
}

TEST_P(RotatingTheBoxTest, SelfAuthoredSingleRowNoObstacle) {
  // 单行无障碍物：石头全部落到最右边
  vector<vector<char>> boxGrid = {{'#', '.', '#', '.', '#'}};
  vector<vector<char>> expected = {
      {'.'},
      {'.'},
      {'#'},
      {'#'},
      {'#'}};
  EXPECT_EQ(expected, solution.rotateTheBox(boxGrid));
}

TEST_P(RotatingTheBoxTest, SelfAuthoredAllEmpty) {
  // 全空
  vector<vector<char>> boxGrid = {{'.', '.', '.'}, {'.', '.', '.'}};
  vector<vector<char>> expected = {
      {'.', '.'},
      {'.', '.'},
      {'.', '.'}};
  EXPECT_EQ(expected, solution.rotateTheBox(boxGrid));
}

TEST_P(RotatingTheBoxTest, SelfAuthoredAllObstacles) {
  // 全障碍物
  vector<vector<char>> boxGrid = {{'*', '*', '*'}};
  vector<vector<char>> expected = {
      {'*'},
      {'*'},
      {'*'}};
  EXPECT_EQ(expected, solution.rotateTheBox(boxGrid));
}

TEST_P(RotatingTheBoxTest, SelfAuthoredStoneBlockedByObstacle) {
  // 石头被障碍物挡住
  vector<vector<char>> boxGrid = {{'#', '#', '*', '#', '.'}};
  // 重力后: ['#', '#', '*', '#', '.'] -> 从右向左: writePos=4
  // j=4: '.' skip; j=3: '#' -> pos=4 '#'; writePos=3
  // j=2: '*' -> pos=2 '*'; writePos=1
  // j=1: '#' -> pos=1 '#'; writePos=0
  // j=0: '#' -> pos=0 '#'; writePos=-1
  // 重力后: ['#', '#', '*', '.', '#']
  // 旋转: 5x1 -> [[.],[.],[*],[#],[#]]? 
  // Wait, let me recalculate.
  // original: [#,#,*,.,.] after gravity: j=3 '#' at writePos=4 -> [.,.,*,.,#]; writePos=3
  // j=1 '#' at writePos=3 -> [.,.,*,.,#]; writePos=2. But pos 2 has '*', actually...
  // Let me redo carefully.
  // Input: [#, #, *, #, .]  (row 0)
  // gravityApplied row starts as [., ., ., ., .]
  // writePos = 4
  // j=4: '.' -> skip
  // j=3: '#' -> gravityApplied[0][4]='#', writePos=3
  // j=2: '*' -> gravityApplied[0][2]='*', writePos=1
  // j=1: '#' -> gravityApplied[0][1]='#', writePos=0
  // j=0: '#' -> gravityApplied[0][0]='#', writePos=-1
  // After gravity: [#, #, *, ., #]
  // Rotation: 5x1 => rows 0..4, col 0
  // (0,0)='#' -> (0, 1-1-0)=(0,0) -> [0][0]='#'
  // (0,1)='#' -> (1, 0) -> [1][0]='#'
  // (0,2)='*' -> (2, 0) -> [2][0]='*'
  // (0,3)='.' -> (3, 0) -> [3][0]='.'
  // (0,4)='#' -> (4, 0) -> [4][0]='#'
  // Result: [[#],[#],[*],[.],[#]]

  // Wait, this boxGrid has only 1 row and 5 cols. After rotation it's 5x1.
  vector<vector<char>> boxGrid2 = {{'#', '#', '*', '#', '.'}};
  vector<vector<char>> expected2 = {
      {'#'},
      {'#'},
      {'*'},
      {'.'},
      {'#'}};
  EXPECT_EQ(expected2, solution.rotateTheBox(boxGrid2));
}

TEST_P(RotatingTheBoxTest, SelfAuthoredSingleCell) {
  // 单元素
  vector<vector<char>> boxGrid = {{'#'}};
  vector<vector<char>> expected = {{'#'}};
  EXPECT_EQ(expected, solution.rotateTheBox(boxGrid));

  vector<vector<char>> boxGrid2 = {{'.'}};
  vector<vector<char>> expected2 = {{'.'}};
  EXPECT_EQ(expected2, solution.rotateTheBox(boxGrid2));

  vector<vector<char>> boxGrid3 = {{'*'}};
  vector<vector<char>> expected3 = {{'*'}};
  EXPECT_EQ(expected3, solution.rotateTheBox(boxGrid3));
}

TEST_P(RotatingTheBoxTest, SelfAuthoredSquare) {
  // 2x2 方形：石头重力+旋转
  vector<vector<char>> boxGrid = {
      {'#', '.'},
      {'.', '#'}};
  // Row 0: [#, .] -> gravity: [#, .] (writePos=1, j=1 '.' skip, j=0 '#' -> pos=1 '#', writePos=0)
  // Wait, that's wrong. Let me re-trace.
  // gravityApplied row 0 = [., .], writePos=1
  // j=1: '.' skip
  // j=0: '#' -> gravityApplied[0][1]='#', writePos=0
  // Row 0 after gravity: [., #]
  // Row 1: [., #] -> gravity: writePos=1
  // j=1: '#' -> gravityApplied[1][1]='#', writePos=0
  // j=0: '.' skip
  // Row 1 after gravity: [., #]
  // After gravity:
  // [[., #],
  //  [., #]]
  // Rotation 90°:
  // (0,0)='.' -> (0, 2-1-0)=(0,1) -> [0][1]='.'
  // (0,1)='#' -> (1, 1) -> [1][1]='#'
  // (1,0)='.' -> (0, 0) -> [0][0]='.'
  // (1,1)='#' -> (1, 0) -> [1][0]='#'
  // Result: [[., .], [#, #]]
  vector<vector<char>> expected = {
      {'.', '.'},
      {'#', '#'}};
  EXPECT_EQ(expected, solution.rotateTheBox(boxGrid));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RotatingTheBoxTest,
    ::testing::ValuesIn(RotatingTheBoxSolution().getStrategyNames()));

}  // namespace problem_1861
}  // namespace leetcode
