#include "leetcode/problems/add-binary.h"

namespace leetcode {
namespace problem_67 {

// 模拟二进制加法
// 从字符串末尾开始逐位相加，处理进位
// 时间复杂度: O(max(n, m)), 空间复杂度: O(max(n, m))
static string solution1(string a, string b) {
  string result;
  int i = a.size() - 1;
  int j = b.size() - 1;
  int carry = 0;
  
  // 从低位到高位逐位相加
  while (i >= 0 || j >= 0 || carry > 0) {
    int sum = carry;
    if (i >= 0) {
      sum += a[i] - '0';
      i--;
    }
    if (j >= 0) {
      sum += b[j] - '0';
      j--;
    }
    result.push_back((sum % 2) + '0');
    carry = sum / 2;
  }
  
  // 反转结果（因为我们是从低位到高位计算的）
  reverse(result.begin(), result.end());
  return result;
}

AddBinarySolution::AddBinarySolution() {
  setMetaInfo({.id = 67,
               .title = "Add Binary",
               .url = "https://leetcode.com/problems/add-binary/"});
  registerStrategy("Simulation", solution1);
}

string AddBinarySolution::addBinary(string a, string b) {
  return getSolution()(a, b);
}

}  // namespace problem_67
}  // namespace leetcode
