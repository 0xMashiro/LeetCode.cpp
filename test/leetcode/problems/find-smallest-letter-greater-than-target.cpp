
#include "leetcode/problems/find-smallest-letter-greater-than-target.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_744 {

class FindSmallestLetterGreaterThanTargetTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindSmallestLetterGreaterThanTargetSolution solution;
};

TEST_P(FindSmallestLetterGreaterThanTargetTest, Example1) {
  std::vector<char> letters = {'c', 'f', 'j'};
  char target = 'a';
  char expected = 'c';
  char result = solution.nextGreatestLetter(letters, target);
  EXPECT_EQ(expected, result);
}

TEST_P(FindSmallestLetterGreaterThanTargetTest, Example2) {
  std::vector<char> letters = {'c', 'f', 'j'};
  char target = 'c';
  char expected = 'f';
  char result = solution.nextGreatestLetter(letters, target);
  EXPECT_EQ(expected, result);
}

TEST_P(FindSmallestLetterGreaterThanTargetTest, Example3) {
  std::vector<char> letters = {'x', 'x', 'y', 'y'};
  char target = 'z';
  char expected = 'x';
  char result = solution.nextGreatestLetter(letters, target);
  EXPECT_EQ(expected, result);
}

// 补充测试用例
TEST_P(FindSmallestLetterGreaterThanTargetTest, AllSameLetters) {
  std::vector<char> letters = {'a', 'a', 'a', 'a'};
  char target = 'a';
  char expected = 'a';  // 没有大于'a'的字符，返回第一个字符
  char result = solution.nextGreatestLetter(letters, target);
  EXPECT_EQ(expected, result);
}

TEST_P(FindSmallestLetterGreaterThanTargetTest, TargetLessThanAll) {
  std::vector<char> letters = {'c', 'f', 'j'};
  char target = 'b';
  char expected = 'c';
  char result = solution.nextGreatestLetter(letters, target);
  EXPECT_EQ(expected, result);
}

TEST_P(FindSmallestLetterGreaterThanTargetTest, TargetGreaterThanAll) {
  std::vector<char> letters = {'a', 'b', 'c'};
  char target = 'z';
  char expected = 'a';
  char result = solution.nextGreatestLetter(letters, target);
  EXPECT_EQ(expected, result);
}

TEST_P(FindSmallestLetterGreaterThanTargetTest, TargetBetweenLetters) {
  std::vector<char> letters = {'a', 'c', 'e', 'g'};
  char target = 'd';
  char expected = 'e';
  char result = solution.nextGreatestLetter(letters, target);
  EXPECT_EQ(expected, result);
}

TEST_P(FindSmallestLetterGreaterThanTargetTest, DuplicateLetters) {
  std::vector<char> letters = {'a', 'b', 'b', 'b', 'c'};
  char target = 'b';
  char expected = 'c';
  char result = solution.nextGreatestLetter(letters, target);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindSmallestLetterGreaterThanTargetTest,
    ::testing::ValuesIn(FindSmallestLetterGreaterThanTargetSolution().getStrategyNames()));

}  // namespace problem_744
}  // namespace leetcode