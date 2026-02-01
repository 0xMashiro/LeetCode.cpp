#include "leetcode/core.h"

namespace leetcode {
namespace problem_1357 {

/**
 * Apply Discount Every n Orders
 * 思路：使用哈希表存储产品价格，维护顾客计数器
 * - 构造函数：建立产品ID到价格的映射
 * - getBill：计算账单，每第n个顾客应用折扣
 * 时间复杂度：getBill O(m)，m为购买产品种类数
 * 空间复杂度：O(p)，p为产品种类数
 */
class Cashier {
 public:
  Cashier(int n, int discount, vector<int>& products, vector<int>& prices);

  double getBill(vector<int> product, vector<int> amount);

 private:
  int n_;           // 每第n个顾客获得折扣
  int discount_;    // 折扣百分比
  int customerCount_;  // 顾客计数器
  unordered_map<int, int> priceMap_;  // 产品ID -> 价格
};

}  // namespace problem_1357
}  // namespace leetcode
