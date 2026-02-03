#include "leetcode/core.h"

namespace leetcode {
namespace problem_1418 {

using Func = std::function<vector<vector<string>>(vector<vector<string>>&)>;

class DisplayTableOfFoodOrdersInARestaurantSolution : public SolutionBase<Func> {
 public:
  //! 1418. Display Table of Food Orders in a Restaurant
  //! https://leetcode.com/problems/display-table-of-food-orders-in-a-restaurant/
  vector<vector<string>> displayTable(vector<vector<string>>& orders);

  DisplayTableOfFoodOrdersInARestaurantSolution();
};

}  // namespace problem_1418
}  // namespace leetcode
