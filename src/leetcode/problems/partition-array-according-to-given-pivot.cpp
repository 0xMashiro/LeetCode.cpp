#include "leetcode/problems/partition-array-according-to-given-pivot.h"

namespace leetcode {
namespace problem_2161 {

// 三路分区：使用三个数组分别存储小于、等于、大于 pivot 的元素
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution1(vector<int>& nums, int pivot) {
  vector<int> less;      // 存储小于 pivot 的元素
  vector<int> equal;     // 存储等于 pivot 的元素
  vector<int> greater;   // 存储大于 pivot 的元素

  // 遍历数组，将元素分类
  for (int num : nums) {
    if (num < pivot) {
      less.push_back(num);
    } else if (num == pivot) {
      equal.push_back(num);
    } else {
      greater.push_back(num);
    }
  }

  // 按顺序拼接：小于 + 等于 + 大于
  vector<int> result;
  result.reserve(nums.size());
  result.insert(result.end(), less.begin(), less.end());
  result.insert(result.end(), equal.begin(), equal.end());
  result.insert(result.end(), greater.begin(), greater.end());

  return result;
}

// 双指针方法：单次遍历，原地构建结果数组
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution2(vector<int>& nums, int pivot) {
  const int n = nums.size();
  vector<int> result(n);
  
  // 先统计小于和等于 pivot 的元素个数
  int lessCount = 0;
  int equalCount = 0;
  for (int num : nums) {
    if (num < pivot) {
      ++lessCount;
    } else if (num == pivot) {
      ++equalCount;
    }
  }

  // 三个指针分别指向三个区间的起始位置
  int lessIdx = 0;
  int equalIdx = lessCount;
  int greaterIdx = lessCount + equalCount;

  // 再次遍历，将元素放入正确位置
  for (int num : nums) {
    if (num < pivot) {
      result[lessIdx++] = num;
    } else if (num == pivot) {
      result[equalIdx++] = num;
    } else {
      result[greaterIdx++] = num;
    }
  }

  return result;
}

PartitionArrayAccordingToGivenPivotSolution::PartitionArrayAccordingToGivenPivotSolution() {
  setMetaInfo({.id = 2161,
               .title = "Partition Array According to Given Pivot",
               .url = "https://leetcode.com/problems/partition-array-according-to-given-pivot/"});
  registerStrategy("Three-way Partition", solution1);
  registerStrategy("Two Pointer", solution2);
}

vector<int> PartitionArrayAccordingToGivenPivotSolution::pivotArray(vector<int>& nums, int pivot) {
  return getSolution()(nums, pivot);
}

}  // namespace problem_2161
}  // namespace leetcode
