#include "leetcode/problems/mice-and-cheese.h"

namespace leetcode {
namespace problem_2611 {

// 贪心算法：选择额外收益最大的 k 个奶酪给第一只老鼠
// 1. 初始假设所有奶酪给第二只老鼠：sum(reward2)
// 2. 计算改给第一只老鼠的额外收益：reward1[i] - reward2[i]
// 3. 选择额外收益最大的 k 个
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static int solution1(vector<int>& reward1, vector<int>& reward2, int k) {
  const int n = reward1.size();
  
  // 计算额外收益：reward1[i] - reward2[i]
  vector<int> diff(n);
  long long total = 0;  // 使用 long long 防止溢出
  for (int i = 0; i < n; ++i) {
    diff[i] = reward1[i] - reward2[i];
    total += reward2[i];  // 初始假设都给第二只老鼠
  }
  
  // 按额外收益降序排序
  sort(diff.begin(), diff.end(), greater<int>());
  
  // 选择前 k 个额外收益最大的改给第一只老鼠
  for (int i = 0; i < k; ++i) {
    total += diff[i];
  }
  
  return static_cast<int>(total);
}

// 优化版本：使用 nth_element 获取前 k 大，平均 O(n)
// 时间复杂度: O(n) 平均, 空间复杂度: O(n)
static int solution2(vector<int>& reward1, vector<int>& reward2, int k) {
  const int n = reward1.size();
  
  if (k == 0) {
    // 第一只老鼠不吃任何奶酪
    long long total = 0;
    for (int x : reward2) total += x;
    return static_cast<int>(total);
  }
  
  if (k == n) {
    // 第一只老鼠吃所有奶酪
    long long total = 0;
    for (int x : reward1) total += x;
    return static_cast<int>(total);
  }
  
  vector<int> diff(n);
  long long total = 0;
  for (int i = 0; i < n; ++i) {
    diff[i] = reward1[i] - reward2[i];
    total += reward2[i];
  }
  
  // 使用 nth_element 将第 k 大的元素放到正确位置，左边都大于等于它
  nth_element(diff.begin(), diff.begin() + k, diff.end(), greater<int>());
  
  // 累加前 k 个最大的额外收益
  for (int i = 0; i < k; ++i) {
    total += diff[i];
  }
  
  return static_cast<int>(total);
}

MiceAndCheeseSolution::MiceAndCheeseSolution() {
  setMetaInfo({.id = 2611,
               .title = "Mice and Cheese",
               .url = "https://leetcode.com/problems/mice-and-cheese/"});
  registerStrategy("Greedy with Sort", solution1);
  registerStrategy("Greedy with nth_element", solution2);
}

int MiceAndCheeseSolution::miceAndCheese(vector<int>& reward1, 
                                          vector<int>& reward2, 
                                          int k) {
  return getSolution()(reward1, reward2, k);
}

}  // namespace problem_2611
}  // namespace leetcode
