#include "leetcode/problems/erect-the-fence.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_587 {

class ErectTheFenceTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ErectTheFenceSolution solution;
  
  // 辅助函数：对结果排序后比较（因为输出顺序可以任意）
  static vector<vector<int>> sortPoints(vector<vector<int>> points) {
    sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
      return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
    });
    return points;
  }
  
  // 辅助函数：检查两个点集是否相等（不考虑顺序）
  static bool equalPoints(vector<vector<int>> a, vector<vector<int>> b) {
    if (a.size() != b.size()) return false;
    a = sortPoints(a);
    b = sortPoints(b);
    return a == b;
  }
};

TEST_P(ErectTheFenceTest, Example1) {
  vector<vector<int>> trees = {{1, 1}, {2, 2}, {2, 0}, {2, 4}, {3, 3}, {4, 2}};
  vector<vector<int>> expected = {{1, 1}, {2, 0}, {4, 2}, {3, 3}, {2, 4}};
  vector<vector<int>> result = solution.outerTrees(trees);
  EXPECT_TRUE(equalPoints(result, expected));
}

TEST_P(ErectTheFenceTest, Example2) {
  vector<vector<int>> trees = {{1, 2}, {2, 2}, {4, 2}};
  vector<vector<int>> expected = {{1, 2}, {2, 2}, {4, 2}};
  vector<vector<int>> result = solution.outerTrees(trees);
  EXPECT_TRUE(equalPoints(result, expected));
}

TEST_P(ErectTheFenceTest, SinglePoint) {
  vector<vector<int>> trees = {{0, 0}};
  vector<vector<int>> expected = {{0, 0}};
  vector<vector<int>> result = solution.outerTrees(trees);
  EXPECT_TRUE(equalPoints(result, expected));
}

TEST_P(ErectTheFenceTest, TwoPoints) {
  vector<vector<int>> trees = {{0, 0}, {1, 1}};
  vector<vector<int>> expected = {{0, 0}, {1, 1}};
  vector<vector<int>> result = solution.outerTrees(trees);
  EXPECT_TRUE(equalPoints(result, expected));
}

TEST_P(ErectTheFenceTest, Square) {
  vector<vector<int>> trees = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
  vector<vector<int>> expected = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
  vector<vector<int>> result = solution.outerTrees(trees);
  EXPECT_TRUE(equalPoints(result, expected));
}

TEST_P(ErectTheFenceTest, CollinearAll) {
  // 所有点共线
  vector<vector<int>> trees = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
  vector<vector<int>> expected = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
  vector<vector<int>> result = solution.outerTrees(trees);
  EXPECT_TRUE(equalPoints(result, expected));
}

TEST_P(ErectTheFenceTest, CenterPoint) {
  // 中心点在凸包内部
  vector<vector<int>> trees = {{0, 0}, {0, 2}, {2, 0}, {2, 2}, {1, 1}};
  vector<vector<int>> expected = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
  vector<vector<int>> result = solution.outerTrees(trees);
  EXPECT_TRUE(equalPoints(result, expected));
}

TEST_P(ErectTheFenceTest, TriangleWithInsidePoint) {
  vector<vector<int>> trees = {{0, 0}, {0, 3}, {3, 0}, {1, 1}};
  vector<vector<int>> expected = {{0, 0}, {0, 3}, {3, 0}};
  vector<vector<int>> result = solution.outerTrees(trees);
  EXPECT_TRUE(equalPoints(result, expected));
}

TEST_P(ErectTheFenceTest, DuplicateLike) {
  // L形状的点
  vector<vector<int>> trees = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {2, 0}};
  vector<vector<int>> expected = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {2, 0}};
  vector<vector<int>> result = solution.outerTrees(trees);
  EXPECT_TRUE(equalPoints(result, expected));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ErectTheFenceTest,
    ::testing::ValuesIn(ErectTheFenceSolution().getStrategyNames()));

}  // namespace problem_587
}  // namespace leetcode
