#include "leetcode/problems/apply-discount-every-n-orders.h"

namespace leetcode {
namespace problem_1357 {

Cashier::Cashier(int n, int discount, vector<int>& products, vector<int>& prices)
    : n_(n), discount_(discount), customerCount_(0) {
  // 建立产品ID到价格的映射
  for (size_t i = 0; i < products.size(); ++i) {
    priceMap_[products[i]] = prices[i];
  }
}

double Cashier::getBill(vector<int> product, vector<int> amount) {
  // 增加顾客计数
  ++customerCount_;
  
  // 计算小计
  long long subtotal = 0;
  for (size_t i = 0; i < product.size(); ++i) {
    subtotal += static_cast<long long>(priceMap_[product[i]]) * amount[i];
  }
  
  // 判断是否需要应用折扣（第n个顾客）
  if (customerCount_ % n_ == 0) {
    // 应用折扣: bill * ((100 - discount) / 100)
    return subtotal * (100 - discount_) / 100.0;
  }
  
  return static_cast<double>(subtotal);
}

}  // namespace problem_1357
}  // namespace leetcode
