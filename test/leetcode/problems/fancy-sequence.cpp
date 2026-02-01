#include "leetcode/problems/fancy-sequence.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1622 {

TEST(LeetCode, FancySequenceExample1) {
  Fancy fancy;
  fancy.append(2);   // fancy sequence: [2]
  fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
  fancy.append(7);   // fancy sequence: [5, 7]
  fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]
  EXPECT_EQ(fancy.getIndex(0), 10);  // return 10
  fancy.addAll(3);   // fancy sequence: [10+3, 14+3] -> [13, 17]
  fancy.append(10);  // fancy sequence: [13, 17, 10]
  fancy.multAll(2);  // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]
  EXPECT_EQ(fancy.getIndex(0), 26);  // return 26
  EXPECT_EQ(fancy.getIndex(1), 34);  // return 34
  EXPECT_EQ(fancy.getIndex(2), 20);  // return 20
}

TEST(LeetCode, FancySequenceEmpty) {
  Fancy fancy;
  EXPECT_EQ(fancy.getIndex(0), -1);  // empty sequence
}

TEST(LeetCode, FancySequenceSingleElement) {
  Fancy fancy;
  fancy.append(5);
  EXPECT_EQ(fancy.getIndex(0), 5);
  fancy.addAll(3);
  EXPECT_EQ(fancy.getIndex(0), 8);
  fancy.multAll(2);
  EXPECT_EQ(fancy.getIndex(0), 16);
}

TEST(LeetCode, FancySequenceOutOfBounds) {
  Fancy fancy;
  fancy.append(1);
  fancy.append(2);
  EXPECT_EQ(fancy.getIndex(2), -1);   // out of bounds
  EXPECT_EQ(fancy.getIndex(100), -1); // out of bounds
  EXPECT_EQ(fancy.getIndex(-1), -1);  // out of bounds
}

TEST(LeetCode, FancySequenceOnlyAddAll) {
  Fancy fancy;
  fancy.append(1);
  fancy.append(2);
  fancy.append(3);
  fancy.addAll(5);
  EXPECT_EQ(fancy.getIndex(0), 6);
  EXPECT_EQ(fancy.getIndex(1), 7);
  EXPECT_EQ(fancy.getIndex(2), 8);
}

TEST(LeetCode, FancySequenceOnlyMultAll) {
  Fancy fancy;
  fancy.append(2);
  fancy.append(3);
  fancy.multAll(3);
  EXPECT_EQ(fancy.getIndex(0), 6);
  EXPECT_EQ(fancy.getIndex(1), 9);
}

TEST(LeetCode, FancySequenceMixedOperations) {
  Fancy fancy;
  fancy.append(1);
  fancy.addAll(2);    // [3]
  fancy.multAll(3);   // [9]
  fancy.append(4);    // [9, 4]
  fancy.addAll(1);    // [10, 5]
  fancy.multAll(2);   // [20, 10]
  
  EXPECT_EQ(fancy.getIndex(0), 20);
  EXPECT_EQ(fancy.getIndex(1), 10);
}

TEST(LeetCode, FancySequenceLargeModulo) {
  const int MOD = 1000000007;
  Fancy fancy;
  fancy.append(MOD - 1);  // -1 mod MOD
  fancy.addAll(1);        // should become 0
  EXPECT_EQ(fancy.getIndex(0), 0);
}

TEST(LeetCode, FancySequenceMultipleAppend) {
  Fancy fancy;
  fancy.append(1);
  fancy.addAll(1);   // [2]
  fancy.append(2);   // [2, 2] (2 is appended with current lazy values)
  fancy.addAll(1);   // [3, 3]
  
  EXPECT_EQ(fancy.getIndex(0), 3);
  EXPECT_EQ(fancy.getIndex(1), 3);
}

}  // namespace problem_1622
}  // namespace leetcode
