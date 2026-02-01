#include "leetcode/core.h"

namespace leetcode {
namespace problem_1202 {

using Func = std::function<std::string(std::string&, std::vector<std::vector<int>>&)>;

/**
 * 1202. Smallest String With Swaps
 * https://leetcode.com/problems/smallest-string-with-swaps/
 * 
 * 给定字符串 s 和可交换的索引对 pairs，可以任意次数交换 pairs 中的索引对。
 * 返回能得到的字典序最小的字符串。
 * 
 * 思路：并查集
 * 1. 使用并查集找出所有连通分量（可以互相交换的索引）
 * 2. 对每个连通分量内的字符进行排序
 * 3. 将排序后的字符按索引顺序放回，得到最小字符串
 * 
 * 时间复杂度：O(n log n + m α(n))
 * 空间复杂度：O(n)
 */
class SmallestStringWithSwapsSolution : public SolutionBase<Func> {
 public:
  std::string smallestStringWithSwaps(std::string s, std::vector<std::vector<int>>& pairs);

  SmallestStringWithSwapsSolution();
};

}  // namespace problem_1202
}  // namespace leetcode
