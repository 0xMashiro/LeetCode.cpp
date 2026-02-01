#include "leetcode/problems/the-score-of-students-solving-math-expression.h"

namespace leetcode {
namespace problem_2019 {

/**
 * 计算正确答案（先乘后加）
 */
static int calculateCorrect(const std::string& s) {
  std::vector<int> nums;
  std::vector<char> ops;
  
  // 解析表达式
  for (int i = 0; i < s.size(); ++i) {
    if (isdigit(s[i])) {
      nums.push_back(s[i] - '0');
    } else {
      ops.push_back(s[i]);
    }
  }
  
  // 先计算所有乘法
  std::vector<int> new_nums;
  std::vector<char> new_ops;
  new_nums.push_back(nums[0]);
  
  for (int i = 0; i < ops.size(); ++i) {
    if (ops[i] == '*') {
      new_nums.back() *= nums[i + 1];
    } else {
      new_nums.push_back(nums[i + 1]);
      new_ops.push_back('+');
    }
  }
  
  // 再计算加法
  int result = 0;
  for (int num : new_nums) {
    result += num;
  }
  return result;
}

/**
 * 使用区间DP计算所有可能的错误答案
 * dp[i][j] 表示从第i个数字到第j个数字的所有可能结果
 */
static std::vector<std::vector<std::unordered_set<int>>> calculateWrongAnswers(
    const std::vector<int>& nums, const std::vector<char>& ops) {
  int n = nums.size();
  // dp[i][j] 存储区间[i,j]的所有可能结果
  std::vector<std::vector<std::unordered_set<int>>> dp(
      n, std::vector<std::unordered_set<int>>(n));
  
  // 初始化：单个数字
  for (int i = 0; i < n; ++i) {
    dp[i][i].insert(nums[i]);
  }
  
  // 区间长度从2到n
  for (int len = 2; len <= n; ++len) {
    for (int i = 0; i + len - 1 < n; ++i) {
      int j = i + len - 1;
      // 枚举分割点k（运算符位置）
      for (int k = i; k < j; ++k) {
        char op = ops[k];
        for (int left : dp[i][k]) {
          for (int right : dp[k + 1][j]) {
            int res;
            if (op == '+') {
              res = left + right;
            } else {
              res = left * right;
            }
            // 结果必须在[0, 1000]范围内（根据题目约束）
            if (res >= 0 && res <= 1000) {
              dp[i][j].insert(res);
            }
          }
        }
      }
    }
  }
  
  return dp;
}

static int solution1(std::string s, std::vector<int>& answers) {
  // 解析表达式，提取数字和运算符
  std::vector<int> nums;
  std::vector<char> ops;
  
  for (int i = 0; i < s.size(); ++i) {
    if (isdigit(s[i])) {
      nums.push_back(s[i] - '0');
    } else {
      ops.push_back(s[i]);
    }
  }
  
  // 计算正确答案
  int correct = calculateCorrect(s);
  
  // 计算所有可能的错误答案
  auto dp = calculateWrongAnswers(nums, ops);
  std::unordered_set<int> wrong_answers = dp[0][nums.size() - 1];
  
  // 统计得分
  int total_score = 0;
  for (int ans : answers) {
    if (ans == correct) {
      total_score += 5;
    } else if (wrong_answers.count(ans)) {
      total_score += 2;
    }
  }
  
  return total_score;
}

TheScoreOfStudentsSolvingMathExpressionSolution::TheScoreOfStudentsSolvingMathExpressionSolution() {
  setMetaInfo({.id = 2019,
               .title = "The Score of Students Solving Math Expression",
               .url = "https://leetcode.com/problems/the-score-of-students-solving-math-expression/"});
  registerStrategy("Interval DP", solution1);
}

int TheScoreOfStudentsSolvingMathExpressionSolution::scoreOfStudents(
    std::string s, std::vector<int>& answers) {
  return getSolution()(s, answers);
}

}  // namespace problem_2019
}  // namespace leetcode
