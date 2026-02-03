#include "leetcode/problems/random-point-in-non-overlapping-rectangles.h"

namespace leetcode {
namespace problem_497 {

void RandomPointInNonOverlappingRectanglesSolution::init(const vector<vector<int>>& rects) {
  rects_ = rects;
  prefix_sum_.clear();
  total_points_ = 0;
  
  // 计算每个矩形的面积（点数）并构建前缀和数组
  for (const auto& rect : rects) {
    int a = rect[0], b = rect[1], x = rect[2], y = rect[3];
    // 矩形包含的点数 = (x - a + 1) * (y - b + 1)
    long long width = x - a + 1;
    long long height = y - b + 1;
    total_points_ += width * height;
    prefix_sum_.push_back(total_points_);
  }
}

RandomPointInNonOverlappingRectanglesSolution::RandomPointInNonOverlappingRectanglesSolution() {
  setMetaInfo({
    .id = 497,
    .title = "Random Point in Non-overlapping Rectangles",
    .url = "https://leetcode.com/problems/random-point-in-non-overlapping-rectangles/"
  });

  // 策略：前缀和 + 二分查找
  registerStrategy("Prefix Sum + Binary Search", [this]() {
    // 生成 [0, total_points_ - 1] 范围内的随机数
    long long target = rand() % total_points_;

    // 二分查找找到对应的矩形
    int left = 0, right = prefix_sum_.size() - 1;
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (prefix_sum_[mid] <= target) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    // 找到矩形索引
    int rect_idx = left;

    // 计算在矩形内的偏移量
    long long prev_sum = (rect_idx == 0) ? 0 : prefix_sum_[rect_idx - 1];
    long long offset = target - prev_sum;

    // 获取矩形信息
    const auto& rect = rects_[rect_idx];
    int a = rect[0], b = rect[1];
    int x = rect[2], y = rect[3];

    // 矩形的宽和高（包含边界）
    int width = x - a + 1;
    int height = y - b + 1;

    // 在矩形内生成随机点
    int dx = offset % width;
    int dy = offset / width;

    return vector<int>{a + dx, b + dy};
  });
}

vector<int> RandomPointInNonOverlappingRectanglesSolution::pick() {
  return getSolution()();
}

}  // namespace problem_497
}  // namespace leetcode
