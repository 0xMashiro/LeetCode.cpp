#include "leetcode/core.h"

namespace leetcode {
namespace problem_519 {

/**
 * Random Flip Matrix 实现
 * 思路：使用哈希映射 + Fisher-Yates 洗牌算法的变种
 * - 将二维坐标 (i, j) 映射为一维索引 idx = i * n + j
 * - 维护剩余可选位置数 remaining
 * - 用哈希表记录被交换过的位置，实现 O(1) 的随机选择
 * 时间复杂度：flip O(1), reset O(1)
 * 空间复杂度：O(k)，k 为 flip 调用次数（最多 1000）
 */
class RandomFlipMatrix {
 public:
  RandomFlipMatrix(int m, int n);

  vector<int> flip();

  void reset();

 private:
  int m_;  // 行数
  int n_;  // 列数
  int remaining_;  // 剩余可选位置数
  unordered_map<int, int> map_;  // 索引映射表
};

}  // namespace problem_519
}  // namespace leetcode
