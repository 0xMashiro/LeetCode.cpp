#include "leetcode/core.h"

namespace leetcode {
namespace problem_42 {

using Func = std::function<int(vector<int>&)>;

/**
 * 42. Trapping Rain Water
 * https://leetcode.com/problems/trapping-rain-water/
 * 
 * 给定 n 个非负整数表示高度图，计算下雨后能接多少雨水。
 * 双指针解法：从两端向中间遍历，维护左右最大高度，
 * 较矮的一边是瓶颈，可以计算该位置的接水量。
 * 时间复杂度: O(n), 空间复杂度: O(1)
 */
class TrappingRainWaterSolution : public SolutionBase<Func> {
 public:
  int trap(vector<int>& height);
  
  TrappingRainWaterSolution();
};

}  // namespace problem_42
}  // namespace leetcode
