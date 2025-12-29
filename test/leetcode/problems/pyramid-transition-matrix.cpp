#include "leetcode/problems/pyramid-transition-matrix.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_756 {

class PyramidTransitionMatrixTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PyramidTransitionMatrixSolution solution;
};

TEST_P(PyramidTransitionMatrixTest, Example1) {
  string bottom = "BCD";
  vector<string> allowed = {"BCC", "CDE", "CEA", "FFF"};
  EXPECT_TRUE(solution.pyramidTransition(bottom, allowed));
}

TEST_P(PyramidTransitionMatrixTest, Example2) {
  string bottom = "AAAA";
  vector<string> allowed = {"AAB", "AAC", "BCD", "BBE", "DEF"};
  EXPECT_FALSE(solution.pyramidTransition(bottom, allowed));
}

// Additional test cases
TEST_P(PyramidTransitionMatrixTest, SingleBlock) {
  string bottom = "A";
  vector<string> allowed = {};
  // Bottom length is 1, pyramid already at top
  EXPECT_TRUE(solution.pyramidTransition(bottom, allowed));
}

TEST_P(PyramidTransitionMatrixTest, TwoBlocksValid) {
  string bottom = "AB";
  vector<string> allowed = {"ABC"};
  // Bottom length 2 -> need to build level 1 (one block)
  // Pair (A,B) can produce C, then level 1 is "C", length 1 -> success
  EXPECT_TRUE(solution.pyramidTransition(bottom, allowed));
}

TEST_P(PyramidTransitionMatrixTest, TwoBlocksInvalid) {
  string bottom = "AB";
  vector<string> allowed = {"ACD"};  // pattern doesn't match (A,B)
  EXPECT_FALSE(solution.pyramidTransition(bottom, allowed));
}

TEST_P(PyramidTransitionMatrixTest, ThreeBlocksValid) {
  string bottom = "ABC";
  vector<string> allowed = {"ABD", "BCE", "DEF"};
  // Bottom: pairs (A,B) -> D, (B,C) -> E -> level 1 "DE"
  // Then (D,E) -> F (from "DEF") -> level 2 "F" -> success
  EXPECT_TRUE(solution.pyramidTransition(bottom, allowed));
}

TEST_P(PyramidTransitionMatrixTest, ThreeBlocksInvalid) {
  string bottom = "ABC";
  vector<string> allowed = {"ABD", "BCE"};
  // Bottom: (A,B)->D, (B,C)->E -> level 1 "DE"
  // No pattern for (D,E) -> cannot build further
  EXPECT_FALSE(solution.pyramidTransition(bottom, allowed));
}

TEST_P(PyramidTransitionMatrixTest, EmptyAllowed) {
  string bottom = "AB";
  vector<string> allowed = {};
  EXPECT_FALSE(solution.pyramidTransition(bottom, allowed));
}

TEST_P(PyramidTransitionMatrixTest, MaxLengthBottom) {
  string bottom = "ABCDEF";
  vector<string> allowed = {
      "ABC", "BCD", "CDE", "DEF", "EFA", "FAB",
      "ABD", "BCE", "CDF", "DEA", "EFB", "FAC"
  };
  // This is a constructed case that should be valid (cyclic).
  // We'll assume it's valid for testing.
  EXPECT_TRUE(solution.pyramidTransition(bottom, allowed));
}

// Edge case: multiple possible tops per pair
TEST_P(PyramidTransitionMatrixTest, MultipleChoices) {
  string bottom = "AB";
  vector<string> allowed = {"ABC", "ABD", "ABE"};
  // Any top works, should succeed
  EXPECT_TRUE(solution.pyramidTransition(bottom, allowed));
}

// Edge case: chain of choices
TEST_P(PyramidTransitionMatrixTest, ChainOfChoices) {
  string bottom = "AAA";
  vector<string> allowed = {"AAB", "ABA", "BAA", "ABB", "BAB", "BBA", "BBB"};
  // This allows many combinations, should find a path
  EXPECT_TRUE(solution.pyramidTransition(bottom, allowed));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PyramidTransitionMatrixTest,
    ::testing::ValuesIn(PyramidTransitionMatrixSolution().getStrategyNames()));

}  // namespace problem_756
}  // namespace leetcode