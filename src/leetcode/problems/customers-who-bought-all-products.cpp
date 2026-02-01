#include "leetcode/problems/customers-who-bought-all-products.h"

namespace leetcode {
namespace problem_1045 {

// 哈希表统计法
// 时间复杂度: O(n + m)，n 是 customers 行数，m 是 products 数量
// 空间复杂度: O(n + m)
static vector<int> solution1(const vector<Customer>& customers,
                             const vector<Product>& products) {
  // 统计所有产品
  unordered_set<int> all_products;
  for (int p : products) {
    all_products.insert(p);
  }
  int total_products = all_products.size();
  
  // 统计每个客户购买的产品（去重）
  unordered_map<int, unordered_set<int>> customer_products;
  for (const auto& [customer_id, product_key] : customers) {
    customer_products[customer_id].insert(product_key);
  }
  
  // 找出购买了所有产品的客户
  vector<int> result;
  for (const auto& [customer_id, bought_products] : customer_products) {
    // 检查该客户是否购买了所有产品
    if (bought_products.size() >= total_products) {
      bool has_all = true;
      for (int p : all_products) {
        if (bought_products.find(p) == bought_products.end()) {
          has_all = false;
          break;
        }
      }
      if (has_all) {
        result.push_back(customer_id);
      }
    }
  }
  
  // 结果按升序排列（方便测试验证）
  sort(result.begin(), result.end());
  return result;
}

// 优化版：利用集合包含关系
// 时间复杂度: O(n + m)
// 空间复杂度: O(n + m)
static vector<int> solution2(const vector<Customer>& customers,
                             const vector<Product>& products) {
  // 统计所有产品
  unordered_set<int> all_products(products.begin(), products.end());
  int total_products = all_products.size();
  
  // 统计每个客户购买的产品数量
  unordered_map<int, unordered_set<int>> customer_products;
  for (const auto& [customer_id, product_key] : customers) {
    customer_products[customer_id].insert(product_key);
  }
  
  // 找出购买了所有产品的客户
  vector<int> result;
  for (const auto& [customer_id, bought_products] : customer_products) {
    if (bought_products.size() == total_products) {
      // 数量相等且所有产品都存在，则购买了所有产品
      result.push_back(customer_id);
    }
  }
  
  sort(result.begin(), result.end());
  return result;
}

CustomersWhoBoughtAllProductsSolution::CustomersWhoBoughtAllProductsSolution() {
  setMetaInfo({.id = 1045,
               .title = "Customers Who Bought All Products",
               .url = "https://leetcode.com/problems/customers-who-bought-all-products/"});
  registerStrategy("Hash Set", solution1);
  registerStrategy("Optimized Hash Set", solution2);
}

vector<int> CustomersWhoBoughtAllProductsSolution::customersWhoBoughtAllProducts(
    const vector<Customer>& customers,
    const vector<Product>& products) {
  return getSolution()(customers, products);
}

}  // namespace problem_1045
}  // namespace leetcode
