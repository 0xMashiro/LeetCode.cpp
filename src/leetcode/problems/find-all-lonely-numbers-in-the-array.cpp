#include "leetcode/problems/find-all-lonely-numbers-in-the-array.h"

namespace leetcode {
namespace problem_2150 {

// 哈希表计数
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution1(vector<int>& nums) {
  unordered_map<int, int> count;
  for (int num : nums) {
    count[num]++;
  }
  
  vector<int> result;
  for (int num : nums) {
    // 检查是否是 lonely: 出现一次，且邻居都不在
    if (count[num] == 1 && count.count(num - 1) == 0 && count.count(num + 1) == 0) {
      result.push_back(num);
    }
  }
  return result;
}

FindAllLonelyNumbersInTheArraySolution::FindAllLonelyNumbersInTheArraySolution() {
  setMetaInfo({.id = 2150,
               .title = "Find All Lonely Numbers in the Array",
               .url = "https://leetcode.com/problems/find-all-lonely-numbers-in-the-array/"});
  registerStrategy("Hash Map Count", solution1);
}

vector<int> FindAllLonelyNumbersInTheArraySolution::findLonely(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2150
}  // namespace leetcode
