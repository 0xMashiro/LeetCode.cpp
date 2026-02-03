
#include "leetcode/problems/mini-parser.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_385 {

TEST(MiniParserTest, Example1) {
  MiniParserSolution solution;
  string s = "324";
  NestedInteger result = solution.deserialize(s);
  EXPECT_TRUE(result.isInteger());
  EXPECT_EQ(result.getInteger(), 324);
}

TEST(MiniParserTest, Example2) {
  MiniParserSolution solution;
  string s = "[123,[456,[789]]]";
  NestedInteger result = solution.deserialize(s);
  
  EXPECT_FALSE(result.isInteger());
  const vector<NestedInteger>& list = result.getList();
  EXPECT_EQ(list.size(), 2);
  
  // First element: 123
  EXPECT_TRUE(list[0].isInteger());
  EXPECT_EQ(list[0].getInteger(), 123);
  
  // Second element: [456,[789]]
  EXPECT_FALSE(list[1].isInteger());
  const vector<NestedInteger>& sublist1 = list[1].getList();
  EXPECT_EQ(sublist1.size(), 2);
  
  // sublist1[0]: 456
  EXPECT_TRUE(sublist1[0].isInteger());
  EXPECT_EQ(sublist1[0].getInteger(), 456);
  
  // sublist1[1]: [789]
  EXPECT_FALSE(sublist1[1].isInteger());
  const vector<NestedInteger>& sublist2 = sublist1[1].getList();
  EXPECT_EQ(sublist2.size(), 1);
  EXPECT_TRUE(sublist2[0].isInteger());
  EXPECT_EQ(sublist2[0].getInteger(), 789);
}

TEST(MiniParserTest, EmptyList) {
  MiniParserSolution solution;
  string s = "[]";
  NestedInteger result = solution.deserialize(s);
  EXPECT_FALSE(result.isInteger());
  EXPECT_EQ(result.getList().size(), 0);
}

TEST(MiniParserTest, NegativeNumber) {
  MiniParserSolution solution;
  string s = "-123";
  NestedInteger result = solution.deserialize(s);
  EXPECT_TRUE(result.isInteger());
  EXPECT_EQ(result.getInteger(), -123);
}

TEST(MiniParserTest, NegativeInList) {
  MiniParserSolution solution;
  string s = "[-1,[-2,3]]";
  NestedInteger result = solution.deserialize(s);
  
  EXPECT_FALSE(result.isInteger());
  const vector<NestedInteger>& list = result.getList();
  EXPECT_EQ(list.size(), 2);
  
  EXPECT_TRUE(list[0].isInteger());
  EXPECT_EQ(list[0].getInteger(), -1);
  
  EXPECT_FALSE(list[1].isInteger());
  const vector<NestedInteger>& sublist = list[1].getList();
  EXPECT_EQ(sublist.size(), 2);
  EXPECT_TRUE(sublist[0].isInteger());
  EXPECT_EQ(sublist[0].getInteger(), -2);
  EXPECT_TRUE(sublist[1].isInteger());
  EXPECT_EQ(sublist[1].getInteger(), 3);
}

TEST(MiniParserTest, MultipleElements) {
  MiniParserSolution solution;
  string s = "[1,2,3,4]";
  NestedInteger result = solution.deserialize(s);
  
  EXPECT_FALSE(result.isInteger());
  const vector<NestedInteger>& list = result.getList();
  EXPECT_EQ(list.size(), 4);
  
  for (int i = 0; i < 4; i++) {
    EXPECT_TRUE(list[i].isInteger());
    EXPECT_EQ(list[i].getInteger(), i + 1);
  }
}

}  // namespace problem_385
}  // namespace leetcode
