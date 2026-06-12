#include "leetcode/problems/odd-string-difference.h"

namespace leetcode {
namespace problem_2451 {

static string solution1(vector<string>& words) {
  auto getDiffKey = [](const string& w) -> string {
    string key;
    for (size_t i = 1; i < w.size(); ++i) {
      int diff = w[i] - w[i - 1];
      key.push_back(static_cast<char>(diff));
    }
    return key;
  };

  // 计算前三个的差值 key
  string key0 = getDiffKey(words[0]);
  string key1 = getDiffKey(words[1]);
  string key2 = getDiffKey(words[2]);

  // 判断标准 key：多数相同的就是标准
  string standardKey;
  if (key0 == key1 || key0 == key2) {
    standardKey = key0;
  } else {
    standardKey = key1;
  }

  // 找到与标准不同的那个
  if (getDiffKey(words[0]) != standardKey) return words[0];
  if (getDiffKey(words[1]) != standardKey) return words[1];
  // 从第三个开始逐个比较
  for (size_t i = 2; i < words.size(); ++i) {
    if (getDiffKey(words[i]) != standardKey) return words[i];
  }

  return "";  // 根据题目约束不会走到这里
}

OddStringDifferenceSolution::OddStringDifferenceSolution() {
  setMetaInfo({.id = 2451,
               .title = "Odd String Difference",
               .url = "https://leetcode.com/problems/odd-string-difference"});
  registerStrategy({.name = "Compare First Three"}, solution1);
}

string OddStringDifferenceSolution::oddString(vector<string>& words) {
  return getSolution()(words);
}

}  // namespace problem_2451
}  // namespace leetcode
