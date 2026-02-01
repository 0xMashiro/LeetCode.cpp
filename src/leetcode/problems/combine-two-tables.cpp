#include "leetcode/problems/combine-two-tables.h"

namespace leetcode {
namespace problem_175 {

// 使用哈希表模拟 LEFT JOIN
// 时间复杂度: O(n + m), 空间复杂度: O(m)
// n = person.size(), m = address.size()
static vector<ResultRow> solution1(vector<Person>& person, vector<Address>& address) {
  // 建立 personId 到 Address 的映射
  unordered_map<int, Address*> addressMap;
  for (auto& addr : address) {
    addressMap[addr.personId] = &addr;
  }
  
  vector<ResultRow> result;
  result.reserve(person.size());
  
  // 遍历 Person 表，进行 LEFT JOIN
  for (auto& p : person) {
    optional<string> city = nullopt;
    optional<string> state = nullopt;
    
    auto it = addressMap.find(p.personId);
    if (it != addressMap.end()) {
      city = it->second->city;
      state = it->second->state;
    }
    
    result.emplace_back(p.firstName, p.lastName, city, state);
  }
  
  return result;
}

// 排序 + 双指针方法
// 时间复杂度: O(n log n + m log m), 空间复杂度: O(1) (不算结果)
static vector<ResultRow> solution2(vector<Person>& person, vector<Address>& address) {
  // 按 personId 排序
  auto personSorted = person;
  auto addressSorted = address;
  
  sort(personSorted.begin(), personSorted.end(), 
       [](const Person& a, const Person& b) { return a.personId < b.personId; });
  sort(addressSorted.begin(), addressSorted.end(),
       [](const Address& a, const Address& b) { return a.personId < b.personId; });
  
  vector<ResultRow> result;
  result.reserve(person.size());
  
  size_t j = 0;
  for (auto& p : personSorted) {
    optional<string> city = nullopt;
    optional<string> state = nullopt;
    
    // 找到匹配的 address
    while (j < addressSorted.size() && addressSorted[j].personId < p.personId) {
      ++j;
    }
    
    if (j < addressSorted.size() && addressSorted[j].personId == p.personId) {
      city = addressSorted[j].city;
      state = addressSorted[j].state;
    }
    
    result.emplace_back(p.firstName, p.lastName, city, state);
  }
  
  return result;
}

CombineTwoTablesSolution::CombineTwoTablesSolution() {
  setMetaInfo({.id = 175,
               .title = "Combine Two Tables",
               .url = "https://leetcode.com/problems/combine-two-tables/"});
  registerStrategy("Hash Map (LEFT JOIN)", solution1);
  registerStrategy("Sort + Two Pointer", solution2);
}

vector<ResultRow> CombineTwoTablesSolution::combineTwoTables(vector<Person>& person, vector<Address>& address) {
  return getSolution()(person, address);
}

}  // namespace problem_175
}  // namespace leetcode
