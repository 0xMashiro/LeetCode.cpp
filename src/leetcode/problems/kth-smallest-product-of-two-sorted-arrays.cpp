#include "leetcode/problems/kth-smallest-product-of-two-sorted-arrays.h"

namespace leetcode {
namespace problem_2040 {

/**
 * 计算乘积 <= x 的对数
 * 对于每个 nums1[i]，在 nums2 中找满足 nums1[i] * nums2[j] <= x 的个数
 * 使用二分查找直接比较，避免除法带来的取整问题
 */
static long long countLessEqual(const vector<int>& nums1,
                                const vector<int>& nums2, long long x) {
  long long count = 0;
  const int n2 = nums2.size();

  for (int num : nums1) {
    if (num > 0) {
      // num > 0: 找最大的 j 使得 num * nums2[j] <= x
      // 即 nums2[j] <= floor(x / num)
      // 使用二分查找：找第一个满足 num * nums2[j] > x 的位置
      int left = 0, right = n2;
      while (left < right) {
        int mid = left + (right - left) / 2;
        if ((long long)num * nums2[mid] <= x) {
          left = mid + 1;
        } else {
          right = mid;
        }
      }
      count += left;
    } else if (num < 0) {
      // num < 0: 找最小的 j 使得 num * nums2[j] <= x
      // 由于 num < 0，乘积随 nums2[j] 增大而减小
      // 使用二分查找：找第一个满足 num * nums2[j] <= x 的位置
      int left = 0, right = n2;
      while (left < right) {
        int mid = left + (right - left) / 2;
        if ((long long)num * nums2[mid] <= x) {
          // 当前和右侧都满足条件
          right = mid;
        } else {
          // 当前不满足，需要去右边找
          left = mid + 1;
        }
      }
      count += n2 - left;
    } else {
      // num == 0: 0 * nums2[j] = 0
      // 0 <= x 则所有 n2 个都满足，否则都不满足
      if (x >= 0) {
        count += n2;
      }
    }
  }
  return count;
}

/**
 * 二分查找第 k 小的乘积
 * 时间复杂度: O(n1 * log(n2) * log(range))
 * 空间复杂度: O(1)
 */
static long long solution1(vector<int>& nums1, vector<int>& nums2,
                           long long k) {
  // 确定二分查找的范围
  long long left =
      min({(long long)nums1.front() * nums2.front(),
           (long long)nums1.front() * nums2.back(),
           (long long)nums1.back() * nums2.front(),
           (long long)nums1.back() * nums2.back()});
  long long right =
      max({(long long)nums1.front() * nums2.front(),
           (long long)nums1.front() * nums2.back(),
           (long long)nums1.back() * nums2.front(),
           (long long)nums1.back() * nums2.back()});

  while (left < right) {
    long long mid = left + (right - left) / 2;
    long long cnt = countLessEqual(nums1, nums2, mid);
    if (cnt < k) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}

KthSmallestProductOfTwoSortedArraysSolution::
    KthSmallestProductOfTwoSortedArraysSolution() {
  setMetaInfo({.id = 2040,
               .title = "Kth Smallest Product of Two Sorted Arrays",
               .url =
                   "https://leetcode.com/problems/kth-smallest-product-of-two-"
                   "sorted-arrays/"});
  registerStrategy("Binary Search + Counting", solution1);
}

long long KthSmallestProductOfTwoSortedArraysSolution::kthSmallestProduct(
    vector<int>& nums1, vector<int>& nums2, long long k) {
  return getSolution()(nums1, nums2, k);
}

}  // namespace problem_2040
}  // namespace leetcode
