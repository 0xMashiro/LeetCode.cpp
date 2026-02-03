#include "leetcode/core.h"

namespace leetcode {
namespace problem_497 {

using Func = std::function<vector<int>()>;

class RandomPointInNonOverlappingRectanglesSolution : public SolutionBase<Func> {
 public:
  // 构造函数接收矩形数组进行初始化
  void init(const vector<vector<int>>& rects);
  
  RandomPointInNonOverlappingRectanglesSolution();

  vector<int> pick();

 protected:
  vector<vector<int>> rects_;       // 矩形数组
  vector<long long> prefix_sum_;    // 前缀和，记录到每个矩形为止的总点数
  long long total_points_;          // 总点数
};

}  // namespace problem_497
}  // namespace leetcode
