#include "leetcode/problems/throne-inheritance.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1600 {

TEST(ThroneInheritanceTest, Example1) {
  // 示例1测试
  ThroneInheritance t("king");
  t.birth("king", "andy");
  t.birth("king", "bob");
  t.birth("king", "catherine");
  t.birth("andy", "matthew");
  t.birth("bob", "alex");
  t.birth("bob", "asha");
  
  vector<string> expected1 = {"king", "andy", "matthew", "bob", "alex", "asha", "catherine"};
  EXPECT_EQ(t.getInheritanceOrder(), expected1);
  
  t.death("bob");
  
  vector<string> expected2 = {"king", "andy", "matthew", "alex", "asha", "catherine"};
  EXPECT_EQ(t.getInheritanceOrder(), expected2);
}

TEST(ThroneInheritanceTest, SingleKing) {
  // 只有国王的情况
  ThroneInheritance t("king");
  vector<string> expected = {"king"};
  EXPECT_EQ(t.getInheritanceOrder(), expected);
}

TEST(ThroneInheritanceTest, KingDeath) {
  // 国王死亡的情况
  ThroneInheritance t("king");
  t.birth("king", "alice");
  t.birth("king", "bob");
  t.death("king");
  
  vector<string> expected = {"alice", "bob"};
  EXPECT_EQ(t.getInheritanceOrder(), expected);
}

TEST(ThroneInheritanceTest, NoChildren) {
  // 没有子女的人出生
  ThroneInheritance t("king");
  t.birth("king", "alice");
  
  vector<string> expected = {"king", "alice"};
  EXPECT_EQ(t.getInheritanceOrder(), expected);
}

TEST(ThroneInheritanceTest, MultipleGenerations) {
  // 多代继承
  ThroneInheritance t("king");
  t.birth("king", "alice");
  t.birth("alice", "jack");
  t.birth("jack", "tom");
  
  vector<string> expected = {"king", "alice", "jack", "tom"};
  EXPECT_EQ(t.getInheritanceOrder(), expected);
}

TEST(ThroneInheritanceTest, LeafNodeDeath) {
  // 叶子节点死亡
  ThroneInheritance t("king");
  t.birth("king", "alice");
  t.birth("king", "bob");
  t.death("alice");
  
  vector<string> expected = {"king", "bob"};
  EXPECT_EQ(t.getInheritanceOrder(), expected);
}

}  // namespace problem_1600
}  // namespace leetcode
