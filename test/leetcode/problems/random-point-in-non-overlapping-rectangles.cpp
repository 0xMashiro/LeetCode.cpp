#include "leetcode/problems/random-point-in-non-overlapping-rectangles.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_497 {

class RandomPointInNonOverlappingRectanglesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override {
    solution.setStrategy(GetParam());
  }

  RandomPointInNonOverlappingRectanglesSolution solution;
};

// 辅助函数：验证点是否在矩形内
bool isPointInRect(const vector<int>& point, const vector<int>& rect) {
  int px = point[0], py = point[1];
  int a = rect[0], b = rect[1], x = rect[2], y = rect[3];
  return px >= a && px <= x && py >= b && py <= y;
}

// 辅助函数：获取矩形的面积（点数）
long long getRectArea(const vector<int>& rect) {
  int a = rect[0], b = rect[1], x = rect[2], y = rect[3];
  return (long long)(x - a + 1) * (long long)(y - b + 1);
}

TEST_P(RandomPointInNonOverlappingRectanglesTest, Example1) {
  // 初始化两个矩形
  vector<vector<int>> rects = {{-2, -2, 1, 1}, {2, 2, 4, 6}};
  solution.init(rects);
  
  // 多次 pick 验证返回的点在有效范围内
  for (int i = 0; i < 100; ++i) {
    vector<int> point = solution.pick();
    
    // 验证点在某个矩形内
    bool inValidRect = false;
    for (const auto& rect : rects) {
      if (isPointInRect(point, rect)) {
        inValidRect = true;
        break;
      }
    }
    EXPECT_TRUE(inValidRect) << "Point [" << point[0] << ", " << point[1] << "] is not in any rectangle";
  }
}

TEST_P(RandomPointInNonOverlappingRectanglesTest, SingleRectangle) {
  // 单个矩形
  vector<vector<int>> rects = {{1, 1, 5, 5}};
  solution.init(rects);
  
  for (int i = 0; i < 50; ++i) {
    vector<int> point = solution.pick();
    EXPECT_TRUE(isPointInRect(point, rects[0]));
  }
}

TEST_P(RandomPointInNonOverlappingRectanglesTest, MultipleRectangles) {
  // 多个小矩形（每个都是单个点）
  vector<vector<int>> rects = {{0, 0, 0, 0}, {1, 1, 1, 1}, {2, 2, 2, 2}};
  solution.init(rects);
  
  for (int i = 0; i < 30; ++i) {
    vector<int> point = solution.pick();
    
    bool inValidRect = false;
    for (const auto& rect : rects) {
      if (isPointInRect(point, rect)) {
        inValidRect = true;
        break;
      }
    }
    EXPECT_TRUE(inValidRect);
  }
}

TEST_P(RandomPointInNonOverlappingRectanglesTest, LargeCoordinates) {
  // 大坐标范围
  vector<vector<int>> rects = {{-1000000000, -1000000000, -999999900, -999999900}};
  solution.init(rects);
  
  for (int i = 0; i < 20; ++i) {
    vector<int> point = solution.pick();
    EXPECT_TRUE(isPointInRect(point, rects[0]));
  }
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RandomPointInNonOverlappingRectanglesTest,
    ::testing::ValuesIn(RandomPointInNonOverlappingRectanglesSolution().getStrategyNames()));

}  // namespace problem_497
}  // namespace leetcode
