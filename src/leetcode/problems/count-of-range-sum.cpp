#include "leetcode/problems/count-of-range-sum.h"

namespace leetcode {
namespace problem_327 {

/**
 * 使用归并排序统计满足条件的区间和数量
 * 时间复杂度: O(n log n), 空间复杂度: O(n)
 */
class RangeSumCounter {
 public:
  RangeSumCounter(vector<long long>& prefix, int lower, int upper)
      : prefix_(prefix), lower_(lower), upper_(upper) {}

  int count() {
    int n = prefix_.size();
    temp_.resize(n);
    return mergeSort(0, n - 1);
  }

 private:
  // 对 prefix[l..r] 进行归并排序，并返回该范围内满足条件的区间对数
  int mergeSort(int l, int r) {
    if (l >= r) return 0;

    int mid = l + (r - l) / 2;
    int count = mergeSort(l, mid) + mergeSort(mid + 1, r);

    // 统计左半部分[l..mid]和右半部分[mid+1..r]之间的有效区间对
    // 对于右半部分的每个 j，统计左半部分有多少 i 满足：
    // prefix[j] - upper <= prefix[i] <= prefix[j] - lower
    int left = l, right = l;
    for (int j = mid + 1; j <= r; ++j) {
      long long low_bound = prefix_[j] - upper_;
      long long high_bound = prefix_[j] - lower_;

      // 找到左半部分中第一个 >= low_bound 的位置
      while (left <= mid && prefix_[left] < low_bound) ++left;
      // 找到左半部分中第一个 > high_bound 的位置
      while (right <= mid && prefix_[right] <= high_bound) ++right;

      count += right - left;
    }

    // 归并两个有序数组
    merge(l, mid, r);
    return count;
  }

  void merge(int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
      if (prefix_[i] <= prefix_[j]) {
        temp_[k++] = prefix_[i++];
      } else {
        temp_[k++] = prefix_[j++];
      }
    }
    while (i <= mid) temp_[k++] = prefix_[i++];
    while (j <= r) temp_[k++] = prefix_[j++];

    for (i = l; i <= r; ++i) {
      prefix_[i] = temp_[i];
    }
  }

  vector<long long>& prefix_;
  vector<long long> temp_;
  int lower_;
  int upper_;
};

static int solution1(vector<int>& nums, int lower, int upper) {
  int n = nums.size();
  // 计算前缀和，prefix[i] 表示 nums[0..i-1] 的和
  vector<long long> prefix(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i] + nums[i];
  }

  RangeSumCounter counter(prefix, lower, upper);
  return counter.count();
}

CountOfRangeSumSolution::CountOfRangeSumSolution() {
  setMetaInfo({.id = 327,
               .title = "Count of Range Sum",
               .url = "https://leetcode.com/problems/count-of-range-sum/"});
  registerStrategy("Merge Sort", solution1);
}

int CountOfRangeSumSolution::countRangeSum(vector<int>& nums, int lower, int upper) {
  return getSolution()(nums, lower, upper);
}

}  // namespace problem_327
}  // namespace leetcode
