#include "leetcode/problems/previous-permutation-with-one-swap.h"

namespace leetcode {
namespace problem_1053 {

/**
 * 算法思路：寻找"上一个排列"
 * 
 * 题目要求：找到字典序最大的、比 arr 小的排列，且只能通过一次交换得到。
 * 
 * 关键观察：
 * 对于每个可能的交换，我们需要比较交换后的结果，选择字典序最大的且小于原数组的。
 * 为了高效找到这个交换，我们：
 * 
 * 1. 从左向右找到第一个满足 arr[i] > arr[i+1] 的位置 i
 *    - 这个位置说明可以通过交换使得排列变小
 *    - 但我们需要在右侧找到小于 arr[i] 的最大值进行交换
 * 
 * 2. 在 i 的右侧找到小于 arr[i] 的最大元素 arr[j]
 *    - 从右向左扫描，找到第一个小于 arr[i] 的元素
 *    - 然后继续向左找是否有相等的元素（选择最左边的相同最大值）
 * 
 * 3. 交换 arr[i] 和 arr[j]
 * 
 * 但等等，对于 [3,2,1]，如果从左找 i=0，交换后得到 [2,3,1] 或 [1,2,3]，不是 [3,1,2]
 * 
 * 重新分析 [3,2,1] -> [3,1,2]：
 * - 交换的是位置 1 和 2（2 和 1）
 * - 这意味着 i=1，不是 i=0
 * 
 * 关键区别：
 * - 对于 [3,2,1]，选择最右边的下降点 i=1
 * - 对于 [1,5,3,4,2] -> [1,4,3,5,2]，选择最左边的下降点 i=1
 * 
 * 规律：应该选择能使得交换后结果最大的那个下降点
 * 对于 [3,2,1]，选 i=0 得到 [2,3,1]，选 i=1 得到 [3,1,2]，[3,1,2] > [2,3,1]
 * 对于 [1,5,3,4,2]，选 i=1 得到 [1,4,3,5,2]，选 i=3 得到 [1,5,3,2,4]，[1,4,3,5,2] > [1,5,3,2,4]（因为第二位 4 > 2 是错的，实际上 4 < 5，所以 [1,4,...] < [1,5,...]）
 * 
 * 等等，[1,4,3,5,2] 和 [1,5,3,2,4] 比较：
 * - 第一位相同
 * - 第二位 4 < 5，所以 [1,4,...] < [1,5,...]
 * 
 * 所以 [1,5,3,2,4] > [1,4,3,5,2]！
 * 
 * 这意味着对于 [1,5,3,4,2]，正确的选择应该是 i=3，结果是 [1,5,3,2,4]
 * 但题目预期是 [1,4,3,5,2]
 * 
 * 让我重新验证 [1,5,3,4,2] 的所有可能交换结果...
 * 
 * 实际上，我之前的测试用例预期可能有误。让我按照题目的三个示例来验证算法。
 * 
 * 根据题目示例：
 * - [3,2,1] -> [3,1,2]：选择 i=1（最右边的下降点）
 * - [1,9,4,6,7] -> [1,7,4,6,9]：选择 i=1（唯一的下降点）
 * 
 * 看来正确的策略是选择最右边的下降点！
 * 
 * 时间复杂度: O(n)，空间复杂度: O(1)
 */
static vector<int> solution1(vector<int>& arr) {
  const int n = arr.size();
  if (n <= 1) return arr;
  
  // 步骤1：从右向左找第一个 arr[i] > arr[i+1]
  // 选择最右边的下降点
  int i = n - 2;
  while (i >= 0 && arr[i] <= arr[i + 1]) {
    --i;
  }
  
  // 如果没有找到，说明数组是升序的，无法得到更小的排列
  if (i < 0) return arr;
  
  // 步骤2：在右侧找到小于 arr[i] 的最大元素
  // 从右向左扫描，第一个小于 arr[i] 的就是最大的（因为右侧是升序的）
  int j = n - 1;
  while (j > i && arr[j] >= arr[i]) {
    --j;
  }
  
  // 如果有多个相同的最大值，选择最左边的那个
  // 这样可以保证交换后的结果字典序最大
  while (j > i && arr[j - 1] == arr[j]) {
    --j;
  }
  
  // 步骤3：交换
  swap(arr[i], arr[j]);
  return arr;
}

PreviousPermutationWithOneSwapSolution::PreviousPermutationWithOneSwapSolution() {
  setMetaInfo({
    .id = 1053,
    .title = "Previous Permutation With One Swap",
    .url = "https://leetcode.com/problems/previous-permutation-with-one-swap/"
  });
  registerStrategy("Greedy", solution1);
}

vector<int> PreviousPermutationWithOneSwapSolution::prevPermOpt1(vector<int>& arr) {
  return getSolution()(arr);
}

}  // namespace problem_1053
}  // namespace leetcode