#include "leetcode/problems/minimum-swaps-to-arrange-a-binary-grid.h"

namespace leetcode {
namespace problem_1536 {

// 贪心算法：计算每行最右边的1的位置，然后贪心地找到满足条件的行
// 时间复杂度: O(n²), 空间复杂度: O(n)
static int solution1(vector<vector<int>> &grid) {
  const int n = grid.size();
  if (n <= 1) return 0;

  // 计算每行最右边的1的位置，-1表示该行全是0
  vector<int> rightmostOne(n);
  for (int i = 0; i < n; ++i) {
    int pos = -1;
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == 1) {
        pos = j;
      }
    }
    rightmostOne[i] = pos;
  }

  int swaps = 0;
  // 对于每一行，找到满足条件的最上面的行
  for (int i = 0; i < n; ++i) {
    // 第i行需要满足：最右边的1的位置 <= i（即右侧至少有n-1-i个0）
    int targetPos = i;
    bool found = false;
    // 从下往上找，找到第一个满足条件的行
    for (int j = i; j < n; ++j) {
      if (rightmostOne[j] <= targetPos) {
        // 找到了，需要将第j行移动到第i行位置
        found = true;
        // 移动需要 j - i 次交换
        swaps += j - i;
        // 将第j行提取出来，并将i到j-1行各下移一行
        int temp = rightmostOne[j];
        for (int k = j; k > i; --k) {
          rightmostOne[k] = rightmostOne[k - 1];
        }
        rightmostOne[i] = temp;
        break;
      }
    }
    if (!found) {
      return -1;
    }
  }

  return swaps;
}

MinimumSwapsToArrangeABinaryGridSolution::MinimumSwapsToArrangeABinaryGridSolution() {
  setMetaInfo({.id = 1536,
               .title = "Minimum Swaps to Arrange a Binary Grid",
               .url = "https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/"});
  registerStrategy("Greedy", solution1);
}

int MinimumSwapsToArrangeABinaryGridSolution::minSwaps(vector<vector<int>> &grid) {
  return getSolution()(grid);
}

}  // namespace problem_1536
}  // namespace leetcode