#include "leetcode/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter.h"

namespace leetcode {
namespace problem_2030 {

// 单调栈（贪心）—— 本题结构唯一合理解为 O(n) 单调栈，无明显多解
// 核心思路：类似 "Remove K Digits" 的最小字典序子序列问题，
// 但额外约束 letter 必须出现至少 repetition 次。
// 在决定是否弹出栈顶时，需同时检查三个条件：
//   1. 标准单调栈条件：c < stk.back() （保持字典序最小）
//   2. 非 letter 过量条件：栈中非 letter 数量 > k - repetition，且当前字符是 letter
//      此时即使 letter 字典序较大，也应弹出非 letter 为其"腾位置"
//   3. 弹出后剩余字符仍能凑齐 k 个且满足 repetition 要求
// 预处理后缀中 letter 出现次数，O(1) 检查剩余可用 letter 数量。
// 时间复杂度: O(n), 空间复杂度: O(n)
static string solution1(string s, int k, char letter, int repetition) {
    int n = s.size();
    
    // 预处理后缀中 letter 的数量
    vector<int> suffixLetter(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        suffixLetter[i] = suffixLetter[i + 1] + (s[i] == letter ? 1 : 0);
    }
    
    vector<char> stk;
    int letterInStack = 0;
    int maxNonLetter = k - repetition;  // 最终答案中最多允许的非 letter 数量
    
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        int remaining = n - i;  // 剩余可用字符数（含当前字符 s[i]）
        
        // 尝试弹出栈顶
        while (!stk.empty()) {
            bool canPop = false;
            
            // 条件 A：标准单调栈条件 —— 当前字符更小，可改善字典序
            if (c < stk.back()) canPop = true;
            
            // 条件 B：栈中非 letter 过多，且当前字符是 letter，需要给它腾位置
            if (c == letter && stk.back() != letter &&
                (int)stk.size() - letterInStack > maxNonLetter) {
                canPop = true;
            }
            
            if (!canPop) break;
            
            // 约束 1：弹出后剩余字符是否足够凑齐 k 个？
            if ((int)stk.size() - 1 + remaining < k) break;
            
            // 约束 2：弹出后剩余 letter 是否足够满足 repetition？
            int newLetterCount = letterInStack - (stk.back() == letter ? 1 : 0);
            if (newLetterCount + suffixLetter[i] < repetition) break;
            
            // 弹出栈顶
            if (stk.back() == letter) --letterInStack;
            stk.pop_back();
        }
        
        stk.push_back(c);
        if (c == letter) ++letterInStack;
    }
    
    // 取前 k 个字符作为答案
    return string(stk.begin(), stk.begin() + k);
}

SmallestKLengthSubsequenceWithOccurrencesOfALetterSolution::SmallestKLengthSubsequenceWithOccurrencesOfALetterSolution() {
    setMetaInfo({.id = 2030,
                 .title = "Smallest K-Length Subsequence With Occurrences of a Letter",
                 .url = "https://leetcode.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/"});
    // @expected: AC
    registerStrategy("Monotonic Stack (Greedy)", solution1);
}

string SmallestKLengthSubsequenceWithOccurrencesOfALetterSolution::smallestSubsequence(string s, int k, char letter, int repetition) {
    return getSolution()(s, k, letter, repetition);
}

}  // namespace problem_2030
}  // namespace leetcode
