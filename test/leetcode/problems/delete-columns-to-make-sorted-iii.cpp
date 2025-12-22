#include "leetcode/problems/delete-columns-to-make-sorted-iii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_960 {

class DeleteColumnsToMakeSortedIiiTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DeleteColumnsToMakeSortedIiiSolution solution;
};

TEST_P(DeleteColumnsToMakeSortedIiiTest, Example1) {
  vector<string> strs = {"babca", "bbazb"};
  int expected = 3;
  int result = solution.minDeletionSize(strs);
  EXPECT_EQ(expected, result);
}

TEST_P(DeleteColumnsToMakeSortedIiiTest, Example2) {
  vector<string> strs = {"edcba"};
  int expected = 4;
  int result = solution.minDeletionSize(strs);
  EXPECT_EQ(expected, result);
}

TEST_P(DeleteColumnsToMakeSortedIiiTest, Example3) {
  vector<string> strs = {"ghi", "def", "abc"};
  int expected = 0;
  int result = solution.minDeletionSize(strs);
  EXPECT_EQ(expected, result);
}

// 额外测试用例：已经排好序的情况
TEST_P(DeleteColumnsToMakeSortedIiiTest, AlreadySorted) {
  vector<string> strs = {"abc", "def", "ghi"};
  int expected = 0;
  int result = solution.minDeletionSize(strs);
  EXPECT_EQ(expected, result);
}

// 额外测试用例：所有列都需要删除的情况
TEST_P(DeleteColumnsToMakeSortedIiiTest, AllNeedDelete) {
  vector<string> strs = {"cba", "fed", "ihg"};
  int expected = 2;  // 只能保留一个字符，需要删除2列
  int result = solution.minDeletionSize(strs);
  EXPECT_EQ(expected, result);
}

// 额外测试用例：两行两列
TEST_P(DeleteColumnsToMakeSortedIiiTest, TwoByTwo) {
  vector<string> strs = {"ab", "ba"};
  // 列0: a,b；列1: b,a
  // 保留列0: "a","b" 已经排序？行1: "b" > "a"? 不对，需要每行内部排序。
  // 检查每行：行0: a <= b (true), 行1: b <= a (false) 所以列0不能保留？
  // 实际上我们需要找到最大的列子序列使得每行内部非递减。
  // 对于这个例子：只有列0或列1单独可以（长度1），所以max_len=1，删除列数=2-1=1
  int expected = 1;
  int result = solution.minDeletionSize(strs);
  EXPECT_EQ(expected, result);
}

// 额外测试用例：多行多列复杂情况
TEST_P(DeleteColumnsToMakeSortedIiiTest, ComplexCase) {
  vector<string> strs = {"cba", "dab", "efg"};
  // 分析：列0: c,d,e；列1: b,a,f；列2: a,b,g
  // 检查列对：
  // 列0->列1: c>b? false; 所以不能转移。
  // 列0->列2: c>a? true; false
  // 列1->列2: b>a? true; false (行2: f>g? false) 等等需要检查所有行
  // 直接相信算法
  // 预期结果？我们手动计算：可能保留列0和列2？检查行0: c<=a? false; 不行。
  // 保留列1和列2？行0: b<=a? false。
  // 所以最多保留1列，删除2列。
  int expected = 2;
  int result = solution.minDeletionSize(strs);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DeleteColumnsToMakeSortedIiiTest,
    ::testing::ValuesIn(DeleteColumnsToMakeSortedIiiSolution().getStrategyNames()));

}  // namespace problem_960
}  // namespace leetcode