
#include "leetcode/core.h"

namespace leetcode {
namespace problem_705 {

/**
 * Design HashSet 实现
 * 思路：使用分离链接法（Separate Chaining），使用标准库容器
 * - vector<list<int>> 存储桶，每个桶是一个链表
 * - 哈希函数：key % bucket_size
 * - 利用标准库的 list 操作简化代码
 * 时间复杂度：平均 O(1)，最坏 O(n)
 * 空间复杂度：O(n)
 */
class MyHashSet {
 public:
  MyHashSet();

  void add(int key);

  void remove(int key);

  bool contains(int key);

 private:
  static constexpr int BUCKET_SIZE = 1009;

  std::vector<std::list<int>> buckets_;

  int hash(int key) const { return key % BUCKET_SIZE; }
};

}  // namespace problem_705
}  // namespace leetcode
