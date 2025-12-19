
#include "leetcode/problems/lru-cache.h"

namespace leetcode {
namespace problem_146 {

int LRUCache::get(int key) {
  if (hash_.find(key) == hash_.end()) return -1;
  auto it = hash_[key];
  int value = it->second;
  cache_.erase(it);
  cache_.push_front({key, value});
  hash_[key] = cache_.begin();
  return value;
}

void LRUCache::put(int key, int value) {
  if (hash_.find(key) != hash_.end()) {
    auto it = hash_[key];
    cache_.erase(it);
    cache_.push_front({key, value});
    hash_[key] = cache_.begin();
  } else {
    if (cache_.size() == capacity_) {
      hash_.erase(cache_.back().first);
      cache_.pop_back();
    }
    cache_.push_front({key, value});
    hash_[key] = cache_.begin();
  }
}

}  // namespace problem_146
}  // namespace leetcode
