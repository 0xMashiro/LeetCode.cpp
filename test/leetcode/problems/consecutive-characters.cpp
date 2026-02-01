#include "leetcode/problems/consecutive-characters.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1446 {

class ConsecutiveCharactersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConsecutiveCharactersSolution solution;
};

// 示例 1："leetcode" -> 2 ("ee")
TEST_P(ConsecutiveCharactersTest, Example1) {
  std::string s = "leetcode";
  EXPECT_EQ(2, solution.maxPower(s));
}

// 示例 2："abbcccddddeeeeedcba" -> 5 ("eeeee")
TEST_P(ConsecutiveCharactersTest, Example2) {
  std::string s = "abbcccddddeeeeedcba";
  EXPECT_EQ(5, solution.maxPower(s));
}

// 边界：单个字符
TEST_P(ConsecutiveCharactersTest, SingleCharacter) {
  std::string s = "a";
  EXPECT_EQ(1, solution.maxPower(s));
}

// 边界：全部相同字符
TEST_P(ConsecutiveCharactersTest, AllSame) {
  std::string s = "aaaaaa";
  EXPECT_EQ(6, solution.maxPower(s));
}

// 边界：全部不同字符
TEST_P(ConsecutiveCharactersTest, AllDifferent) {
  std::string s = "abcdef";
  EXPECT_EQ(1, solution.maxPower(s));
}

// 边界：连续字符在末尾
TEST_P(ConsecutiveCharactersTest, ConsecutiveAtEnd) {
  std::string s = "abccc";
  EXPECT_EQ(3, solution.maxPower(s));
}

// 边界：连续字符在开头
TEST_P(ConsecutiveCharactersTest, ConsecutiveAtStart) {
  std::string s = "aaabc";
  EXPECT_EQ(3, solution.maxPower(s));
}

// 边界：最大长度 500（上限）
TEST_P(ConsecutiveCharactersTest, MaxLength) {
  std::string s(500, 'a');
  EXPECT_EQ(500, solution.maxPower(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConsecutiveCharactersTest,
    ::testing::ValuesIn(ConsecutiveCharactersSolution().getStrategyNames()));

}  // namespace problem_1446
}  // namespace leetcode
