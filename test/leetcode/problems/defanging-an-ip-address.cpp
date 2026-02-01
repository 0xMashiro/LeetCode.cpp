#include "leetcode/problems/defanging-an-ip-address.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1108 {

class DefangingAnIpAddressTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DefangingAnIpAddressSolution solution;
};

TEST_P(DefangingAnIpAddressTest, Example1) {
  string address = "1.1.1.1";
  string expected = "1[.]1[.]1[.]1";
  EXPECT_EQ(expected, solution.defangIPaddr(address));
}

TEST_P(DefangingAnIpAddressTest, Example2) {
  string address = "255.100.50.0";
  string expected = "255[.]100[.]50[.]0";
  EXPECT_EQ(expected, solution.defangIPaddr(address));
}

TEST_P(DefangingAnIpAddressTest, NoDots) {
  // 边界情况：没有点的IP地址（虽然题目保证是有效IPv4，但这是极限情况）
  string address = "127001";
  string expected = "127001";
  EXPECT_EQ(expected, solution.defangIPaddr(address));
}

TEST_P(DefangingAnIpAddressTest, AllDots) {
  // 边界情况：全是点
  string address = "...";
  string expected = "[.][.][.]";
  EXPECT_EQ(expected, solution.defangIPaddr(address));
}

TEST_P(DefangingAnIpAddressTest, SingleDot) {
  // 边界情况：只有一个点
  string address = "1.1";
  string expected = "1[.]1";
  EXPECT_EQ(expected, solution.defangIPaddr(address));
}

TEST_P(DefangingAnIpAddressTest, LongAddress) {
  // 典型情况：较长的IP地址
  string address = "192.168.1.1";
  string expected = "192[.]168[.]1[.]1";
  EXPECT_EQ(expected, solution.defangIPaddr(address));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DefangingAnIpAddressTest,
    ::testing::ValuesIn(DefangingAnIpAddressSolution().getStrategyNames()));

}  // namespace problem_1108
}  // namespace leetcode
