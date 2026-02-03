#include "leetcode/problems/maximum-nesting-depth-of-two-valid-parentheses-strings.h"

namespace leetcode {
namespace problem_1111 {

// 贪心策略：按当前嵌套深度的奇偶性分配
// 奇数深度分配给 A（标记 0），偶数深度分配给 B（标记 1）
// 这样两个序列的最大深度都约为原序列最大深度的一半
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution1(string seq) {
  int n = seq.size();
  vector<int> answer(n);
  int depth = 0;
  
  for (int i = 0; i < n; ++i) {
    if (seq[i] == '(') {
      // 遇到左括号，深度增加，根据奇偶性分配
      ++depth;
      answer[i] = (depth % 2 == 1) ? 0 : 1;
    } else {
      // 遇到右括号，先根据当前深度分配，然后深度减少
      answer[i] = (depth % 2 == 1) ? 0 : 1;
      --depth;
    }
  }
  
  return answer;
}

// 另一种等价的实现方式：使用 i & 1 与括号索引结合
// 利用括号的层数奇偶性进行分配
static vector<int> solution2(string seq) {
  int n = seq.size();
  vector<int> answer(n);
  int depth = 0;
  
  for (int i = 0; i < n; ++i) {
    if (seq[i] == '(') {
      answer[i] = depth % 2;
      ++depth;
    } else {
      --depth;
      answer[i] = depth % 2;
    }
  }
  
  return answer;
}

MaximumNestingDepthOfTwoValidParenthesesStringsSolution::MaximumNestingDepthOfTwoValidParenthesesStringsSolution() {
  setMetaInfo({
    .id = 1111,
    .title = "Maximum Nesting Depth of Two Valid Parentheses Strings",
    .url = "https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/"
  });
  registerStrategy("Odd-Even Depth Split", solution1);
  registerStrategy("Depth Modulo Split", solution2);
}

vector<int> MaximumNestingDepthOfTwoValidParenthesesStringsSolution::maxDepthAfterSplit(string seq) {
  return getSolution()(seq);
}

}  // namespace problem_1111
}  // namespace leetcode