
#include "leetcode/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays.h"

namespace leetcode {
namespace problem_3430 {

/**
 * 计算以每个位置为结束、长度不超过k的子数组中，nums[i]作为最小值的贡献
 * 
 * 思路：使用单调栈找到左边第一个严格小于nums[i]的位置L
 * 对于以i结尾的子数组，起始位置可以是 [max(L+1, i-k+1), i] 范围内的任意位置
 * 同时需要考虑右边边界限制（但这里我们先计算单侧）
 * 
 * 更通用的方法：计算nums[i]作为最小值出现在多少个子数组中
 * - left[i]: 左边严格小于nums[i]的位置
 * - right[i]: 右边小于等于nums[i]的位置
 * 子数组起始位置范围: (left[i], i], 共 leftCount = i - left[i] 种
 * 子数组结束位置范围: [i, right[i]), 共 rightCount = right[i] - i 种
 * 
 * 对于长度不超过k的限制：
 * 需要统计满足 end - start + 1 <= k 的 (start, end) 对数
 * 即 end - start < k，也就是 start > end - k
 * 
 * 设 start ∈ (left[i], i], end ∈ [i, right[i])
 * 需要满足: start >= end - k + 1 (即子数组长度不超过k)
 * 
 * 对于固定的end，start的合法范围是: (left[i], min(i, end)] ∩ [end-k+1, +∞)
 * 
 * 优化计算：枚举较短的边界
 */

// 计算nums[i]作为最小值的贡献和（考虑长度不超过k的限制）
static long long calcMinSum(const vector<int>& nums, int k) {
    const int n = nums.size();
    vector<int> left(n, -1), right(n, n);
    stack<int> stk;
    
    // 找左边第一个严格小于的位置
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && nums[stk.top()] >= nums[i]) {
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
    }
    
    while (!stk.empty()) stk.pop();
    
    // 找右边第一个小于等于的位置（避免重复计算）
    for (int i = n - 1; i >= 0; --i) {
        while (!stk.empty() && nums[stk.top()] > nums[i]) {
            stk.pop();
        }
        right[i] = stk.empty() ? n : stk.top();
        stk.push(i);
    }
    
    long long total = 0;
    
    for (int i = 0; i < n; ++i) {
        // 左边可选位置: (left[i], i], 即 [left[i]+1, i]
        // 右边可选位置: [i, right[i])
        // 需要子数组长度不超过k，即: end - start + 1 <= k
        
        int L = left[i] + 1;  // 最左可开始位置
        int R = right[i] - 1; // 最右可结束位置
        
        // 枚举较短的边界来计算
        long long count = 0;
        
        // 枚举所有可能的结束位置 end ∈ [i, R]
        // 对于每个end，start必须满足: max(L, end-k+1) <= start <= i
        for (int end = i; end <= R && end < i + k; ++end) {
            int minStart = max(L, end - k + 1);
            int maxStart = i;
            if (minStart <= maxStart) {
                count += (maxStart - minStart + 1);
            }
        }
        
        total += (long long)nums[i] * count;
    }
    
    return total;
}

// 优化版本：O(n) 计算
static long long calcMinSumOptimized(const vector<int>& nums, int k) {
    const int n = nums.size();
    vector<int> left(n, -1), right(n, n);
    stack<int> stk;
    
    // 找左边第一个严格小于的位置
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && nums[stk.top()] >= nums[i]) {
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
    }
    
    while (!stk.empty()) stk.pop();
    
    // 找右边第一个小于等于的位置
    for (int i = n - 1; i >= 0; --i) {
        while (!stk.empty() && nums[stk.top()] > nums[i]) {
            stk.pop();
        }
        right[i] = stk.empty() ? n : stk.top();
        stk.push(i);
    }
    
    long long total = 0;
    
    for (int i = 0; i < n; ++i) {
        int l = left[i] + 1;      // 最小起始位置
        int r = right[i] - 1;     // 最大结束位置
        
        // 我们需要统计满足 start∈[l,i], end∈[i,r], end-start+1<=k 的(start,end)对数
        // 即 end - start < k, 即 start > end - k
        
        // 枚举start在[l,i]范围内
        // 对于start，end的范围是[i, min(r, start+k-1)]
        
        // 找到临界点：当start <= r-k+1时，end最大为start+k-1
        // 当start > r-k+1时，end最大为r
        
        long long cnt = 0;
        
        // start ∈ [l, min(i, r-k+1)] 时，end ∈ [i, start+k-1]
        int mid = min(i, r - k + 1);
        if (l <= mid) {
            // 等差数列求和: 对于start=l, 有(l+k-1)-i+1 = l+k-i个end可选
            // 对于start=mid, 有mid+k-i个end可选
            long long first = l + k - i;  // start=l时的可选end数
            long long last = mid + k - i; // start=mid时的可选end数
            long long num = mid - l + 1;
            cnt += (first + last) * num / 2;
        }
        
        // start ∈ [max(l, r-k+2), i] 时，end ∈ [i, r]
        int start2 = max(l, r - k + 2);
        if (start2 <= i) {
            long long endChoices = r - i + 1;
            cnt += endChoices * (i - start2 + 1);
        }
        
        total += (long long)nums[i] * cnt;
    }
    
    return total;
}

// 计算nums[i]作为最大值的贡献和（考虑长度不超过k的限制）
static long long calcMaxSumOptimized(const vector<int>& nums, int k) {
    const int n = nums.size();
    vector<int> left(n, -1), right(n, n);
    stack<int> stk;
    
    // 找左边第一个严格大于的位置
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && nums[stk.top()] <= nums[i]) {
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
    }
    
    while (!stk.empty()) stk.pop();
    
    // 找右边第一个大于等于的位置
    for (int i = n - 1; i >= 0; --i) {
        while (!stk.empty() && nums[stk.top()] < nums[i]) {
            stk.pop();
        }
        right[i] = stk.empty() ? n : stk.top();
        stk.push(i);
    }
    
    long long total = 0;
    
    for (int i = 0; i < n; ++i) {
        int l = left[i] + 1;      // 最小起始位置
        int r = right[i] - 1;     // 最大结束位置
        
        long long cnt = 0;
        
        // start ∈ [l, min(i, r-k+1)] 时，end ∈ [i, start+k-1]
        int mid = min(i, r - k + 1);
        if (l <= mid) {
            long long first = l + k - i;
            long long last = mid + k - i;
            long long num = mid - l + 1;
            cnt += (first + last) * num / 2;
        }
        
        // start ∈ [max(l, r-k+2), i] 时，end ∈ [i, r]
        int start2 = max(l, r - k + 2);
        if (start2 <= i) {
            long long endChoices = r - i + 1;
            cnt += endChoices * (i - start2 + 1);
        }
        
        total += (long long)nums[i] * cnt;
    }
    
    return total;
}

// 主解法
static long long solution1(vector<int>& nums, int k) {
    return calcMinSumOptimized(nums, k) + calcMaxSumOptimized(nums, k);
}

MaximumAndMinimumSumsOfAtMostSizeKSubarraysSolution::MaximumAndMinimumSumsOfAtMostSizeKSubarraysSolution() {
    setMetaInfo({
        .id = 3430,
        .title = "Maximum and Minimum Sums of at Most Size K Subarrays",
        .url = "https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/"
    });
    registerStrategy("Monotonic Stack + Contribution", solution1);
}

long long MaximumAndMinimumSumsOfAtMostSizeKSubarraysSolution::minMaxSubarraySum(vector<int>& nums, int k) {
    return getSolution()(nums, k);
}

}  // namespace problem_3430
}  // namespace leetcode
