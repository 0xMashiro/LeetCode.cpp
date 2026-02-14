#include "leetcode/problems/champagne-tower.h"

namespace leetcode {
namespace problem_799 {

// 模拟法：逐层计算每个杯子的香槟量
// 用dp[i][j]表示第i行第j个杯子收到的总香槟量（可能超过1）
// 如果dp[i][j] > 1，则溢出部分(dp[i][j] - 1) / 2分别流入下一行的两个杯子
// 时间复杂度: O(query_row^2)，空间复杂度: O(query_row)
static double solution1(int poured, int query_row, int query_glass) {
  // 由于只需要前一行的数据，可以用一维数组优化空间
  // 但为了清晰，先用二维思路，用vector存储当前行
  vector<double> current_row(1, poured);  // 第0行只有1个杯子，初始倒入poured
  
  for (int row = 0; row < query_row; ++row) {
    vector<double> next_row(row + 2, 0.0);  // 下一行有row+2个杯子
    for (int glass = 0; glass <= row; ++glass) {
      if (current_row[glass] > 1.0) {
        // 溢出部分平均分给下一行的左右两个杯子
        double overflow = (current_row[glass] - 1.0) / 2.0;
        next_row[glass] += overflow;      // 左下方的杯子
        next_row[glass + 1] += overflow;  // 右下方的杯子
      }
    }
    current_row = std::move(next_row);
  }
  
  // 返回结果，但最多为1（杯子满了）
  return min(1.0, current_row[query_glass]);
}

ChampagneTowerSolution::ChampagneTowerSolution() {
  setMetaInfo({.id = 799,
               .title = "Champagne Tower",
               .url = "https://leetcode.com/problems/champagne-tower/"});
  registerStrategy("Simulation", solution1);
}

double ChampagneTowerSolution::champagneTower(int poured, int query_row, int query_glass) {
  return getSolution()(poured, query_row, query_glass);
}

}  // namespace problem_799
}  // namespace leetcode
