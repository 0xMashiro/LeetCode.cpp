#include "leetcode/problems/last-remaining-integer-after-alternating-deletion-operations.h"

namespace leetcode {
namespace problem_3782 {

/**
 * 核心思路：数学模拟，追踪序列的起始位置、步长和长度
 * 
 * 序列始终保持等差数列，用 (head, step, count) 表示
 * 
 * 操作分析：
 * - 操作1（从左删，删第2,4,6...个）：
 *   第1个保留，第2个删，第3个保留...所以 head 不变，step *= 2
 *   剩余元素：count = (count + 1) / 2（向上取整）
 * 
 * - 操作2（从右删，从右边数删第2,4...个）：
 *   剩余元素数量 count 的奇偶性决定 head 是否变化：
 *   - count 为偶数：head += step（如 [1,3,5,7] → [3,7]，head 从1变3）
 *   - count 为奇数：head 不变（如 [1,3,5] → [1,5]，head 保持1）
 *   step *= 2, count = (count + 1) / 2
 * 
 * 验证 n=5：
 * [1,2,3,4,5] 
 * 操作1：删2,4 → [1,3,5], head=1, step=2, count=3
 * 操作2：count=3奇数，head不变，删从右第2个(3) → [1,5], head=1, step=4, count=2
 * 操作1：head不变，删第2个(5) → [1], head=1 ✓
 * 
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 */
static long long solution1(long long n) {
  long long head = 1;        // 当前序列的起始值
  long long step = 1;        // 当前序列的步长
  long long count = n;       // 当前序列元素个数
  bool left_to_right = true; // true=操作1(从左删), false=操作2(从右删)
  
  while (count > 1) {
    if (left_to_right) {
      // 操作1：从左删除，head 不变
    } else {
      // 操作2：从右删除，count为偶数时 head 移动
      if (count % 2 == 0) {
        head += step;
      }
    }
    
    step *= 2;
    count = (count + 1) / 2;  // 向上取整：删一半后剩余的数量
    left_to_right = !left_to_right;
  }
  
  return head;
}

LastRemainingIntegerAfterAlternatingDeletionOperationsSolution::LastRemainingIntegerAfterAlternatingDeletionOperationsSolution() {
  setMetaInfo({
    .id = 3782,
    .title = "Last Remaining Integer After Alternating Deletion Operations",
    .url = "https://leetcode.com/problems/last-remaining-integer-after-alternating-deletion-operations/"
  });
  registerStrategy("Mathematical Simulation", solution1);
}

long long LastRemainingIntegerAfterAlternatingDeletionOperationsSolution::lastInteger(long long n) {
  return getSolution()(n);
}

}  // namespace problem_3782
}  // namespace leetcode
