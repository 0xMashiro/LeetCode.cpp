#include "leetcode/core.h"

namespace leetcode {
namespace problem_1689 {

using Func = std::function<int(string)>;

class PartitioningIntoMinimumNumberOfDeciBinaryNumbersSolution : public SolutionBase<Func> {
 public:
  //! 1689. Partitioning Into Minimum Number Of Deci-Binary Numbers
  //! https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/
  int minPartitions(string n);

  PartitioningIntoMinimumNumberOfDeciBinaryNumbersSolution();
};

}  // namespace problem_1689
}  // namespace leetcode
