#include "leetcode/problems/add-binary.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_67 {

class AddBinaryTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  AddBinarySolution solution;
};

TEST_P(AddBinaryTest, Example1) {
  string a = "11";
  string b = "1";
  string expected = "100";
  EXPECT_EQ(expected, solution.addBinary(a, b));
}

TEST_P(AddBinaryTest, Example2) {
  string a = "1010";
  string b = "1011";
  string expected = "10101";
  EXPECT_EQ(expected, solution.addBinary(a, b));
}

TEST_P(AddBinaryTest, SimpleCase) {
  string a = "0";
  string b = "0";
  string expected = "0";
  EXPECT_EQ(expected, solution.addBinary(a, b));
}

TEST_P(AddBinaryTest, DifferentLength) {
  string a = "1";
  string b = "111";
  string expected = "1000";
  EXPECT_EQ(expected, solution.addBinary(a, b));
}

TEST_P(AddBinaryTest, CarryPropagation) {
  string a = "111";
  string b = "111";
  string expected = "1110";
  EXPECT_EQ(expected, solution.addBinary(a, b));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, AddBinaryTest,
    ::testing::ValuesIn(AddBinarySolution().getStrategyNames()));

}  // namespace problem_67
}  // namespace leetcode
