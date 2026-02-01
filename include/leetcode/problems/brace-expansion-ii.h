#include "leetcode/core.h"

namespace leetcode {
namespace problem_1096 {

using Func = std::function<vector<string>(string)>;

/**
 * 1096. Brace Expansion II
 * https://leetcode.com/problems/brace-expansion-ii/
 * 
 * 使用递归下降解析器处理花括号表达式
 * 文法：
 *   expr: term (',' term)*   // 逗号表示并集
 *   term: factor+            // 连接表示笛卡尔积
 *   factor: letter | '{' expr '}'
 */
class BraceExpansionIiSolution : public SolutionBase<Func> {
 public:
  vector<string> braceExpansionII(string expression);

  BraceExpansionIiSolution();

 private:
  string s;
  int pos;
  
  // 解析表达式：处理逗号（并集）
  set<string> parseExpr();
  
  // 解析项：处理连接（笛卡尔积）
  set<string> parseTerm();
  
  // 解析因子：处理字母或花括号
  set<string> parseFactor();
};

}  // namespace problem_1096
}  // namespace leetcode
