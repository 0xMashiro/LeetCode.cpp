#include "leetcode/problems/ambiguous-coordinates.h"

namespace leetcode {
namespace problem_816 {

// 生成字符串 num 所有合法的数字表示（整数或小数）
// 合法的表示需要满足：
// 1. 整数：不能有前导零（除非是 "0" 本身）
// 2. 小数：整数部分不能有前导零（除非是 "0"），小数部分末尾不能有零
static vector<string> getValidNumbers(const string& num) {
  vector<string> result;
  int n = num.size();
  
  // 尝试所有可能的小数点位置（包括没有小数点的情况）
  for (int i = 1; i <= n; ++i) {
    string integerPart = num.substr(0, i);
    string decimalPart = num.substr(i);
    
    // 检查整数部分是否合法
    // 不能有前导零，除非是 "0" 本身
    if (integerPart.size() > 1 && integerPart[0] == '0') {
      continue;
    }
    
    if (decimalPart.empty()) {
      // 没有小数部分，是整数
      result.push_back(integerPart);
    } else {
      // 有小数部分
      // 小数部分末尾不能有零
      if (decimalPart.back() == '0') {
        continue;
      }
      result.push_back(integerPart + "." + decimalPart);
    }
  }
  
  return result;
}

static vector<string> solution1(string s) {
  vector<string> result;
  int n = s.size();
  
  // 去掉括号
  string digits = s.substr(1, n - 2);
  int m = digits.size();
  
  // 在位置 i 处分割，左边是 x，右边是 y
  for (int i = 1; i < m; ++i) {
    string xStr = digits.substr(0, i);
    string yStr = digits.substr(i);
    
    vector<string> xOptions = getValidNumbers(xStr);
    vector<string> yOptions = getValidNumbers(yStr);
    
    // 组合所有可能的坐标对
    for (const string& x : xOptions) {
      for (const string& y : yOptions) {
        result.push_back("(" + x + ", " + y + ")");
      }
    }
  }
  
  return result;
}

AmbiguousCoordinatesSolution::AmbiguousCoordinatesSolution() {
  setMetaInfo({.id = 816,
               .title = "Ambiguous Coordinates",
               .url = "https://leetcode.com/problems/ambiguous-coordinates/"});
  registerStrategy("Enumerate", solution1);
}

vector<string> AmbiguousCoordinatesSolution::ambiguousCoordinates(string s) {
  return getSolution()(s);
}

}  // namespace problem_816
}  // namespace leetcode