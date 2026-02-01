#include "leetcode/core.h"

namespace leetcode {
namespace problem_2019 {

using Func = std::function<int(std::string, std::vector<int>&)>;

/**
 * 2019. The Score of Students Solving Math Expression
 * https://leetcode.com/problems/the-score-of-students-solving-math-expression/
 *
 * 思路：
 * 1. 计算正确答案：按照先乘后加的规则
 * 2. 使用区间DP计算所有可能的错误答案（所有加括号方式）
 * 3. 统计学生得分：正确答案5分，错误顺序但计算正确2分，其他0分
 */
class TheScoreOfStudentsSolvingMathExpressionSolution : public SolutionBase<Func> {
 public:
  int scoreOfStudents(std::string s, std::vector<int>& answers);

  TheScoreOfStudentsSolvingMathExpressionSolution();
};

}  // namespace problem_2019
}  // namespace leetcode
