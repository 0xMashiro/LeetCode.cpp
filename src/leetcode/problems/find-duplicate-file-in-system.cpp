#include "leetcode/problems/find-duplicate-file-in-system.h"

namespace leetcode {
namespace problem_609 {

// 哈希表解法：按文件内容分组
// 时间复杂度: O(N * L)，N为paths长度，L为单个字符串平均长度
// 空间复杂度: O(N * L)
static vector<vector<string>> solution1(vector<string>& paths) {
  unordered_map<string, vector<string>> contentToFiles;
  
  for (const string& path : paths) {
    // 解析每个路径字符串
    size_t spacePos = path.find(' ');
    string directory = path.substr(0, spacePos);
    
    size_t i = spacePos + 1;
    while (i < path.size()) {
      // 找到左括号位置，分隔文件名和内容
      size_t leftParen = path.find('(', i);
      size_t rightParen = path.find(')', leftParen);
      
      string filename = path.substr(i, leftParen - i);
      string content = path.substr(leftParen + 1, rightParen - leftParen - 1);
      string fullPath = directory + "/" + filename;
      
      contentToFiles[content].push_back(fullPath);
      
      // 移动到下一个文件（跳过空格）
      i = rightParen + 2;
    }
  }
  
  // 只返回有重复的文件组（至少2个文件）
  vector<vector<string>> result;
  for (auto& [content, files] : contentToFiles) {
    if (files.size() >= 2) {
      result.push_back(files);
    }
  }
  
  return result;
}

FindDuplicateFileInSystemSolution::FindDuplicateFileInSystemSolution() {
  setMetaInfo({.id = 609,
               .title = "Find Duplicate File in System",
               .url = "https://leetcode.com/problems/find-duplicate-file-in-system/"});
  registerStrategy("Hash Map", solution1);
}

vector<vector<string>> FindDuplicateFileInSystemSolution::findDuplicate(vector<string>& paths) {
  return getSolution()(paths);
}

}  // namespace problem_609
}  // namespace leetcode
