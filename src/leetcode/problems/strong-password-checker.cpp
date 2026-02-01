#include "leetcode/problems/strong-password-checker.h"

namespace leetcode {
namespace problem_420 {

/**
 * 强密码检查器
 * 
 * 思路：贪心算法，分三种情况处理
 * 
 * 1. 首先统计缺失的字符类型（小写、大写、数字）
 * 2. 找出所有连续重复字符序列的长度（≥3）
 * 
 * 对于连续重复序列的处理策略：
 * - 每3个连续字符需要1次替换来打破
 * - 删除操作可以节省替换次数：
 *   - 长度 % 3 == 0：删除1个可省1次替换
 *   - 长度 % 3 == 1：删除2个可省1次替换  
 *   - 长度 % 3 == 2：删除3个可省1次替换
 * 
 * 三种情况：
 * - 长度 < 6：需要插入，插入可同时解决类型缺失和连续重复
 * - 长度 > 20：需要删除，优先删除能节省替换的位置
 * - 6 ≤ 长度 ≤ 20：只需替换
 */
static int solution1(string password) {
  int n = password.size();
  
  // 检查缺失的字符类型
  bool hasLower = false, hasUpper = false, hasDigit = false;
  for (char c : password) {
    if (islower(c)) hasLower = true;
    else if (isupper(c)) hasUpper = true;
    else if (isdigit(c)) hasDigit = true;
  }
  int missingTypes = (!hasLower) + (!hasUpper) + (!hasDigit);
  
  // 情况1：长度小于6，需要插入
  if (n < 6) {
    // 需要插入 6-n 个字符
    // 插入操作可以同时解决：
    // 1. 长度不足
    // 2. 连续重复（在重复序列中间插入）
    // 3. 缺失的类型
    // 最优策略：插入位置优先选择连续重复序列
    return max(6 - n, missingTypes);
  }
  
  // 找出所有连续重复序列
  // 用 replace 统计需要的替换次数
  // 对于需要删除的情况，记录可以节省的替换次数
  
  int replace = 0;  // 需要的替换次数
  // oneSeq: 长度%3==0 的序列，删除1个可省1次替换
  // twoSeq: 长度%3==1 的序列，删除2个可省1次替换
  int oneSeq = 0, twoSeq = 0;  
  
  // 修正后的连续重复检测
  for (int i = 0; i < n; ) {
    int j = i;
    while (j < n && password[j] == password[i]) {
      j++;
    }
    int length = j - i;
    if (length >= 3) {
      // 每3个连续字符需要1次替换
      replace += length / 3;
      if (length % 3 == 0) oneSeq++;
      else if (length % 3 == 1) twoSeq++;
    }
    i = j;
  }
  
  // 情况2：长度大于20，需要删除
  if (n > 20) {
    int deleteCount = n - 20;  // 需要删除的字符数
    
    // 优先删除能节省替换的位置
    // 第一优先级：长度%3==0的序列，删除1个节省1次替换
    int use = min(deleteCount, oneSeq);
    replace -= use;
    deleteCount -= use;
    
    // 第二优先级：长度%3==1的序列，删除2个节省1次替换
    use = min(max(0, deleteCount / 2), twoSeq);
    replace -= use;
    deleteCount -= use * 2;
    
    // 第三优先级：长度%3==2的序列，删除3个节省1次替换
    replace -= deleteCount / 3;
    
    return (n - 20) + max(replace, missingTypes);
  }
  
  // 情况3：6 <= n <= 20，只需要替换
  // 每次替换可以：
  // 1. 打破3个连续重复
  // 2. 同时解决一个缺失的类型
  return max(replace, missingTypes);
}

StrongPasswordCheckerSolution::StrongPasswordCheckerSolution() {
  setMetaInfo({.id = 420,
               .title = "Strong Password Checker",
               .url = "https://leetcode.com/problems/strong-password-checker/"});
  registerStrategy("Greedy", solution1);
}

int StrongPasswordCheckerSolution::strongPasswordChecker(string password) {
  return getSolution()(password);
}

}  // namespace problem_420
}  // namespace leetcode
