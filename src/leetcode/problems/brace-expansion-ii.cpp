#include "leetcode/problems/brace-expansion-ii.h"

namespace leetcode {
namespace problem_1096 {

// 计算两个集合的笛卡尔积（连接）
static set<string> cartesianProduct(const set<string>& a, const set<string>& b) {
  set<string> result;
  for (const string& x : a) {
    for (const string& y : b) {
      result.insert(x + y);
    }
  }
  return result;
}

// 解析表达式：term (',' term)*
// 逗号表示并集
set<string> BraceExpansionIiSolution::parseExpr() {
  set<string> result = parseTerm();
  
  while (pos < s.size() && s[pos] == ',') {
    ++pos;  // 跳过 ','
    set<string> term = parseTerm();
    // 并集
    result.insert(term.begin(), term.end());
  }
  
  return result;
}

// 解析项：factor+
// 连接表示笛卡尔积
set<string> BraceExpansionIiSolution::parseTerm() {
  set<string> result = {""};  // 初始为空字符串（乘法单位元）
  
  // 只要后面还有因子（字母或 '{'）就继续解析
  while (pos < s.size() && (s[pos] == '{' || islower(s[pos]))) {
    set<string> factor = parseFactor();
    // 笛卡尔积
    result = cartesianProduct(result, factor);
  }
  
  return result;
}

// 解析因子：字母 | '{' expr '}'
set<string> BraceExpansionIiSolution::parseFactor() {
  if (s[pos] == '{') {
    ++pos;  // 跳过 '{'
    set<string> result = parseExpr();
    ++pos;  // 跳过 '}'
    return result;
  } else {
    // 单个小写字母
    return {string(1, s[pos++])};
  }
}

// 主函数
vector<string> BraceExpansionIiSolution::braceExpansionII(string expression) {
  s = expression;
  pos = 0;
  set<string> result = parseExpr();
  return vector<string>(result.begin(), result.end());
}

BraceExpansionIiSolution::BraceExpansionIiSolution() {
  setMetaInfo({
    .id = 1096,
    .title = "Brace Expansion II",
    .url = "https://leetcode.com/problems/brace-expansion-ii/"
  });
  registerStrategy("Recursive Descent Parser", [this](string expression) {
    return this->braceExpansionII(expression);
  });
}

}  // namespace problem_1096
}  // namespace leetcode
