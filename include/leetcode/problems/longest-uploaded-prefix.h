#include "leetcode/core.h"

namespace leetcode {
namespace problem_2424 {

/**
 * Longest Uploaded Prefix 实现
 * 
 * 思路：使用布尔数组记录每个视频的上传状态，维护一个指针表示当前最长前缀
 * - uploaded[i] 表示视频 i 是否已上传
 * - longest_prefix 表示当前最长已上传前缀的终点（即 1 到 longest_prefix 都已上传）
 * 
 * upload 操作：标记视频为已上传，然后尝试扩展 longest_prefix
 * longest 操作：直接返回 longest_prefix
 * 
 * 时间复杂度：upload 均摊 O(1)，longest O(1)
 * 空间复杂度：O(n)
 */
class LUPrefix {
 public:
  LUPrefix(int n);
  
  void upload(int video);
  
  int longest();

 private:
  std::vector<bool> uploaded_;  // 记录每个视频是否已上传，下标从 1 开始
  int longest_prefix_;          // 当前最长已上传前缀的终点
  int n_;                       // 视频总数
};

}  // namespace problem_2424
}  // namespace leetcode
