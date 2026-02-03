#include "leetcode/problems/solve-the-equation.h"

namespace leetcode {
namespace problem_640 {

// 解析方程的一侧，返回 {x的系数, 常数}
static pair<int, int> parseSide(const string& s) {
  int coeff = 0;  // x的系数
  int constant = 0;  // 常数
  int n = s.size();
  int i = 0;
  int sign = 1;  // 当前符号，1为正，-1为负
  
  while (i < n) {
    if (s[i] == '+') {
      sign = 1;
      i++;
    } else if (s[i] == '-') {
      sign = -1;
      i++;
    }
    
    // 读取数字
    int num = 0;
    bool hasNum = false;
    while (i < n && isdigit(s[i])) {
      num = num * 10 + (s[i] - '0');
      hasNum = true;
      i++;
    }
    
    // 检查是否是x项
    if (i < n && s[i] == 'x') {
      // x的系数
      if (!hasNum) {
        num = 1;  // x前面没有数字，系数为1
      }
      coeff += sign * num;
      i++;
    } else {
      // 常数项
      constant += sign * num;
    }
  }
  
  return {coeff, constant};
}

static string solution1(string equation) {
  // 找到等号位置
  size_t equalPos = equation.find('=');
  string left = equation.substr(0, equalPos);
  string right = equation.substr(equalPos + 1);
  
  // 解析左右两边
  auto [leftCoeff, leftConst] = parseSide(left);
  auto [rightCoeff, rightConst] = parseSide(right);
  
  // 移项：左边系数 - 右边系数 = 右边常数 - 左边常数
  int a = leftCoeff - rightCoeff;  // x的系数
  int b = rightConst - leftConst;  // 常数
  
  if (a == 0) {
    if (b == 0) {
      return "Infinite solutions";
    } else {
      return "No solution";
    }
  }
  
  return "x=" + to_string(b / a);
}

SolveTheEquationSolution::SolveTheEquationSolution() {
  setMetaInfo({.id = 640,
               .title = "Solve the Equation",
               .url = "https://leetcode.com/problems/solve-the-equation/"});
  registerStrategy("Linear Equation Parse", solution1);
}

string SolveTheEquationSolution::solveEquation(string equation) {
  return getSolution()(equation);
}

}  // namespace problem_640
}  // namespace leetcode
