#include "leetcode/core.h"

namespace leetcode {
namespace problem_1045 {

using Customer = std::pair<int, int>;  // {customer_id, product_key}
using Product = int;                   // product_key

using Func = std::function<vector<int>(const vector<Customer>&, const vector<Product>&)>;

/**
 * 1045. Customers Who Bought All Products
 * https://leetcode.com/problems/customers-who-bought-all-products/
 *
 * 找出购买了所有产品的客户
 * 思路：统计每个客户购买的唯一产品数量，与产品总数比较
 */
class CustomersWhoBoughtAllProductsSolution : public SolutionBase<Func> {
 public:
  vector<int> customersWhoBoughtAllProducts(const vector<Customer>& customers,
                                            const vector<Product>& products);

  CustomersWhoBoughtAllProductsSolution();
};

}  // namespace problem_1045
}  // namespace leetcode
