#include "leetcode/problems/customers-who-bought-all-products.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1045 {

class CustomersWhoBoughtAllProductsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CustomersWhoBoughtAllProductsSolution solution;
};

TEST_P(CustomersWhoBoughtAllProductsTest, Example1) {
  // Customer table
  vector<Customer> customers = {
    {1, 5}, {2, 6}, {3, 5}, {3, 6}, {1, 6}
  };
  // Product table
  vector<Product> products = {5, 6};
  // Expected: customer 1 and 3 bought all products
  vector<int> expected = {1, 3};
  
  vector<int> result = solution.customersWhoBoughtAllProducts(customers, products);
  EXPECT_EQ(expected, result);
}

TEST_P(CustomersWhoBoughtAllProductsTest, NoCustomerBoughtAll) {
  // No customer bought all products
  vector<Customer> customers = {
    {1, 5}, {2, 6}, {3, 5}
  };
  vector<Product> products = {5, 6, 7};
  vector<int> expected = {};
  
  vector<int> result = solution.customersWhoBoughtAllProducts(customers, products);
  EXPECT_EQ(expected, result);
}

TEST_P(CustomersWhoBoughtAllProductsTest, SingleProduct) {
  // Only one product
  vector<Customer> customers = {
    {1, 5}, {2, 5}, {3, 5}
  };
  vector<Product> products = {5};
  vector<int> expected = {1, 2, 3};
  
  vector<int> result = solution.customersWhoBoughtAllProducts(customers, products);
  EXPECT_EQ(expected, result);
}

TEST_P(CustomersWhoBoughtAllProductsTest, EmptyCustomer) {
  // No customers
  vector<Customer> customers = {};
  vector<Product> products = {5, 6};
  vector<int> expected = {};
  
  vector<int> result = solution.customersWhoBoughtAllProducts(customers, products);
  EXPECT_EQ(expected, result);
}

TEST_P(CustomersWhoBoughtAllProductsTest, DuplicatesInCustomer) {
  // Customer with duplicate purchases
  vector<Customer> customers = {
    {1, 5}, {1, 5}, {1, 6}, {1, 6}
  };
  vector<Product> products = {5, 6};
  vector<int> expected = {1};
  
  vector<int> result = solution.customersWhoBoughtAllProducts(customers, products);
  EXPECT_EQ(expected, result);
}

TEST_P(CustomersWhoBoughtAllProductsTest, MultipleProductsMoreCustomers) {
  // More complex case
  vector<Customer> customers = {
    {1, 1}, {1, 2}, {1, 3},
    {2, 1}, {2, 2},
    {3, 1}, {3, 2}, {3, 3}, {3, 4},
    {4, 1}, {4, 2}, {4, 3}, {4, 4}
  };
  vector<Product> products = {1, 2, 3, 4};
  vector<int> expected = {3, 4};
  
  vector<int> result = solution.customersWhoBoughtAllProducts(customers, products);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CustomersWhoBoughtAllProductsTest,
    ::testing::ValuesIn(CustomersWhoBoughtAllProductsSolution().getStrategyNames()));

}  // namespace problem_1045
}  // namespace leetcode
