#include "leetcode/problems/random-flip-matrix.h"

namespace leetcode {
namespace problem_519 {

RandomFlipMatrix::RandomFlipMatrix(int m, int n) : m_(m), n_(n) {
  reset();
}

vector<int> RandomFlipMatrix::flip() {
  // 从 [0, remaining_) 中随机选一个数
  int r = rand() % remaining_;
  remaining_--;

  // 获取实际映射的索引：如果 r 在 map 中有映射，用映射值；否则用 r
  int idx = map_.count(r) ? map_[r] : r;

  // 将 remaining_ 位置的值放到 r 位置（交换思想）
  // 如果 remaining_ 有映射，用映射值；否则用 remaining_ 本身
  map_[r] = map_.count(remaining_) ? map_[remaining_] : remaining_;

  // 将一维索引转换为二维坐标
  return {idx / n_, idx % n_};
}

void RandomFlipMatrix::reset() {
  remaining_ = m_ * n_;
  map_.clear();
}

}  // namespace problem_519
}  // namespace leetcode
