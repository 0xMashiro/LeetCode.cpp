
#include "leetcode/core.h"

namespace leetcode {
namespace problem_146 {

/**
 * LRU Cache 实现
 * 思路：使用双向链表（std::list）维护访问顺序，哈希表（std::unordered_map）实现
 * O(1) 查找
 * - 链表头部存储最近使用的元素，尾部存储最久未使用的元素
 * - 哈希表存储 key 到链表迭代器的映射，实现快速定位
 * 时间复杂度：get 和 put 均为 O(1)
 * 空间复杂度：O(capacity)
 */
class LRUCache {
 public:
  LRUCache(int capacity) : capacity_(capacity) {}

  int get(int key);

  void put(int key, int value);

 private:
  using KV = pair<int, int>;
  int capacity_;
  list<KV> cache_;  // {key, value} 的列表，头部是最新的
  unordered_map<int, list<KV>::iterator> hash_;  // key -> 迭代器
};

}  // namespace problem_146
}  // namespace leetcode
