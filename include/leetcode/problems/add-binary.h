#include "leetcode/core.h"

namespace leetcode {
namespace problem_67 {

using Func = std::function<string(string, string)>;

class AddBinarySolution : public SolutionBase<Func> {
 public:
  //! 67. Add Binary
  //! https://leetcode.com/problems/add-binary/
  string addBinary(string a, string b);

  AddBinarySolution();
};

}  // namespace problem_67
}  // namespace leetcode
