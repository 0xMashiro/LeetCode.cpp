
#include "leetcode/problems/design-hashset.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_705 {

TEST(LeetCode, DesignHashsetExample1) {
  MyHashSet myHashSet;
  myHashSet.add(1);
  myHashSet.add(2);
  EXPECT_TRUE(myHashSet.contains(1));
  EXPECT_FALSE(myHashSet.contains(3));
  myHashSet.add(2);
  EXPECT_TRUE(myHashSet.contains(2));
  myHashSet.remove(2);
  EXPECT_FALSE(myHashSet.contains(2));
}

TEST(LeetCode, DesignHashsetEmptySet) {
  MyHashSet myHashSet;
  EXPECT_FALSE(myHashSet.contains(0));
  EXPECT_FALSE(myHashSet.contains(100));
  myHashSet.remove(1);
  EXPECT_FALSE(myHashSet.contains(1));
}

TEST(LeetCode, DesignHashsetSingleElement) {
  MyHashSet myHashSet;
  myHashSet.add(42);
  EXPECT_TRUE(myHashSet.contains(42));
  myHashSet.remove(42);
  EXPECT_FALSE(myHashSet.contains(42));
  myHashSet.remove(42);
  EXPECT_FALSE(myHashSet.contains(42));
}

TEST(LeetCode, DesignHashsetDuplicateAdd) {
  MyHashSet myHashSet;
  myHashSet.add(5);
  myHashSet.add(5);
  myHashSet.add(5);
  EXPECT_TRUE(myHashSet.contains(5));
  myHashSet.remove(5);
  EXPECT_FALSE(myHashSet.contains(5));
}

TEST(LeetCode, DesignHashsetBoundaryKeys) {
  MyHashSet myHashSet;
  myHashSet.add(0);
  myHashSet.add(1000000);
  EXPECT_TRUE(myHashSet.contains(0));
  EXPECT_TRUE(myHashSet.contains(1000000));
  myHashSet.remove(0);
  myHashSet.remove(1000000);
  EXPECT_FALSE(myHashSet.contains(0));
  EXPECT_FALSE(myHashSet.contains(1000000));
}

TEST(LeetCode, DesignHashsetMultipleOperations) {
  MyHashSet myHashSet;
  for (int i = 0; i < 100; i += 2) {
    myHashSet.add(i);
  }
  for (int i = 0; i < 100; i += 2) {
    EXPECT_TRUE(myHashSet.contains(i));
  }
  for (int i = 1; i < 100; i += 2) {
    EXPECT_FALSE(myHashSet.contains(i));
  }
  for (int i = 0; i < 50; i += 2) {
    myHashSet.remove(i);
  }
  for (int i = 0; i < 50; i += 2) {
    EXPECT_FALSE(myHashSet.contains(i));
  }
  for (int i = 50; i < 100; i += 2) {
    EXPECT_TRUE(myHashSet.contains(i));
  }
}

}  // namespace problem_705
}  // namespace leetcode
