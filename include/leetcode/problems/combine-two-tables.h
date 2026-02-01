#include "leetcode/core.h"

namespace leetcode {
namespace problem_175 {

// 定义表结构
struct Person {
  int personId;
  string lastName;
  string firstName;
};

struct Address {
  int addressId;
  int personId;
  string city;
  string state;
};

// 结果行: firstName, lastName, city, state
using ResultRow = tuple<string, string, optional<string>, optional<string>>;

using Func = std::function<vector<ResultRow>(vector<Person>&, vector<Address>&)>;

class CombineTwoTablesSolution : public SolutionBase<Func> {
 public:
  //! 175. Combine Two Tables
  //! https://leetcode.com/problems/combine-two-tables/
  vector<ResultRow> combineTwoTables(vector<Person>& person, vector<Address>& address);

  CombineTwoTablesSolution();
};

}  // namespace problem_175
}  // namespace leetcode
