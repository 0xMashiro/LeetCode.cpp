#include "leetcode/problems/maximum-element-after-decreasing-and-rearranging.h"

#include <algorithm>
#include <vector>

namespace leetcode {
namespace problem_1846 {

// 排序后贪心构建：arr[0] = 1，后续每个元素取 min(原值, 前值+1)
// 时间复杂度: O(n log n)
// 空间复杂度: O(1)（不计排序栈深度）
static int greedySorting(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
    arr[0] = 1;
    const int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; ++i) {
        arr[i] = std::min(arr[i], arr[i - 1] + 1);
    }
    return arr.back();
}

MaximumElementAfterDecreasingAndRearrangingSolution::MaximumElementAfterDecreasingAndRearrangingSolution() {
    setMetaInfo({.id = 1846,
                 .title = "Maximum Element After Decreasing and Rearranging",
                 .url = "https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/"});
    registerStrategy({.name = "Greedy Sorting",
                      .expected = "Accepted",
                      .time_complexity = "O(n log n)",
                      .space_complexity = "O(1)",
                      .tags = {"Array", "Greedy", "Sorting"}},
                     greedySorting);
}

int MaximumElementAfterDecreasingAndRearrangingSolution::maximumElementAfterDecrementingAndRearranging(std::vector<int>& arr) {
    return getSolution()(arr);
}

}  // namespace problem_1846
}  // namespace leetcode
