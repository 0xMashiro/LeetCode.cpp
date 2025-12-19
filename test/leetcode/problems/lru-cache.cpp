
#include "leetcode/problems/lru-cache.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_146 {

TEST(LeetCode, LruCacheTest) {
  LRUCache lRUCache = LRUCache(2);
  lRUCache.put(1, 1);  // cache is {1=1}
  lRUCache.put(2, 2);  // cache is {1=1, 2=2}
  EXPECT_EQ(lRUCache.get(1), 1);
  lRUCache.put(3, 3);  // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  EXPECT_EQ(lRUCache.get(2), -1);  // returns -1 (not found)
  lRUCache.put(4, 4);  // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  EXPECT_EQ(lRUCache.get(1), -1);  // return -1 (not found)
  EXPECT_EQ(lRUCache.get(3), 3);   // return 3
  EXPECT_EQ(lRUCache.get(4), 4);   // return 4
}

}  // namespace problem_146
}  // namespace leetcode
