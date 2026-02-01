#include "leetcode/problems/random-flip-matrix.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_519 {

TEST(LeetCode, RandomFlipMatrixTest) {
  RandomFlipMatrix solution(3, 1);

  // 第一次 flip，应该返回 [0,0], [1,0], [2,0] 中的一个
  auto result1 = solution.flip();
  EXPECT_EQ(2, result1.size());
  EXPECT_GE(result1[0], 0);
  EXPECT_LT(result1[0], 3);
  EXPECT_EQ(0, result1[1]);

  // 第二次 flip，返回剩下的两个之一
  auto result2 = solution.flip();
  EXPECT_EQ(2, result2.size());
  EXPECT_GE(result2[0], 0);
  EXPECT_LT(result2[0], 3);
  EXPECT_EQ(0, result2[1]);
  // 确保两次结果不同
  EXPECT_NE(result1, result2);

  // 第三次 flip，返回最后一个
  auto result3 = solution.flip();
  EXPECT_EQ(2, result3.size());
  EXPECT_GE(result3[0], 0);
  EXPECT_LT(result3[0], 3);
  EXPECT_EQ(0, result3[1]);
  // 确保三次结果都不同
  EXPECT_NE(result1, result3);
  EXPECT_NE(result2, result3);

  // reset 后重新 flip
  solution.reset();
  auto result4 = solution.flip();
  EXPECT_EQ(2, result4.size());
  EXPECT_GE(result4[0], 0);
  EXPECT_LT(result4[0], 3);
  EXPECT_EQ(0, result4[1]);
}

}  // namespace problem_519
}  // namespace leetcode
