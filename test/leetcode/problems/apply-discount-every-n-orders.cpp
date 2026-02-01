#include "leetcode/problems/apply-discount-every-n-orders.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1357 {

TEST(LeetCode, ApplyDiscountEveryNOrdersExample1) {
  // Example 1 from problem description
  vector<int> products = {1, 2, 3, 4, 5, 6, 7};
  vector<int> prices = {100, 200, 300, 400, 300, 200, 100};
  Cashier cashier(3, 50, products, prices);
  
  // 1st customer, no discount. bill = 1*100 + 2*200 = 500
  vector<int> product1 = {1, 2};
  vector<int> amount1 = {1, 2};
  EXPECT_DOUBLE_EQ(cashier.getBill(product1, amount1), 500.0);
  
  // 2nd customer, no discount. bill = 10*300 + 10*100 = 4000
  vector<int> product2 = {3, 7};
  vector<int> amount2 = {10, 10};
  EXPECT_DOUBLE_EQ(cashier.getBill(product2, amount2), 4000.0);
  
  // 3rd customer, 50% discount. Original bill = 1600, Actual = 800
  vector<int> product3 = {1, 2, 3, 4, 5, 6, 7};
  vector<int> amount3 = {1, 1, 1, 1, 1, 1, 1};
  EXPECT_DOUBLE_EQ(cashier.getBill(product3, amount3), 800.0);
  
  // 4th customer, no discount. bill = 10*400 = 4000
  vector<int> product4 = {4};
  vector<int> amount4 = {10};
  EXPECT_DOUBLE_EQ(cashier.getBill(product4, amount4), 4000.0);
  
  // 5th customer, no discount. bill = 10*100 + 10*300 = 4000
  vector<int> product5 = {7, 3};
  vector<int> amount5 = {10, 10};
  EXPECT_DOUBLE_EQ(cashier.getBill(product5, amount5), 4000.0);
  
  // 6th customer, 50% discount. Original bill = 14700, Actual = 7350
  vector<int> product6 = {7, 5, 3, 1, 6, 4, 2};
  vector<int> amount6 = {10, 10, 10, 9, 9, 9, 7};
  EXPECT_DOUBLE_EQ(cashier.getBill(product6, amount6), 7350.0);
  
  // 7th customer, no discount. bill = 5*200 + 3*300 + 2*300 = 2500
  vector<int> product7 = {2, 3, 5};
  vector<int> amount7 = {5, 3, 2};
  EXPECT_DOUBLE_EQ(cashier.getBill(product7, amount7), 2500.0);
}

TEST(LeetCode, ApplyDiscountEveryNOrdersNoDiscount) {
  // Test with discount = 0 (no discount ever applied)
  vector<int> products = {1, 2};
  vector<int> prices = {100, 200};
  Cashier cashier(2, 0, products, prices);
  
  vector<int> product = {1, 2};
  vector<int> amount = {1, 1};
  
  // Even 2nd customer gets no discount because discount is 0
  EXPECT_DOUBLE_EQ(cashier.getBill(product, amount), 300.0);  // 1st customer
  EXPECT_DOUBLE_EQ(cashier.getBill(product, amount), 300.0);  // 2nd customer, 0% discount
}

TEST(LeetCode, ApplyDiscountEveryNOrdersSingleProduct) {
  // Test with single product
  vector<int> products = {1};
  vector<int> prices = {100};
  Cashier cashier(1, 10, products, prices);  // Every customer gets 10% discount
  
  vector<int> product = {1};
  vector<int> amount = {1};
  
  // Every customer is the nth customer
  EXPECT_DOUBLE_EQ(cashier.getBill(product, amount), 90.0);  // 100 * 0.9
  EXPECT_DOUBLE_EQ(cashier.getBill(product, amount), 90.0);  // 100 * 0.9
  EXPECT_DOUBLE_EQ(cashier.getBill(product, amount), 90.0);  // 100 * 0.9
}

TEST(LeetCode, ApplyDiscountEveryNOrdersFullDiscount) {
  // Test with 100% discount
  vector<int> products = {1, 2};
  vector<int> prices = {100, 200};
  Cashier cashier(1, 100, products, prices);
  
  vector<int> product = {1, 2};
  vector<int> amount = {1, 1};
  
  // 100% discount means free
  EXPECT_DOUBLE_EQ(cashier.getBill(product, amount), 0.0);
}

TEST(LeetCode, ApplyDiscountEveryNOrdersLargeAmount) {
  // Test with large amounts to check for overflow
  vector<int> products = {1};
  vector<int> prices = {1000};
  Cashier cashier(2, 50, products, prices);
  
  vector<int> product = {1};
  vector<int> amount = {1000};  // 1000 * 1000 = 1,000,000
  
  EXPECT_DOUBLE_EQ(cashier.getBill(product, amount), 1000000.0);  // 1st customer, no discount
  EXPECT_DOUBLE_EQ(cashier.getBill(product, amount), 500000.0);   // 2nd customer, 50% discount
}

}  // namespace problem_1357
}  // namespace leetcode
