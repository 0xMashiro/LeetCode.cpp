#include "leetcode/problems/separate-squares-i.h"

namespace leetcode {
namespace problem_3453 {

static double computeDifference(const vector<vector<int>>& squares, double t) {
    double diff = 0.0;
    for (const auto& sq : squares) {
        double y = sq[1];
        double l = sq[2];
        if (t <= y) {
            diff -= l * l; // 整个正方形在线上方
        } else if (t >= y + l) {
            diff += l * l; // 整个正方形在线下方
        } else {
            double h = t - y;
            diff += l * (2.0 * h - l);
        }
    }
    return diff;
}

static double solution1(vector<vector<int>>& squares) {
    double min_y = 1e18, max_y_plus_l = -1e18;
    for (const auto& sq : squares) {
        double y = sq[1];
        double l = sq[2];
        if (y < min_y) min_y = y;
        if (y + l > max_y_plus_l) max_y_plus_l = y + l;
    }
    double lo = min_y, hi = max_y_plus_l;
    // 二分搜索60次，精度足够
    for (int iter = 0; iter < 60; ++iter) {
        double mid = (lo + hi) * 0.5;
        if (computeDifference(squares, mid) >= 0.0) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return hi;
}

SeparateSquaresISolution::SeparateSquaresISolution() {
    setMetaInfo({.id = 3453,
                 .title = "Separate Squares I",
                 .url = "https://leetcode.com/problems/separate-squares-i/"});
    registerStrategy("Binary Search", solution1);
}

double SeparateSquaresISolution::separateSquares(vector<vector<int>>& squares) {
    return getSolution()(squares);
}

}  // namespace problem_3453
}  // namespace leetcode