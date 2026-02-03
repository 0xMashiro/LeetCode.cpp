#include "leetcode/problems/longest-uploaded-prefix.h"

namespace leetcode {
namespace problem_2424 {

LUPrefix::LUPrefix(int n) : n_(n), longest_prefix_(0) {
  uploaded_.resize(n + 1, false);  // 下标 0 不使用，使用 1 到 n
}

void LUPrefix::upload(int video) {
  // 标记该视频为已上传
  uploaded_[video] = true;
  
  // 尝试扩展最长前缀：如果当前 longest_prefix_ 的下一个视频已上传，就不断扩展
  while (longest_prefix_ < n_ && uploaded_[longest_prefix_ + 1]) {
    ++longest_prefix_;
  }
}

int LUPrefix::longest() {
  return longest_prefix_;
}

}  // namespace problem_2424
}  // namespace leetcode
