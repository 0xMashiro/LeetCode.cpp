#include "leetcode/problems/simplify-path.h"

namespace leetcode {
namespace problem_71 {

// 使用栈处理路径简化
// 时间复杂度: O(n), 空间复杂度: O(n)
static string solution1(string path) {
  vector<string> stack;  // 模拟栈，存储目录名
  string token;
  
  // 手动分割路径，按 '/' 分隔
  for (int i = 0; i <= path.size(); ++i) {
    // 遇到 '/' 或字符串结束，处理当前 token
    if (i == path.size() || path[i] == '/') {
      if (!token.empty()) {
        if (token == "..") {
          // 返回上级目录：弹栈
          if (!stack.empty()) {
            stack.pop_back();
          }
        } else if (token != ".") {
          // 有效目录名：压栈
          stack.push_back(token);
        }
        token.clear();
      }
    } else {
      token += path[i];
    }
  }
  
  // 构建简化后的路径
  if (stack.empty()) {
    return "/";
  }
  
  string result;
  for (const string& dir : stack) {
    result += "/" + dir;
  }
  return result;
}

SimplifyPathSolution::SimplifyPathSolution() {
  setMetaInfo({.id = 71,
               .title = "Simplify Path",
               .url = "https://leetcode.com/problems/simplify-path/"});
  registerStrategy("Stack", solution1);
}

string SimplifyPathSolution::simplifyPath(string path) {
  return getSolution()(path);
}

}  // namespace problem_71
}  // namespace leetcode
