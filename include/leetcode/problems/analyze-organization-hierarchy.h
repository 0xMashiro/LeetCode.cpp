#include "leetcode/core.h"

namespace leetcode {
namespace problem_3482 {

/**
 * 员工结构体
 */
struct Employee {
  int employee_id;
  string employee_name;
  optional<int> manager_id;  // null 表示 CEO
  int salary;
  string department;
};

/**
 * 结果结构体
 */
struct ResultRow {
  int employee_id;
  string employee_name;
  int level;
  int team_size;
  long long budget;
};

using Func = std::function<vector<ResultRow>(vector<Employee>&)>;

/**
 * 3482. Analyze Organization Hierarchy
 * https://leetcode.com/problems/analyze-organization-hierarchy/
 *
 * 分析组织层级，计算每个员工的级别、团队大小和薪资预算
 */
class AnalyzeOrganizationHierarchySolution : public SolutionBase<Func> {
 public:
  vector<ResultRow> analyzeOrganizationHierarchy(vector<Employee>& employees);
  AnalyzeOrganizationHierarchySolution();
};

}  // namespace problem_3482
}  // namespace leetcode
