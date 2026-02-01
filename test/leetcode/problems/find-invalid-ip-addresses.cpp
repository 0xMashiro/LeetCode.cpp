#include "leetcode/problems/find-invalid-ip-addresses.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3451 {

class FindInvalidIpAddressesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindInvalidIpAddressesSolution solution;
};

// 题目示例
TEST_P(FindInvalidIpAddressesTest, Example1) {
  vector<string> ips = {
    "192.168.1.1",
    "256.1.2.3",
    "192.168.001.1",
    "192.168.1.1",
    "192.168.1",
    "256.1.2.3",
    "192.168.001.1"
  };
  vector<string> expected = {
    "256.1.2.3 2",
    "192.168.001.1 2",
    "192.168.1 1"
  };
  EXPECT_EQ(expected, solution.findInvalidIpAddresses(ips));
}

// 测试空输入
TEST_P(FindInvalidIpAddressesTest, EmptyInput) {
  vector<string> ips = {};
  vector<string> expected = {};
  EXPECT_EQ(expected, solution.findInvalidIpAddresses(ips));
}

// 测试所有 IP 都有效的情况
TEST_P(FindInvalidIpAddressesTest, AllValid) {
  vector<string> ips = {
    "192.168.1.1",
    "10.0.0.1",
    "255.255.255.255",
    "0.0.0.0"
  };
  vector<string> expected = {};
  EXPECT_EQ(expected, solution.findInvalidIpAddresses(ips));
}

// 测试所有 IP 都无效的情况（按 IP 降序：字符串比较）
TEST_P(FindInvalidIpAddressesTest, AllInvalid) {
  vector<string> ips = {
    "256.1.2.3",      // > 255
    "192.168.01.1",   // 前导零
    "192.168.1"       // 不足 4 octets
  };
  // 字符串降序："256.1.2.3" > "192.168.1" > "192.168.01.1"
  vector<string> expected = {
    "256.1.2.3 1",
    "192.168.1 1",
    "192.168.01.1 1"
  };
  EXPECT_EQ(expected, solution.findInvalidIpAddresses(ips));
}

// 测试边界值（按字符串降序排序）
TEST_P(FindInvalidIpAddressesTest, BoundaryValues) {
  vector<string> ips = {
    "0.0.0.0",        // 有效（最小值）
    "255.255.255.255", // 有效（最大值）
    "256.0.0.0",      // 无效（256 > 255）
    "0.0.0.256",      // 无效（256 > 255）
    "00.0.0.0",       // 无效（前导零）
    "0.00.0.0",       // 无效（前导零）
    "0.0.0.00"        // 无效（前导零）
  };
  // 字符串降序："256.0.0.0" > "00.0.0.0" > "0.00.0.0" > "0.0.0.256" > "0.0.0.00"
  vector<string> expected = {
    "256.0.0.0 1",
    "00.0.0.0 1",
    "0.00.0.0 1",
    "0.0.0.256 1",
    "0.0.0.00 1"
  };
  EXPECT_EQ(expected, solution.findInvalidIpAddresses(ips));
}

// 测试超过 4 octets 的情况（字符串降序排序）
TEST_P(FindInvalidIpAddressesTest, TooManyOctets) {
  vector<string> ips = {
    "192.168.1.1.1",   // 5 octets
    "1.2.3.4.5.6",     // 6 octets
    "192.168.1.1"      // 有效，4 octets
  };
  // 字符串降序："192.168.1.1.1" > "1.2.3.4.5.6"
  vector<string> expected = {
    "192.168.1.1.1 1",
    "1.2.3.4.5.6 1"
  };
  EXPECT_EQ(expected, solution.findInvalidIpAddresses(ips));
}

// 测试少于 4 octets 的情况
TEST_P(FindInvalidIpAddressesTest, TooFewOctets) {
  vector<string> ips = {
    "192.168.1",       // 3 octets
    "192.168",         // 2 octets
    "192",             // 1 octet
    "192.168.1.1"      // 有效
  };
  // 字符串降序："192.168.1" > "192.168" > "192"
  vector<string> expected = {
    "192.168.1 1",
    "192.168 1",
    "192 1"
  };
  EXPECT_EQ(expected, solution.findInvalidIpAddresses(ips));
}

// 测试 IP 降序排序（相同计数时）
TEST_P(FindInvalidIpAddressesTest, IpDescendingSort) {
  vector<string> ips = {
    "256.1.1.1",       // 都出现 1 次，按 IP 降序
    "192.168.1",       
    "192.168.001.1"
  };
  // 字符串降序："256.1.1.1" > "192.168.1" > "192.168.001.1"
  vector<string> expected = {
    "256.1.1.1 1",
    "192.168.1 1",
    "192.168.001.1 1"
  };
  EXPECT_EQ(expected, solution.findInvalidIpAddresses(ips));
}

// 测试重复多次的 IP
TEST_P(FindInvalidIpAddressesTest, MultipleOccurrences) {
  vector<string> ips = {
    "256.0.0.0",
    "256.0.0.0",
    "256.0.0.0",
    "192.168.01.1",
    "192.168.01.1",
    "192.168.1"
  };
  // 按 count 降序，相同 count 按 IP 降序
  vector<string> expected = {
    "256.0.0.0 3",
    "192.168.01.1 2",
    "192.168.1 1"
  };
  EXPECT_EQ(expected, solution.findInvalidIpAddresses(ips));
}

// 测试包含非法字符的 IP（字符串降序排序）
TEST_P(FindInvalidIpAddressesTest, InvalidCharacters) {
  vector<string> ips = {
    "192.168.a.1",     // 包含字母
    "192.168.1.1.1",   // 5 octets
    "192..168.1.1"     // 空 octet
  };
  // 字符串降序："192.168.a.1" > "192.168.1.1.1" > "192..168.1.1"
  vector<string> expected = {
    "192.168.a.1 1",
    "192.168.1.1.1 1",
    "192..168.1.1 1"
  };
  EXPECT_EQ(expected, solution.findInvalidIpAddresses(ips));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindInvalidIpAddressesTest,
    ::testing::ValuesIn(FindInvalidIpAddressesSolution().getStrategyNames()));

}  // namespace problem_3451
}  // namespace leetcode
