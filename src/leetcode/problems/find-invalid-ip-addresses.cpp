#include "leetcode/problems/find-invalid-ip-addresses.h"

namespace leetcode {
namespace problem_3451 {

/**
 * 检查 IP 地址是否有效
 * 有效 IPv4 地址条件：
 * 1. 必须有且仅有 4 个 octet（由 '.' 分隔）
 * 2. 每个 octet 必须在 0-255 范围内
 * 3. 每个 octet 不能有前导零（除非是单独的 "0"）
 */
static bool isValidIP(const string& ip) {
  vector<string> octets;
  string current;
  
  // 按 '.' 分割 IP 地址
  for (char c : ip) {
    if (c == '.') {
      if (current.empty()) return false;  // 连续的 '.'
      octets.push_back(current);
      current.clear();
    } else {
      if (!isdigit(c)) return false;  // 非数字字符
      current += c;
    }
  }
  
  // 处理最后一个 octet
  if (!current.empty()) {
    octets.push_back(current);
  }
  
  // 检查 octet 数量
  if (octets.size() != 4) return false;
  
  // 检查每个 octet
  for (const string& octet : octets) {
    if (octet.empty()) return false;
    
    // 检查前导零
    if (octet.length() > 1 && octet[0] == '0') {
      return false;  // 有前导零（如 "01", "001"）
    }
    
    // 检查数值范围（避免溢出）
    if (octet.length() > 3) return false;  // 超过 3 位肯定大于 255
    
    // 安全转换为整数
    long long num = 0;
    for (char c : octet) {
      num = num * 10 + (c - '0');
    }
    
    if (num > 255) return false;
  }
  
  return true;
}

/**
 * 主要解决方案
 * 步骤：
 * 1. 遍历所有 IP，统计无效 IP 的出现次数
 * 2. 按出现次数降序、IP 降序排序
 * 3. 格式化输出
 */
static vector<string> solution1(vector<string>& ips) {
  unordered_map<string, int> invalidCount;
  
  // 统计每个无效 IP 的出现次数
  for (const string& ip : ips) {
    if (!isValidIP(ip)) {
      invalidCount[ip]++;
    }
  }
  
  // 转换为 vector 以便排序
  vector<pair<string, int>> result;
  for (const auto& [ip, count] : invalidCount) {
    result.emplace_back(ip, count);
  }
  
  // 按 count 降序，然后按 ip 降序排序
  sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
    if (a.second != b.second) {
      return a.second > b.second;  // count 降序
    }
    return a.first > b.first;  // ip 降序（字符串比较）
  });
  
  // 格式化输出
  vector<string> output;
  for (const auto& [ip, count] : result) {
    output.push_back(ip + " " + to_string(count));
  }
  
  return output;
}

FindInvalidIpAddressesSolution::FindInvalidIpAddressesSolution() {
  setMetaInfo({
    .id = 3451,
    .title = "Find Invalid IP Addresses",
    .url = "https://leetcode.com/problems/find-invalid-ip-addresses/"
  });
  registerStrategy("HashMap + Sort", solution1);
}

vector<string> FindInvalidIpAddressesSolution::findInvalidIpAddresses(vector<string>& ips) {
  return getSolution()(ips);
}

}  // namespace problem_3451
}  // namespace leetcode
