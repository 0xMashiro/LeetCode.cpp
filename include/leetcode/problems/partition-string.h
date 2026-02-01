#include "leetcode/core.h"

namespace leetcode {
namespace problem_3597 {

using Func = std::function<vector<string>(string)>;

class PartitionStringSolution : public SolutionBase<Func> {
 public:
  vector<string> partitionString(string s);

  PartitionStringSolution();
};

}  // namespace problem_3597
}  // namespace leetcode
