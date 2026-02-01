#include "leetcode/problems/minimum-number-of-moves-to-seat-everyone.h"

namespace leetcode {
namespace problem_2037 {

/**
 * 贪心算法：排序后一一对应
 * 
 * 思路：将座位和学生都排序，然后按顺序配对。
 * 这样可以保证总移动次数最小。
 * 
 * 证明：假设排序后 seats = [s1, s2, ..., sn], students = [t1, t2, ..., tn]
 * 我们需要证明 ∑|si - ti| 是最小的。
 * 这是一个经典的贪心问题，类似于匹配问题中的最优解。
 * 如果存在交叉配对（即 si < sj 但 ti > tj），交换后不会增加总距离。
 * 
 * 时间复杂度: O(n log n)
 * 空间复杂度: O(1) 或 O(n) 取决于排序实现
 */
static int solution1(vector<int>& seats, vector<int>& students) {
  // 排序座位和学生位置
  sort(seats.begin(), seats.end());
  sort(students.begin(), students.end());
  
  int totalMoves = 0;
  const int n = seats.size();
  
  // 按顺序配对，计算总移动次数
  for (int i = 0; i < n; ++i) {
    totalMoves += abs(seats[i] - students[i]);
  }
  
  return totalMoves;
}

MinimumNumberOfMovesToSeatEveryoneSolution::MinimumNumberOfMovesToSeatEveryoneSolution() {
  setMetaInfo({.id = 2037,
               .title = "Minimum Number of Moves to Seat Everyone",
               .url = "https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/"});
  registerStrategy("Greedy Sorting", solution1);
}

int MinimumNumberOfMovesToSeatEveryoneSolution::minMovesToSeat(vector<int>& seats, vector<int>& students) {
  return getSolution()(seats, students);
}

}  // namespace problem_2037
}  // namespace leetcode
