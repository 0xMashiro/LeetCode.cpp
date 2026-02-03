#include "leetcode/problems/display-table-of-food-orders-in-a-restaurant.h"

namespace leetcode {
namespace problem_1418 {

static vector<vector<string>> solution(vector<vector<string>>& orders) {
  // 收集所有桌号（数字）和食物名称
  set<int> table_numbers;
  set<string> food_names;
  // table -> food -> count
  unordered_map<int, unordered_map<string, int>> table_food_count;
  
  for (const auto& order : orders) {
    int table = stoi(order[1]);
    const string& food = order[2];
    table_numbers.insert(table);
    food_names.insert(food);
    table_food_count[table][food]++;
  }
  
  // 构建结果
  vector<vector<string>> result;
  
  // 第一行：表头
  vector<string> header;
  header.push_back("Table");
  for (const auto& food : food_names) {
    header.push_back(food);
  }
  result.push_back(header);
  
  // 后续行：每个桌的数据
  for (int table : table_numbers) {
    vector<string> row;
    row.push_back(to_string(table));
    for (const auto& food : food_names) {
      int count = 0;
      auto it = table_food_count[table].find(food);
      if (it != table_food_count[table].end()) {
        count = it->second;
      }
      row.push_back(to_string(count));
    }
    result.push_back(row);
  }
  
  return result;
}

DisplayTableOfFoodOrdersInARestaurantSolution::DisplayTableOfFoodOrdersInARestaurantSolution() {
  setMetaInfo({.id = 1418,
               .title = "Display Table of Food Orders in a Restaurant",
               .url = "https://leetcode.com/problems/display-table-of-food-orders-in-a-restaurant/"});
  registerStrategy("Hash Map", solution);
}

vector<vector<string>> DisplayTableOfFoodOrdersInARestaurantSolution::displayTable(vector<vector<string>>& orders) {
  return getSolution()(orders);
}

}  // namespace problem_1418
}  // namespace leetcode
