#include "leetcode/problems/reformat-the-string.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1417 {

class ReformatTheStringTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ReformatTheStringSolution solution;
};

TEST_P(ReformatTheStringTest, Example1) {
  std::string s = "a0b1c2";
  std::string result = solution.reformat(s);
  // 验证结果长度正确
  EXPECT_EQ(result.size(), s.size());
  // 验证交替性：检查相邻字符类型不同
  for (size_t i = 1; i < result.size(); ++i) {
    bool prev_is_digit = isdigit(result[i-1]);
    bool curr_is_digit = isdigit(result[i]);
    EXPECT_NE(prev_is_digit, curr_is_digit) 
        << "Adjacent characters have same type at position " << i;
  }
}

TEST_P(ReformatTheStringTest, Example2) {
  std::string s = "leetcode";
  std::string result = solution.reformat(s);
  EXPECT_EQ(result, "");
}

TEST_P(ReformatTheStringTest, Example3) {
  std::string s = "1229857369";
  std::string result = solution.reformat(s);
  EXPECT_EQ(result, "");
}

TEST_P(ReformatTheStringTest, SingleLetter) {
  std::string s = "a";
  std::string result = solution.reformat(s);
  EXPECT_EQ(result, "a");
}

TEST_P(ReformatTheStringTest, SingleDigit) {
  std::string s = "1";
  std::string result = solution.reformat(s);
  EXPECT_EQ(result, "1");
}

TEST_P(ReformatTheStringTest, AlternatingEqual) {
  std::string s = "a1b2";
  std::string result = solution.reformat(s);
  EXPECT_EQ(result.size(), s.size());
  for (size_t i = 1; i < result.size(); ++i) {
    bool prev_is_digit = isdigit(result[i-1]);
    bool curr_is_digit = isdigit(result[i]);
    EXPECT_NE(prev_is_digit, curr_is_digit);
  }
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ReformatTheStringTest,
    ::testing::ValuesIn(ReformatTheStringSolution().getStrategyNames()));

}  // namespace problem_1417
}  // namespace leetcode
