
#include "leetcode/problems/minimum-cost-to-change-the-final-value-of-expression.h"

namespace leetcode {
namespace problem_1896 {

/**
 * 解题思路：使用栈模拟表达式求值
 * 
 * 对于每个子表达式，我们需要维护两个信息：
 * 1. value: 当前表达式的值（0或1）
 * 2. cost: 将当前表达式值翻转的最小代价
 * 
 * 对于叶子节点（'0'或'1'）：
 * - '0': value=0, cost=1（变成'1'需要1次操作）
 * - '1': value=1, cost=1（变成'0'需要1次操作）
 * 
 * 对于 & 运算（假设左子树(val1,cost1)，右子树(val2,cost2)）：
 * - 结果值：val1 & val2
 * - 结果0翻1：需要变成1&1，代价 = cost1(0->1) + cost2(0->1) 或改运算符
 *   但最优策略：改运算符为|，然后可能还需要改子树
 *   实际上：min(cost1+cost2, 1 + 某个子树cost) 需要仔细分析
 * 
 * 更系统的方法：
 * 对于每个节点，记录 (值, 变成0的最小代价, 变成1的最小代价)
 * 或者：dp[0]=变成0的最小代价, dp[1]=变成1的最小代价
 * 
 * 叶子节点：
 * - '0': dp[0]=0, dp[1]=1
 * - '1': dp[0]=1, dp[1]=0
 * 
 * & 运算：
 * - dp[0] = min(dp1[0]+dp2[0], dp1[0]+dp2[1], dp1[1]+dp2[0], 1+min(...))
 *   实际上：0&0=0, 0&1=0, 1&0=0, 1&1=1
 *   要得到0：可以是0&0, 0&1, 1&0
 *   要得到1：只能是1&1
 *   所以：dp[0] = min({dp1[0]+dp2[0], dp1[0]+dp2[1], dp1[1]+dp2[0]})
 *        dp[1] = dp1[1] + dp2[1]
 *   或者改运算符：1+改|运算后的代价
 *   
 * 但注意：我们也可以改运算符！&改成|，代价+1
 * 所以：
 * dp[0] = min({
 *   dp1[0]+dp2[0],  // 0&0=0
 *   dp1[0]+dp2[1],  // 0&1=0
 *   dp1[1]+dp2[0],  // 1&0=0
 *   1 + min({dp1[0]+dp2[0], dp1[1]+dp2[1], dp1[0]+dp2[1]})  // 改|后得到0
 * })
 * 
 * 实际上对于|运算得到0：只能是0|0
 * 所以最后一项是：1 + dp1[0] + dp2[0]
 * 
 * 类似地，dp[1] = min({
 *   dp1[1]+dp2[1],  // 1&1=1
 *   1 + dp1[1]+dp2[1]  // 改|后得到1：1|1=1
 * }) = dp1[1]+dp2[1]  // 显然不改运算符更好
 * 
 * 等等，这样分析有问题。让我们重新思考：
 * 
 * 我们有两个选择：
 * 1. 不改当前运算符，递归计算子问题
 * 2. 改当前运算符（代价+1），然后递归计算
 * 
 * 对于 & 运算不改的情况：
 * - 得到0：左0或右0即可 = min(dp1[0]+dp2[0], dp1[0]+dp2[1], dp1[1]+dp2[0])
 * - 得到1：必须左右都为1 = dp1[1]+dp2[1]
 * 
 * 对于 & 改成 | 的情况（额外代价1）：
 * - 得到0：必须左右都为0 = 1 + dp1[0] + dp2[0]
 * - 得到1：左1或右1即可 = 1 + min(dp1[0]+dp2[1], dp1[1]+dp2[0], dp1[1]+dp2[1])
 * 
 * 所以：
 * dp&[0] = min(dp1[0]+dp2[0], dp1[0]+dp2[1], dp1[1]+dp2[0], 1+dp1[0]+dp2[0])
 *        = min(dp1[0]+dp2[1], dp1[1]+dp2[0], dp1[0]+dp2[0])  // 最后一项总是>=第一项
 *        不对，1+dp1[0]+dp2[0] 可能更小吗？不可能，因为dp1[0]+dp2[0]已经包含在内了
 *        所以：dp&[0] = min({dp1[0]+dp2[0], dp1[0]+dp2[1], dp1[1]+dp2[0]})
 *        
 * 等等，我犯了个错误。dp1[0]表示将左子树变成0的最小代价，但不一定是改叶子。
 * 实际上对于叶子'0'，dp[0]=0（已经是0，不用改），dp[1]=1（改成1需要1次）
 * 对于叶子'1'，dp[0]=1（改成0需要1次），dp[1]=0（已经是1，不用改）
 * 
 * 所以上面的公式是正确的。
 * 
 * 类似分析 | 运算：
 * 不改|：
 * - 得到0：必须左右都为0 = dp1[0]+dp2[0]
 * - 得到1：左1或右1即可 = min(dp1[1]+dp2[0], dp1[0]+dp2[1], dp1[1]+dp2[1])
 * 
 * 改成&（额外代价1）：
 * - 得到0：左0或右0即可 = 1 + min(dp1[0]+dp2[0], dp1[0]+dp2[1], dp1[1]+dp2[0])
 * - 得到1：必须左右都为1 = 1 + dp1[1]+dp2[1]
 * 
 * 所以：
 * dp|[0] = min(dp1[0]+dp2[0], 1+min(dp1[0]+dp2[0], dp1[0]+dp2[1], dp1[1]+dp2[0]))
 * dp|[1] = min(min(dp1[1]+dp2[0], dp1[0]+dp2[1], dp1[1]+dp2[1]), 1+dp1[1]+dp2[1])
 *        = min(dp1[1]+dp2[0], dp1[0]+dp2[1], dp1[1]+dp2[1])
 */

// 使用pair<int, int>表示 {变成0的最小代价, 变成1的最小代价}
using CostPair = pair<int, int>;

static int minOperationsToFlipImpl(string& expr) {
  int n = expr.size();
  // 两个栈：一个存值（cost pair），一个存运算符
  stack<CostPair> valStack;
  stack<char> opStack;
  
  auto applyOp = [&]() {
    char op = opStack.top(); opStack.pop();
    auto right = valStack.top(); valStack.pop();
    auto left = valStack.top(); valStack.pop();
    
    int l0 = left.first, l1 = left.second;
    int r0 = right.first, r1 = right.second;
    
    CostPair res;
    if (op == '&') {
      // 不改运算符
      int to0 = min({l0 + r0, l0 + r1, l1 + r0});
      int to1 = l1 + r1;
      // 改运算符为|，额外+1
      int to0Change = 1 + l0 + r0;  // |运算得0：必须0|0
      int to1Change = 1 + min({l0 + r1, l1 + r0, l1 + r1});  // |运算得1：任意一个为1
      
      res.first = min(to0, to0Change);
      res.second = min(to1, to1Change);
    } else {  // op == '|'
      // 不改运算符
      int to0 = l0 + r0;
      int to1 = min({l1 + r0, l0 + r1, l1 + r1});
      // 改运算符为&，额外+1
      int to0Change = 1 + min({l0 + r0, l0 + r1, l1 + r0});  // &运算得0：任意一个为0
      int to1Change = 1 + l1 + r1;  // &运算得1：必须1&1
      
      res.first = min(to0, to0Change);
      res.second = min(to1, to1Change);
    }
    
    valStack.push(res);
  };
  
  for (int i = 0; i < n; i++) {
    char c = expr[i];
    if (c == '0') {
      valStack.push({0, 1});  // 变成0代价0，变成1代价1
    } else if (c == '1') {
      valStack.push({1, 0});  // 变成0代价1，变成1代价0
    } else if (c == '(') {
      opStack.push(c);
    } else if (c == ')') {
      // 计算到左括号
      while (!opStack.empty() && opStack.top() != '(') {
        applyOp();
      }
      opStack.pop();  // 弹出'('
    } else if (c == '&' || c == '|') {
      // 由于&和|优先级相同，从左到右计算，所以先计算前面的
      while (!opStack.empty() && opStack.top() != '(') {
        applyOp();
      }
      opStack.push(c);
    }
  }
  
  // 处理剩余运算符
  while (!opStack.empty()) {
    applyOp();
  }
  
  auto finalRes = valStack.top();
  // 返回翻转最终值的代价
  // 如果最终值是0，返回变成1的代价；如果最终值是1，返回变成0的代价
  // 但注意最终值可能是0或1，我们需要的是"改变最终值"的代价
  // 表达式原始值：如果second==0则是1，如果first==0则是0
  // 但实际上first和second可能都不为0（都需要操作才能达到）
  // 我们需要知道原始值是什么
  
  // 重新思考：finalRes.first是变成0的最小代价，finalRes.second是变成1的最小代价
  // 哪个是原始值？代价为0的那个！
  if (finalRes.first == 0) {
    // 原始值是0，返回变成1的代价
    return finalRes.second;
  } else {
    // 原始值是1，返回变成0的代价
    return finalRes.first;
  }
}

// 优化：实际上可以只用一个栈，存储pair<cost0, cost1>
static int solution1(string expression) {
  return minOperationsToFlipImpl(expression);
}

MinimumCostToChangeTheFinalValueOfExpressionSolution::MinimumCostToChangeTheFinalValueOfExpressionSolution() {
  setMetaInfo({.id = 1896,
               .title = "Minimum Cost to Change the Final Value of Expression",
               .url = "https://leetcode.com/problems/minimum-cost-to-change-the-final-value-of-expression/"});
  registerStrategy("Stack DP", solution1);
}

int MinimumCostToChangeTheFinalValueOfExpressionSolution::minOperationsToFlip(string expression) {
  return getSolution()(expression);
}

}  // namespace problem_1896
}  // namespace leetcode
