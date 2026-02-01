#include "leetcode/core.h"

namespace leetcode {
namespace problem_192 {

using Func = std::function<vector<pair<string, int>>(const string&)>;

/**
 * Word Frequency 解决方案
 * 统计文本中每个单词的出现频率，并按频率降序返回
 */
class WordFrequencySolution : public SolutionBase<Func> {
 public:
  //! 192. Word Frequency
  //! https://leetcode.com/problems/word-frequency/
  vector<pair<string, int>> wordFrequency(const string& content);

  WordFrequencySolution();
};

}  // namespace problem_192
}  // namespace leetcode
