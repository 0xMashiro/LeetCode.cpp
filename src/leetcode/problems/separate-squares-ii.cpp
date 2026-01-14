#include "leetcode/problems/separate-squares-ii.h"

namespace leetcode {
namespace problem_3454 {

namespace {

struct Event {
  long long y;
  int type;  // 1: start, -1: end
  int idx;
  bool operator<(const Event& other) const {
    if (y != other.y) return y < other.y;
    // 相同 y 时，先处理结束事件还是开始事件？
    // 区间计算使用前一个 y 到当前 y 的宽度，当前 y 上的事件不应该影响该区间。
    // 所以应该先计算区间，再处理事件。
    // 因此排序时类型不重要，但为了稳定性，可以按类型排序。
    // 但为了确保处理顺序，我们可以在主循环中先计算区间再处理事件。
    // 所以这里只需按 y 排序。
    return y < other.y;
  }
};

struct Interval {
  long long start_y;
  long long end_y;
  long double start_area;
  long double width;
};

class SegmentTree {
 private:
  struct Node {
    int cnt;
    long long len;  // 覆盖长度（原始坐标）
    int l, r;
  };
  vector<Node> tree_;
  const vector<long long>& xs_;

  void build(int idx, int l, int r) {
    tree_[idx].l = l;
    tree_[idx].r = r;
    tree_[idx].cnt = 0;
    tree_[idx].len = 0;
    if (l + 1 == r) return;
    int mid = (l + r) / 2;
    build(idx * 2, l, mid);
    build(idx * 2 + 1, mid, r);
  }

  void pushUp(int idx) {
    if (tree_[idx].cnt > 0) {
      tree_[idx].len = xs_[tree_[idx].r] - xs_[tree_[idx].l];
    } else {
      if (tree_[idx].l + 1 == tree_[idx].r) {
        tree_[idx].len = 0;
      } else {
        tree_[idx].len = tree_[idx * 2].len + tree_[idx * 2 + 1].len;
      }
    }
  }

  void update(int idx, int L, int R, int val) {
    if (L <= tree_[idx].l && tree_[idx].r <= R) {
      tree_[idx].cnt += val;
      pushUp(idx);
      return;
    }
    int mid = (tree_[idx].l + tree_[idx].r) / 2;
    if (L < mid) update(idx * 2, L, R, val);
    if (R > mid) update(idx * 2 + 1, L, R, val);
    pushUp(idx);
  }

 public:
  SegmentTree(const vector<long long>& xs) : xs_(xs) {
    int n = xs.size();
    tree_.resize(4 * n);
    build(1, 0, n - 1);
  }

  void add(long long x1, long long x2, int val) {
    int l = lower_bound(xs_.begin(), xs_.end(), x1) - xs_.begin();
    int r = lower_bound(xs_.begin(), xs_.end(), x2) - xs_.begin();
    if (l < r) {
      update(1, l, r, val);
    }
  }

  long double getLength() const { return static_cast<long double>(tree_[1].len); }
};

// 扫描线算法计算最小 y 使得上下面积相等
static double solution1(vector<vector<int>>& squares) {
  const int n = squares.size();
  if (n == 0) return 0.0;

  // 收集所有 x 坐标用于离散化
  vector<long long> xs;
  xs.reserve(2 * n);
  vector<Event> events;
  events.reserve(2 * n);
  for (int i = 0; i < n; ++i) {
    long long x = squares[i][0];
    long long y = squares[i][1];
    long long l = squares[i][2];
    xs.push_back(x);
    xs.push_back(x + l);
    events.push_back({y, 1, i});
    events.push_back({y + l, -1, i});
  }
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());

  sort(events.begin(), events.end(),
       [](const Event& a, const Event& b) { return a.y < b.y; });

  SegmentTree segTree(xs);

  vector<Interval> intervals;
  long double area = 0.0;
  long long prev_y = events[0].y;

  // 初始时没有正方形被激活
  // 遍历事件，计算每个区间面积
  for (const auto& ev : events) {
    long long curr_y = ev.y;
    if (curr_y > prev_y) {
      long double width = segTree.getLength();
      intervals.push_back({prev_y, curr_y, area, width});
      area += width * (curr_y - prev_y);
    }
    // 更新激活集合
    int idx = ev.idx;
    long long x = squares[idx][0];
    long long l = squares[idx][2];
    if (ev.type == 1) {
      segTree.add(x, x + l, 1);
    } else {
      segTree.add(x, x + l, -1);
    }
    prev_y = curr_y;
  }

  long double total_area = area;
  long double target = total_area / 2.0;

  // 处理目标面积为零的情况
  if (total_area == 0.0) {
    // 所有正方形面积为零（不可能，因为 l >= 1）
    return 0.0;
  }

  // 检查是否正好在某个事件点上
  // 我们已经记录了每个区间开始时的面积，但事件点处的面积是区间结束时的面积
  // 我们可以检查每个区间的起点和终点面积
  // 简单方法：遍历区间，检查 target 是否在区间内
  for (const auto& interval : intervals) {
    long double area_start = interval.start_area;
    long double area_end = area_start + interval.width * (interval.end_y - interval.start_y);
    if (area_start <= target && target <= area_end) {
      if (interval.width == 0.0) {
        // 宽度为零，区间内面积不变，如果 target 等于面积，则返回 start_y
        if (target == area_start) {
          return static_cast<double>(interval.start_y);
        }
        continue;
      }
      // 线性插值
      long double dy = (target - area_start) / interval.width;
      double result = static_cast<double>(interval.start_y) + static_cast<double>(dy);
      // 确保结果不小于 start_y，不大于 end_y（由于浮点误差可能越界）
      if (result < interval.start_y) result = static_cast<double>(interval.start_y);
      if (result > interval.end_y) result = static_cast<double>(interval.end_y);
      return result;
    }
  }

  // 如果 target 等于最后一个区间的结束面积（即 total_area），返回最后一个 y
  // 但 target 是 total_area/2，不可能等于 total_area（除非 total_area=0）
  // 如果 target 等于某个区间的结束面积，上述循环会捕获到（因为 area_end 包含端点）
  // 为了安全，返回 prev_y（最后一个事件点）
  return static_cast<double>(prev_y);
}

}  // namespace

SeparateSquaresIiSolution::SeparateSquaresIiSolution() {
  setMetaInfo({.id = 3454,
               .title = "Separate Squares II",
               .url = "https://leetcode.com/problems/separate-squares-ii/"});
  registerStrategy("Sweep Line + Segment Tree", solution1);
}

double SeparateSquaresIiSolution::separateSquares(vector<vector<int>>& squares) {
  return getSolution()(squares);
}

}  // namespace problem_3454
}  // namespace leetcode