#include "leetcode/core.h"

namespace leetcode {
namespace problem_2879 {

// 员工数据结构
struct Employee {
    int employee_id;
    string name;
    string department;
    int salary;
};

using Func = std::function<vector<Employee>(const vector<Employee>&)>;

class DisplayTheFirstThreeRowsSolution : public SolutionBase<Func> {
 public:
  // 2879. Display the First Three Rows
  // https://leetcode.com/problems/display-the-first-three-rows/
  vector<Employee> selectFirstThreeRows(const vector<Employee>& employees);

  DisplayTheFirstThreeRowsSolution();
};

}  // namespace problem_2879
}  // namespace leetcode