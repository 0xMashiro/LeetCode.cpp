#include "leetcode/problems/display-the-first-three-rows.h"

namespace leetcode {
namespace problem_2879 {

// 直接返回前3行
// 时间复杂度: O(1), 空间复杂度: O(1)
static vector<Employee> solution1(const vector<Employee>& employees) {
    vector<Employee> result;
    int n = min(3, static_cast<int>(employees.size()));
    for (int i = 0; i < n; ++i) {
        result.push_back(employees[i]);
    }
    return result;
}

DisplayTheFirstThreeRowsSolution::DisplayTheFirstThreeRowsSolution() {
    setMetaInfo({.id = 2879,
                 .title = "Display the First Three Rows",
                 .url = "https://leetcode.com/problems/display-the-first-three-rows/"});
    registerStrategy("Direct Slice", solution1);
}

vector<Employee> DisplayTheFirstThreeRowsSolution::selectFirstThreeRows(const vector<Employee>& employees) {
    return getSolution()(employees);
}

}  // namespace problem_2879
}  // namespace leetcode