#include "leetcode/problems/most-beautiful-item-for-each-query.h"

namespace leetcode {
namespace problem_2070 {

// 排序 + 前缀最大值 + 二分查找
// 时间复杂度: O((n+m) log n), n=items.length, m=queries.length
// 空间复杂度: O(n)
static vector<int> solution1(vector<vector<int>>& items, vector<int>& queries) {
  const int n = items.size();
  const int m = queries.size();
  
  // 按价格升序排序
  sort(items.begin(), items.end(), [](const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
  });
  
  // 预处理：对于每个价格，记录该价格及之前的最大美丽值
  // 使用 vector<pair<price, max_beauty>> 存储
  vector<pair<int, int>> priceBeauty;
  int maxBeauty = 0;
  for (const auto& item : items) {
    int price = item[0];
    int beauty = item[1];
    maxBeauty = max(maxBeauty, beauty);
    // 只记录价格变化时的最大美丽值（优化空间）
    if (priceBeauty.empty() || priceBeauty.back().first != price) {
      priceBeauty.push_back({price, maxBeauty});
    } else {
      // 相同价格，更新最大美丽值
      priceBeauty.back().second = maxBeauty;
    }
  }
  
  // 处理每个查询
  vector<int> answer(m, 0);
  for (int i = 0; i < m; ++i) {
    int query = queries[i];
    
    // 二分查找最后一个价格 <= query 的位置
    int left = 0, right = priceBeauty.size() - 1;
    int result = -1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (priceBeauty[mid].first <= query) {
        result = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    
    if (result != -1) {
      answer[i] = priceBeauty[result].second;
    }
    // 否则保持为 0（没有价格 <= query 的商品）
  }
  
  return answer;
}

// 优化版本：使用 upper_bound 简化二分查找
// 时间复杂度: O((n+m) log n)
// 空间复杂度: O(n)
static vector<int> solution2(vector<vector<int>>& items, vector<int>& queries) {
  const int n = items.size();
  const int m = queries.size();
  
  // 按价格升序排序
  sort(items.begin(), items.end(), [](const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
  });
  
  // 预处理：构建价格数组和前缀最大美丽值数组
  vector<int> prices;
  vector<int> maxBeauties;
  int currentMax = 0;
  
  for (const auto& item : items) {
    int price = item[0];
    int beauty = item[1];
    currentMax = max(currentMax, beauty);
    
    // 去重：相同价格只保留最后一个（有最大美丽值）
    if (prices.empty() || prices.back() != price) {
      prices.push_back(price);
      maxBeauties.push_back(currentMax);
    } else {
      maxBeauties.back() = currentMax;
    }
  }
  
  // 处理每个查询
  vector<int> answer(m);
  for (int i = 0; i < m; ++i) {
    // upper_bound 返回第一个 > query 的位置
    auto it = upper_bound(prices.begin(), prices.end(), queries[i]);
    if (it == prices.begin()) {
      answer[i] = 0;  // 所有价格都 > query
    } else {
      --it;
      int idx = distance(prices.begin(), it);
      answer[i] = maxBeauties[idx];
    }
  }
  
  return answer;
}

MostBeautifulItemForEachQuerySolution::MostBeautifulItemForEachQuerySolution() {
  setMetaInfo({.id = 2070,
               .title = "Most Beautiful Item for Each Query",
               .url = "https://leetcode.com/problems/most-beautiful-item-for-each-query/"});
  registerStrategy("Binary Search Manual", solution1);
  registerStrategy("Binary Search STL", solution2);
}

vector<int> MostBeautifulItemForEachQuerySolution::maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
  return getSolution()(items, queries);
}

}  // namespace problem_2070
}  // namespace leetcode
