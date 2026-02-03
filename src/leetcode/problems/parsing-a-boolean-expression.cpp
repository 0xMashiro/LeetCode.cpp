#include "leetcode/problems/parsing-a-boolean-expression.h"

namespace leetcode {
namespace problem_1106 {

class Parser {
 public:
  Parser(const string& s) : s_(s), idx_(0) {}

  bool parse() { return parseExpr(); }

 private:
  const string& s_;
  int idx_;

  bool parseExpr() {
    char ch = s_[idx_];
    if (ch == 't') {
      ++idx_;
      return true;
    }
    if (ch == 'f') {
      ++idx_;
      return false;
    }
    if (ch == '!') {
      ++idx_;  // skip '!'
      ++idx_;  // skip '('
      bool result = !parseExpr();
      ++idx_;  // skip ')'
      return result;
    }
    if (ch == '&' || ch == '|') {
      char op = ch;
      ++idx_;  // skip '&' or '|'
      ++idx_;  // skip '('
      bool result = parseExpr();
      while (s_[idx_] == ',') {
        ++idx_;  // skip ','
        bool next = parseExpr();
        if (op == '&') {
          result = result && next;
        } else {
          result = result || next;
        }
      }
      ++idx_;  // skip ')'
      return result;
    }
    return false;  // should never reach here
  }
};

static bool solution(string expression) {
  Parser parser(expression);
  return parser.parse();
}

ParsingABooleanExpressionSolution::ParsingABooleanExpressionSolution() {
  setMetaInfo({.id = 1106,
               .title = "Parsing A Boolean Expression",
               .url = "https://leetcode.com/problems/parsing-a-boolean-expression/"});
  registerStrategy("Recursive Parser", solution);
}

bool ParsingABooleanExpressionSolution::parseBoolExpr(string expression) {
  return getSolution()(expression);
}

}  // namespace problem_1106
}  // namespace leetcode
