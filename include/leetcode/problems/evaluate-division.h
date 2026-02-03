#include "leetcode/core.h"

namespace leetcode {
namespace problem_399 {

using Func = std::function<vector<double>(vector<vector<string>>&, vector<double>&, vector<vector<string>>&)>;

/**
 * 399. Evaluate Division
 * https://leetcode.com/problems/evaluate-division/
 * 
 * 思路：将问题转化为图论问题
 * - 变量作为节点，等式作为带权有向边
 * - a/b=value 建立边 a->b(权重value) 和 b->a(权重1/value)
 * - 查询转化为求两点间路径的权重乘积
 * - 对每个查询使用DFS搜索路径
 * 
 * 时间复杂度：O(Q * (V+E))，Q为查询数，V为变量数，E为边数
 * 空间复杂度：O(V+E)
 */
class EvaluateDivisionSolution : public SolutionBase<Func> {
 public:
  vector<double> calcEquation(vector<vector<string>>& equations, 
                               vector<double>& values, 
                               vector<vector<string>>& queries);

  EvaluateDivisionSolution();
};

}  // namespace problem_399
}  // namespace leetcode
