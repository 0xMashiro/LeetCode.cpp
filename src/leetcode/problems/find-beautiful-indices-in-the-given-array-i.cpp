#include "leetcode/problems/find-beautiful-indices-in-the-given-array-i.h"

namespace leetcode {
namespace problem_3006 {

// KMP 算法计算部分匹配表（前缀函数）
static vector<int> computeLPS(const string& pattern) {
  int m = pattern.size();
  vector<int> lps(m, 0);
  int len = 0;
  int i = 1;
  while (i < m) {
    if (pattern[i] == pattern[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }
  return lps;
}

// KMP 算法查找所有匹配位置
static vector<int> kmpSearch(const string& text, const string& pattern) {
  vector<int> positions;
  if (pattern.empty() || pattern.size() > text.size()) {
    return positions;
  }
  
  vector<int> lps = computeLPS(pattern);
  int n = text.size();
  int m = pattern.size();
  int i = 0;  // text 的索引
  int j = 0;  // pattern 的索引
  
  while (i < n) {
    if (text[i] == pattern[j]) {
      i++;
      j++;
      if (j == m) {
        positions.push_back(i - j);  // 找到匹配，记录起始位置
        j = lps[j - 1];
      }
    } else {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }
  return positions;
}

// 主解决方案
static vector<int> solution(string s, string a, string b, int k) {
  // 找出 a 和 b 在 s 中所有出现的位置
  vector<int> listA = kmpSearch(s, a);
  vector<int> listB = kmpSearch(s, b);
  
  vector<int> result;
  
  // 如果 b 没有出现，直接返回空
  if (listB.empty()) {
    return result;
  }
  
  // 双指针检查每个 listA 中的位置是否有匹配的 listB 中的位置
  int j = 0;
  for (int i : listA) {
    // 移动指针 j 直到 listB[j] >= i - k 或者超出范围
    while (j < listB.size() && listB[j] < i - k) {
      j++;
    }
    
    // 检查当前 j 或前一个位置是否满足条件
    if (j < listB.size() && abs(listB[j] - i) <= k) {
      result.push_back(i);
    } else if (j > 0 && abs(listB[j - 1] - i) <= k) {
      result.push_back(i);
    }
  }
  
  return result;
}

FindBeautifulIndicesInTheGivenArrayISolution::FindBeautifulIndicesInTheGivenArrayISolution() {
  setMetaInfo({
    .id = 3006,
    .title = "Find Beautiful Indices in the Given Array I",
    .url = "https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-i/"
  });
  registerStrategy("KMP + Two Pointers", solution);
}

vector<int> FindBeautifulIndicesInTheGivenArrayISolution::beautifulIndices(string s, string a, string b, int k) {
  return getSolution()(s, a, b, k);
}

}  // namespace problem_3006
}  // namespace leetcode
