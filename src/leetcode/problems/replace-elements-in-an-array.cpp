#include "leetcode/problems/replace-elements-in-an-array.h"

namespace leetcode {
namespace problem_2295 {

// 哈希表优化：建立值到索引的映射
// 时间复杂度: O(n + m), 空间复杂度: O(n)
static vector<int> solution1(vector<int>& nums, vector<vector<int>>& operations) {
  // 建立值到索引的映射
  unordered_map<int, int> valToIndex;
  for (int i = 0; i < nums.size(); ++i) {
    valToIndex[nums[i]] = i;
  }
  
  // 处理每个操作
  for (const auto& op : operations) {
    int oldVal = op[0];
    int newVal = op[1];
    
    // 找到 oldVal 的索引
    int idx = valToIndex[oldVal];
    
    // 替换数组中的值
    nums[idx] = newVal;
    
    // 更新哈希表
    valToIndex.erase(oldVal);
    valToIndex[newVal] = idx;
  }
  
  return nums;
}

ReplaceElementsInAnArraySolution::ReplaceElementsInAnArraySolution() {
  setMetaInfo({.id = 2295,
               .title = "Replace Elements in an Array",
               .url = "https://leetcode.com/problems/replace-elements-in-an-array/"});
  registerStrategy("Hash Map", solution1);
}

vector<int> ReplaceElementsInAnArraySolution::arrayChange(vector<int>& nums, 
                                                          vector<vector<int>>& operations) {
  return getSolution()(nums, operations);
}

}  // namespace problem_2295
}  // namespace leetcode
