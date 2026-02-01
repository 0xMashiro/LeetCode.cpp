
#include "leetcode/problems/get-the-size-of-a-dataframe.h"

namespace leetcode {
namespace problem_2878 {

// 直接获取 DataFrame 的行数和列数
// 时间复杂度: O(1), 空间复杂度: O(1)
static vector<int> solution1(DataFrame& players) {
  return {static_cast<int>(players.rows()), static_cast<int>(players.cols())};
}

GetTheSizeOfADataframeSolution::GetTheSizeOfADataframeSolution() {
  setMetaInfo({.id = 2878,
               .title = "Get the Size of a DataFrame",
               .url = "https://leetcode.com/problems/get-the-size-of-a-dataframe/"});
  registerStrategy("Direct Access", solution1);
}

vector<int> GetTheSizeOfADataframeSolution::getDataFrameSize(DataFrame& players) {
  return getSolution()(players);
}

}  // namespace problem_2878
}  // namespace leetcode
