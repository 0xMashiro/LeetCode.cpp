#include "leetcode/core.h"

namespace leetcode {
namespace problem_3451 {

using Func = std::function<vector<string>(vector<string>&)>;

/**
 * Find Invalid IP Addresses
 * https://leetcode.com/problems/find-invalid-ip-addresses/
 * 
 * 题目要求：
 * 给定 IP 地址列表，找出所有无效的 IPv4 地址。
 * 无效条件：
 * 1. 任何一个 octet > 255
 * 2. 任何一个 octet 有前导零（如 01）
 * 3. octet 数量不为 4
 * 
 * 返回格式：每个元素为 "ip count"，按 count 降序、ip 降序排序
 */
class FindInvalidIpAddressesSolution : public SolutionBase<Func> {
 public:
  //! 3451. Find Invalid IP Addresses
  //! https://leetcode.com/problems/find-invalid-ip-addresses/
  vector<string> findInvalidIpAddresses(vector<string>& ips);

  FindInvalidIpAddressesSolution();
};

}  // namespace problem_3451
}  // namespace leetcode
