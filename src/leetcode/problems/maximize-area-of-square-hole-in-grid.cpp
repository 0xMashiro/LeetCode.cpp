#include "leetcode/problems/maximize-area-of-square-hole-in-grid.h"

namespace leetcode {
namespace problem_2943 {

// 策略1：排序后遍历找最长连续序列
// 时间复杂度: O(h log h + v log v)，其中 h = hBars.size(), v = vBars.size()
// 空间复杂度: O(h + v)（排序需要副本）
static int solution1(int n, int m, vector<int>& hBars, vector<int>& vBars) {
  // 计算水平方向最大连续可移除杆长度
  int maxH = 0;
  if (!hBars.empty()) {
    vector<int> hSorted = hBars;
    sort(hSorted.begin(), hSorted.end());
    int current = 1;
    for (int i = 1; i < hSorted.size(); ++i) {
      if (hSorted[i] == hSorted[i - 1] + 1) {
        ++current;
      } else {
        maxH = max(maxH, current);
        current = 1;
      }
    }
    maxH = max(maxH, current);
  }
  
  // 计算垂直方向最大连续可移除杆长度
  int maxV = 0;
  if (!vBars.empty()) {
    vector<int> vSorted = vBars;
    sort(vSorted.begin(), vSorted.end());
    int current = 1;
    for (int i = 1; i < vSorted.size(); ++i) {
      if (vSorted[i] == vSorted[i - 1] + 1) {
        ++current;
      } else {
        maxV = max(maxV, current);
        current = 1;
      }
    }
    maxV = max(maxV, current);
  }
  
  // 边长 = 最长连续长度 + 1
  int side = min(maxH + 1, maxV + 1);
  return side * side;
}

// 策略2：使用哈希集合找最长连续序列
// 时间复杂度: O(h + v)，但由于集合操作常数较大，实际可能比排序慢
// 空间复杂度: O(h + v)
static int solution2(int n, int m, vector<int>& hBars, vector<int>& vBars) {
  // 辅助函数：计算数组中的最长连续序列长度
  auto longestConsecutive = [](const vector<int>& nums) -> int {
    if (nums.empty()) return 0;
    unordered_set<int> numSet(nums.begin(), nums.end());
    int maxLen = 0;
    for (int num : numSet) {
      // 只有当 num 是序列的起点时才计算长度
      if (numSet.find(num - 1) == numSet.end()) {
        int currentNum = num;
        int currentLen = 1;
        while (numSet.find(currentNum + 1) != numSet.end()) {
          ++currentNum;
          ++currentLen;
        }
        maxLen = max(maxLen, currentLen);
      }
    }
    return maxLen;
  };
  
  int maxH = longestConsecutive(hBars);
  int maxV = longestConsecutive(vBars);
  
  int side = min(maxH + 1, maxV + 1);
  return side * side;
}

MaximizeAreaOfSquareHoleInGridSolution::MaximizeAreaOfSquareHoleInGridSolution() {
  setMetaInfo({.id = 2943,
               .title = "Maximize Area of Square Hole in Grid",
               .url = "https://leetcode.com/problems/maximize-area-of-square-hole-in-grid/"});
  registerStrategy({.name = "Sorting + Traversal"}, solution1);
  registerStrategy({.name = "Hash Set"}, solution2);
}

int MaximizeAreaOfSquareHoleInGridSolution::maximizeSquareHoleArea(
    int n, int m, vector<int>& hBars, vector<int>& vBars) {
  return getSolution()(n, m, hBars, vBars);
}

}  // namespace problem_2943
}  // namespace leetcode