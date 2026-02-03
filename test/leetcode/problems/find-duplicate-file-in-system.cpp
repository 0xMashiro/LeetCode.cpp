#include "leetcode/problems/find-duplicate-file-in-system.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_609 {

class FindDuplicateFileInSystemTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindDuplicateFileInSystemSolution solution;
};

TEST_P(FindDuplicateFileInSystemTest, Example1) {
  vector<string> paths = {"root/a 1.txt(abcd) 2.txt(efgh)",
                          "root/c 3.txt(abcd)",
                          "root/c/d 4.txt(efgh)",
                          "root 4.txt(efgh)"};
  vector<vector<string>> result = solution.findDuplicate(paths);
  
  // 对结果进行排序以便比较
  for (auto& group : result) {
    sort(group.begin(), group.end());
  }
  sort(result.begin(), result.end());
  
  // 按字典序排序后的 expected（基于每组第一个元素排序）
  // "root/4.txt" < "root/a/1.txt"
  vector<vector<string>> expected = {{"root/4.txt", "root/a/2.txt", "root/c/d/4.txt"},
                                     {"root/a/1.txt", "root/c/3.txt"}};
  EXPECT_EQ(expected, result);
}

TEST_P(FindDuplicateFileInSystemTest, Example2) {
  vector<string> paths = {"root/a 1.txt(abcd) 2.txt(efgh)",
                          "root/c 3.txt(abcd)",
                          "root/c/d 4.txt(efgh)"};
  vector<vector<string>> result = solution.findDuplicate(paths);
  
  // 对结果进行排序以便比较
  for (auto& group : result) {
    sort(group.begin(), group.end());
  }
  sort(result.begin(), result.end());
  
  // 按字典序排序后的 expected
  vector<vector<string>> expected = {{"root/a/1.txt", "root/c/3.txt"},
                                     {"root/a/2.txt", "root/c/d/4.txt"}};
  EXPECT_EQ(expected, result);
}

TEST_P(FindDuplicateFileInSystemTest, NoDuplicate) {
  vector<string> paths = {"root/a 1.txt(abcd)", "root/c 2.txt(efgh)"};
  vector<vector<string>> result = solution.findDuplicate(paths);
  
  vector<vector<string>> expected;
  EXPECT_EQ(expected, result);
}

TEST_P(FindDuplicateFileInSystemTest, SingleFile) {
  vector<string> paths = {"root/a 1.txt(abcd)"};
  vector<vector<string>> result = solution.findDuplicate(paths);
  
  vector<vector<string>> expected;
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindDuplicateFileInSystemTest,
    ::testing::ValuesIn(FindDuplicateFileInSystemSolution().getStrategyNames()));

}  // namespace problem_609
}  // namespace leetcode
