#include "leetcode/core.h"

namespace leetcode {
namespace problem_1744 {

using Func = std::function<vector<bool>(vector<int>&, vector<vector<int>>&)>;

/**
 * 1744. Can You Eat Your Favorite Candy on Your Favorite Day?
 * https://leetcode.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/
 *
 * 思路：前缀和 + 数学分析
 * - 计算前缀和，得到每种糖果的累计数量范围
 * - 对于每个查询，判断是否能在指定天数吃到指定类型的糖果
 */
class CanYouEatYourFavoriteCandyOnYourFavoriteDaySolution : public SolutionBase<Func> {
 public:
  vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries);

  CanYouEatYourFavoriteCandyOnYourFavoriteDaySolution();
};

}  // namespace problem_1744
}  // namespace leetcode
