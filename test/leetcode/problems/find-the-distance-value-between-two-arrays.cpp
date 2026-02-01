#include "leetcode/problems/find-the-distance-value-between-two-arrays.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1385 {

class FindTheDistanceValueBetweenTwoArraysTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindTheDistanceValueBetweenTwoArraysSolution solution;
};

TEST_P(FindTheDistanceValueBetweenTwoArraysTest, Example1) {
  vector<int> arr1 = {4, 5, 8};
  vector<int> arr2 = {10, 9, 1, 8};
  int d = 2;
  int expected = 2;
  EXPECT_EQ(expected, solution.findTheDistanceValue(arr1, arr2, d));
}

TEST_P(FindTheDistanceValueBetweenTwoArraysTest, Example2) {
  vector<int> arr1 = {1, 4, 2, 3};
  vector<int> arr2 = {-4, -3, 6, 10, 20, 30};
  int d = 3;
  int expected = 2;
  EXPECT_EQ(expected, solution.findTheDistanceValue(arr1, arr2, d));
}

TEST_P(FindTheDistanceValueBetweenTwoArraysTest, Example3) {
  vector<int> arr1 = {2, 1, 100, 3};
  vector<int> arr2 = {-5, -2, 10, -3, 7};
  int d = 6;
  int expected = 1;
  EXPECT_EQ(expected, solution.findTheDistanceValue(arr1, arr2, d));
}

TEST_P(FindTheDistanceValueBetweenTwoArraysTest, SingleElement) {
  // 边界情况：单元素数组
  vector<int> arr1 = {1};
  vector<int> arr2 = {10};
  int d = 5;
  int expected = 1;  // |1-10|=9 > 5
  EXPECT_EQ(expected, solution.findTheDistanceValue(arr1, arr2, d));
}

TEST_P(FindTheDistanceValueBetweenTwoArraysTest, NoValidElement) {
  // 边界情况：没有满足条件的元素
  vector<int> arr1 = {1, 2, 3};
  vector<int> arr2 = {1, 2, 3};
  int d = 0;
  int expected = 0;  // 每个元素都能找到差值为0的元素
  EXPECT_EQ(expected, solution.findTheDistanceValue(arr1, arr2, d));
}

TEST_P(FindTheDistanceValueBetweenTwoArraysTest, AllValidElements) {
  // 边界情况：所有元素都满足条件
  vector<int> arr1 = {1, 2, 3};
  vector<int> arr2 = {100, 200, 300};
  int d = 10;
  int expected = 3;  // 所有元素都距离很远
  EXPECT_EQ(expected, solution.findTheDistanceValue(arr1, arr2, d));
}

TEST_P(FindTheDistanceValueBetweenTwoArraysTest, NegativeNumbers) {
  // 边界情况：负数
  // arr1 = {-10, -5, 0}, arr2 = {-20, -15, 5}, d = 4
  // -10: |-10-(-20)|=10>4, |-10-(-15)|=5>4, |-10-5|=15>4 -> valid
  // -5:  |-5-(-20)|=15>4,  |-5-(-15)|=10>4, |-5-5|=10>4  -> valid
  // 0:   |0-(-20)|=20>4,   |0-(-15)|=15>4,  |0-5|=5>4    -> valid
  vector<int> arr1 = {-10, -5, 0};
  vector<int> arr2 = {-20, -15, 5};
  int d = 4;
  int expected = 3;  // 所有三个元素都满足条件
  EXPECT_EQ(expected, solution.findTheDistanceValue(arr1, arr2, d));
}

TEST_P(FindTheDistanceValueBetweenTwoArraysTest, ZeroDistance) {
  // 边界情况：d = 0
  vector<int> arr1 = {1, 2, 3};
  vector<int> arr2 = {4, 5, 6};
  int d = 0;
  int expected = 3;  // 所有差值都 > 0
  EXPECT_EQ(expected, solution.findTheDistanceValue(arr1, arr2, d));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindTheDistanceValueBetweenTwoArraysTest,
    ::testing::ValuesIn(FindTheDistanceValueBetweenTwoArraysSolution().getStrategyNames()));

}  // namespace problem_1385
}  // namespace leetcode
