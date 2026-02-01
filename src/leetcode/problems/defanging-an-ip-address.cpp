#include "leetcode/problems/defanging-an-ip-address.h"

namespace leetcode {
namespace problem_1108 {

// 方法一：遍历替换法
// 遍历字符串，遇到 '.' 则添加 "[.]"，否则添加原字符
// 时间复杂度: O(n), 空间复杂度: O(n)
static string solution1(string address) {
  string result;
  for (char c : address) {
    if (c == '.') {
      result += "[.]";
    } else {
      result += c;
    }
  }
  return result;
}

// 方法二：预分配空间法
// 先统计 '.' 的数量，预分配空间后填充
// 时间复杂度: O(n), 空间复杂度: O(n)
static string solution2(string address) {
  int dotCount = 0;
  for (char c : address) {
    if (c == '.') ++dotCount;
  }
  
  string result;
  result.reserve(address.size() + dotCount * 2);  // 每个 '.' 变成 "[.]"，多2个字符
  
  for (char c : address) {
    if (c == '.') {
      result += "[.]";
    } else {
      result += c;
    }
  }
  return result;
}

DefangingAnIpAddressSolution::DefangingAnIpAddressSolution() {
  setMetaInfo({.id = 1108,
               .title = "Defanging an IP Address",
               .url = "https://leetcode.com/problems/defanging-an-ip-address/"});
  registerStrategy("Iterate & Replace", solution1);
  registerStrategy("Pre-allocate Space", solution2);
}

string DefangingAnIpAddressSolution::defangIPaddr(string address) {
  return getSolution()(address);
}

}  // namespace problem_1108
}  // namespace leetcode
