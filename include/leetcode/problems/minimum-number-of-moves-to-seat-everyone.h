#include "leetcode/core.h"

namespace leetcode {
namespace problem_2037 {

using Func = std::function<int(vector<int>&, vector<int>&)>;

/**
 * 2037. Minimum Number of Moves to Seat Everyone
 * https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/
 * 
 * 给定 n 个座位和 n 个学生的位置，计算将每个学生分配到一个座位的最小移动次数。
 * 每次移动可以将学生的位置 ±1。
 * 
 * 解题思路：
 * 贪心算法 - 将两个数组排序后一一对应，这样总移动距离最小。
 * 将第 i 小的学生分配到第 i 小的座位，可以保证绝对差之和最小。
 * 
 * 时间复杂度: O(n log n) 主要是排序
 * 空间复杂度: O(1) 或 O(n) 取决于排序算法
 */
class MinimumNumberOfMovesToSeatEveryoneSolution : public SolutionBase<Func> {
 public:
  int minMovesToSeat(vector<int>& seats, vector<int>& students);

  MinimumNumberOfMovesToSeatEveryoneSolution();
};

}  // namespace problem_2037
}  // namespace leetcode
