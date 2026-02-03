
#include "leetcode/problems/design-hashset.h"

namespace leetcode {
namespace problem_705 {

MyHashSet::MyHashSet() : buckets_(BUCKET_SIZE) {}

void MyHashSet::add(int key) {
  int idx = hash(key);
  auto& bucket = buckets_[idx];
  // 如果已存在，不重复添加
  for (int k : bucket) {
    if (k == key) return;
  }
  bucket.push_back(key);
}

void MyHashSet::remove(int key) {
  int idx = hash(key);
  auto& bucket = buckets_[idx];
  for (auto it = bucket.begin(); it != bucket.end(); ++it) {
    if (*it == key) {
      bucket.erase(it);
      return;
    }
  }
}

bool MyHashSet::contains(int key) {
  int idx = hash(key);
  auto& bucket = buckets_[idx];
  for (int k : bucket) {
    if (k == key) return true;
  }
  return false;
}

}  // namespace problem_705
}  // namespace leetcode
