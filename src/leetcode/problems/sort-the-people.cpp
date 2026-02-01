#include "leetcode/problems/sort-the-people.h"

namespace leetcode {
namespace problem_2418 {

// 方法：配对排序
// 将 names 和 heights 配对，按 heights 降序排序，然后提取 names
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static vector<string> solution1(vector<string>& names, vector<int>& heights) {
  const int n = names.size();
  // 创建索引数组
  vector<int> indices(n);
  iota(indices.begin(), indices.end(), 0);  // 填充 0, 1, 2, ..., n-1
  
  // 按 heights 降序排序索引
  sort(indices.begin(), indices.end(), [&](int a, int b) {
    return heights[a] > heights[b];  // 降序
  });
  
  // 根据排序后的索引提取 names
  vector<string> result;
  result.reserve(n);
  for (int idx : indices) {
    result.push_back(names[idx]);
  }
  
  return result;
}

// 方法2：直接配对排序（更简洁）
// 将 (height, name) 配对，按 height 降序排序
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static vector<string> solution2(vector<string>& names, vector<int>& heights) {
  const int n = names.size();
  vector<pair<int, string>> pairs;  // (height, name)
  pairs.reserve(n);
  
  for (int i = 0; i < n; ++i) {
    pairs.emplace_back(heights[i], names[i]);
  }
  
  // 按 height 降序排序（pair 默认按 first 升序，需要自定义比较器）
  sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
    return a.first > b.first;  // 降序
  });
  
  // 提取 names
  vector<string> result;
  result.reserve(n);
  for (const auto& p : pairs) {
    result.push_back(p.second);
  }
  
  return result;
}

SortThePeopleSolution::SortThePeopleSolution() {
  setMetaInfo({
    .id = 2418,
    .title = "Sort the People",
    .url = "https://leetcode.com/problems/sort-the-people/"
  });
  registerStrategy("Index Sort", solution1);
  registerStrategy("Pair Sort", solution2);
}

vector<string> SortThePeopleSolution::sortPeople(vector<string>& names, vector<int>& heights) {
  return getSolution()(names, heights);
}

}  // namespace problem_2418
}  // namespace leetcode
