#include "leetcode/core.h"

namespace leetcode {
namespace problem_3782 {

using Func = std::function<long long(long long)>;

class LastRemainingIntegerAfterAlternatingDeletionOperationsSolution : public SolutionBase<Func> {
 public:
  long long lastInteger(long long n);

  LastRemainingIntegerAfterAlternatingDeletionOperationsSolution();
};

}  // namespace problem_3782
}  // namespace leetcode
