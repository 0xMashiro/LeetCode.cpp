#include "leetcode/problems/text-justification.h"

namespace leetcode {
namespace problem_68 {

// 文本左右对齐
// 贪心策略：每行尽可能多地放置单词
// 时间复杂度: O(n * maxWidth), 空间复杂度: O(maxWidth) 用于构建每行
static vector<string> solution1(vector<string>& words, int maxWidth) {
  vector<string> result;
  int n = words.size();
  int i = 0;
  
  while (i < n) {
    // 确定当前行能放多少个单词
    int lineLength = words[i].length();
    int j = i + 1;
    
    // 尽可能多地放单词，加上至少一个空格
    while (j < n && lineLength + 1 + words[j].length() <= maxWidth) {
      lineLength += 1 + words[j].length();  // 1是空格，加上单词长度
      j++;
    }
    
    // 现在 words[i..j-1] 是当前行的单词
    int numWords = j - i;
    int numSpaces = maxWidth - lineLength + (numWords - 1);  // 需要填充的总空格数
    
    string line;
    
    // 最后一行或只有一个单词：左对齐
    if (j == n || numWords == 1) {
      line = words[i];
      for (int k = i + 1; k < j; k++) {
        line += " " + words[k];
      }
      // 末尾补空格
      line += string(maxWidth - line.length(), ' ');
    } else {
      // 普通行：均匀分配空格
      int spacePerSlot = numSpaces / (numWords - 1);  // 每个间隔的基础空格数
      int extraSpaces = numSpaces % (numWords - 1);   // 左边需要多分配一个空格的间隔数
      
      line = words[i];
      for (int k = i + 1; k < j; k++) {
        int spaces = spacePerSlot + (k - i - 1 < extraSpaces ? 1 : 0);
        line += string(spaces, ' ') + words[k];
      }
    }
    
    result.push_back(line);
    i = j;
  }
  
  return result;
}

TextJustificationSolution::TextJustificationSolution() {
  setMetaInfo({.id = 68,
               .title = "Text Justification",
               .url = "https://leetcode.com/problems/text-justification/"});
  registerStrategy("Greedy", solution1);
}

vector<string> TextJustificationSolution::fullJustify(vector<string>& words, int maxWidth) {
  return getSolution()(words, maxWidth);
}

}  // namespace problem_68
}  // namespace leetcode
