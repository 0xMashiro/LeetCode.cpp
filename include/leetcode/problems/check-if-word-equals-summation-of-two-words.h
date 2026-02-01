#include "leetcode/core.h"

namespace leetcode {
namespace problem_1880 {

using Func = std::function<bool(string, string, string)>;

/**
 * 1880. Check if Word Equals Summation of Two Words
 * https://leetcode.com/problems/check-if-word-equals-summation-of-two-words/
 * 
 * 思路：将每个单词转换为对应的数值（a-j 对应 0-9），然后比较两数之和是否等于第三数
 * 时间复杂度：O(n)，其中 n 为三个字符串总长度
 * 空间复杂度：O(1)
 */
class CheckIfWordEqualsSummationOfTwoWordsSolution : public SolutionBase<Func> {
 public:
  bool isSumEqual(string firstWord, string secondWord, string targetWord);

  CheckIfWordEqualsSummationOfTwoWordsSolution();
};

}  // namespace problem_1880
}  // namespace leetcode
