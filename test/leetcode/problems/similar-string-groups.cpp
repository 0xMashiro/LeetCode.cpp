#include "leetcode/problems/similar-string-groups.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_839 {

class SimilarStringGroupsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SimilarStringGroupsSolution solution;
};

TEST_P(SimilarStringGroupsTest, Example1) {
  // Example 1: tars, rats, arts, star
  // Groups: {tars, rats, arts}, {star}
  vector<string> strs = {"tars", "rats", "arts", "star"};
  EXPECT_EQ(solution.numSimilarGroups(strs), 2);
}

TEST_P(SimilarStringGroupsTest, Example2) {
  // Example 2: omv, ovm
  // Similar by swapping positions 1 and 2
  vector<string> strs = {"omv", "ovm"};
  EXPECT_EQ(solution.numSimilarGroups(strs), 1);
}

TEST_P(SimilarStringGroupsTest, SingleString) {
  // Boundary: single string, one group
  vector<string> strs = {"abc"};
  EXPECT_EQ(solution.numSimilarGroups(strs), 1);
}

TEST_P(SimilarStringGroupsTest, AllIdentical) {
  // All strings are identical
  vector<string> strs = {"abc", "abc", "abc"};
  EXPECT_EQ(solution.numSimilarGroups(strs), 1);
}

TEST_P(SimilarStringGroupsTest, ConnectedViaChain) {
  // Strings connected via chain: abc ~ acb ~ bca
  // abc vs acb: diff at pos 1,2 -> similar
  // acb vs bca: diff at pos 0,2 -> similar (a vs b, c vs c, b vs a)
  // All three are in one group via transitive property
  vector<string> strs = {"abc", "acb", "bca"};
  EXPECT_EQ(solution.numSimilarGroups(strs), 1);
}

TEST_P(SimilarStringGroupsTest, LongStrings) {
  // Test with longer strings
  // abcdef ~ abcedf (diff at pos 3,4) -> similar
  // abcedf ~ abcfde (diff at pos 4,5: d vs f, f vs e... wait let me recalculate)
  // Actually: abcedf vs abcfde
  // pos 0: a=a, 1: b=b, 2: c=c, 3: e vs f, 4: d vs d, 5: f vs e
  // diff at pos 3 and 5 -> 2 differences -> similar
  // So all three are connected: abcdef ~ abcedf ~ abcfde
  vector<string> strs = {"abcdef", "abcedf", "abcfde"};
  EXPECT_EQ(solution.numSimilarGroups(strs), 1);
}

TEST_P(SimilarStringGroupsTest, ThreeCharsPermutations) {
  // Test with 3 character strings - all permutations of "abc"
  // abc ~ acb (swap pos 1,2)
  // abc ~ bac (swap pos 0,1)
  // All permutations are connected via chains
  vector<string> strs = {"abc", "acb", "bac", "bca", "cab", "cba"};
  EXPECT_EQ(solution.numSimilarGroups(strs), 1);
}

TEST_P(SimilarStringGroupsTest, TwoCharStrings) {
  // With 2 chars, any two different anagrams differ at exactly 2 positions
  // So they are always similar
  vector<string> strs = {"ab", "ba"};
  EXPECT_EQ(solution.numSimilarGroups(strs), 1);
}

TEST_P(SimilarStringGroupsTest, TwoIndependentGroups) {
  // Two independent groups that cannot be connected
  // Group 1: {tars, rats, arts} 
  // Group 2: {star} - star is not similar to any in group 1
  // Wait, actually need to verify this...
  // tars vs star: t vs s, a vs t, r vs a, s vs r -> 4 differences
  // rats vs star: r vs s, a vs t, t vs a, s vs r -> 4 differences
  // arts vs star: a vs s, r vs t, t vs a, s vs r -> 4 differences
  // So yes, star is isolated from the other group
  // But we need multiple independent groups in one test
  // This is tricky since all must be anagrams of each other
  // So all strings must have the same character counts
  // Let's use "tars", "rats", "arts", "star" which is already in Example1
  vector<string> strs = {"tars", "rats", "arts", "star"};
  EXPECT_EQ(solution.numSimilarGroups(strs), 2);
}

TEST_P(SimilarStringGroupsTest, FourCharTwoGroups) {
  // Create two groups of 4-char strings that are not connected
  // Both must be anagrams of each other
  // First group: abcd permutations that are similar-connected
  // Second group: the same abcd permutations but not connected to first
  // This is impossible because if they're all permutations of abcd, 
  // they may be connected via chains
  
  // Alternative: just test with more strings in example 1 style
  // tars group + additional similar strings
  vector<string> strs = {"tars", "rats", "arts", "star", "tsar"};
  // Check if tsar connects:
  // tsar vs tars: s vs a, a vs r, r vs s -> diff at 1,2,3 = 3 -> not similar
  // tsar vs rats: t vs r, s vs a, a vs t, r vs s -> 4 diff
  // tsar vs arts: t vs a, s vs r, a vs t, r vs s -> 4 diff
  // tsar vs star: t vs s, s vs t, a vs a, r vs r -> diff at 0,1 = 2 -> similar
  // So star and tsar form a group, still 2 groups total
  EXPECT_EQ(solution.numSimilarGroups(strs), 2);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SimilarStringGroupsTest,
    ::testing::ValuesIn(SimilarStringGroupsSolution().getStrategyNames()));

}  // namespace problem_839
}  // namespace leetcode
