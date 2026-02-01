#include "leetcode/core.h"

namespace leetcode {
namespace problem_816 {

using Func = std::function<vector<string>(string)>;

class AmbiguousCoordinatesSolution : public SolutionBase<Func> {
 public:
  vector<string> ambiguousCoordinates(string s);

  AmbiguousCoordinatesSolution();
};

}  // namespace problem_816
}  // namespace leetcode