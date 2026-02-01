
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2878 {

/**
 * DataFrame 结构体，模拟 Pandas DataFrame
 * 使用二维 vector 存储表格数据
 */
struct DataFrame {
  vector<vector<string>> data;  // 表格数据
  vector<string> columns;       // 列名
  
  DataFrame() = default;
  DataFrame(const vector<vector<string>>& d, const vector<string>& c) 
      : data(d), columns(c) {}
  
  // 获取行数
  size_t rows() const { return data.size(); }
  
  // 获取列数
  size_t cols() const { return columns.size(); }
};

using Func = std::function<vector<int>(DataFrame&)>;

/**
 * 2878. Get the Size of a DataFrame
 * https://leetcode.com/problems/get-the-size-of-a-dataframe/
 */
class GetTheSizeOfADataframeSolution : public SolutionBase<Func> {
 public:
  //! 计算 DataFrame 的行数和列数
  //! @param players DataFrame 对象
  //! @return [number of rows, number of columns]
  vector<int> getDataFrameSize(DataFrame& players);

  GetTheSizeOfADataframeSolution();
};

}  // namespace problem_2878
}  // namespace leetcode
