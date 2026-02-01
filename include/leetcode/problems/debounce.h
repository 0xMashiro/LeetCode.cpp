#ifndef LEETCODE_PROBLEMS_DEBOUNCE_H__
#define LEETCODE_PROBLEMS_DEBOUNCE_H__

#include "leetcode/core.h"

namespace leetcode {
namespace problem_2627 {

/**
 * Debounce（防抖）实现
 * 思路：使用线程和条件变量实现延迟执行
 * - 每次调用时取消之前的定时任务（如果存在）
 * - 启动新的定时任务，延迟 t 毫秒后执行
 * - 使用互斥锁保证线程安全
 */
class Debounce {
 public:
  /**
   * 构造函数
   * @param fn 要执行的函数
   * @param t 延迟时间（毫秒）
   */
  Debounce(std::function<void(vector<int>)> fn, int t);

  /**
   * 析构函数：确保线程正确结束
   */
  ~Debounce();

  /**
   * 调用防抖函数
   * @param args 函数参数
   */
  void operator()(vector<int> args);

 private:
  std::function<void(vector<int>)> fn_;  // 目标函数
  int t_;                                 // 延迟时间（毫秒）
  std::mutex mutex_;                      // 互斥锁
  std::condition_variable cv_;            // 条件变量
  std::thread timer_thread_;              // 定时器线程
  std::atomic<bool> cancelled_;           // 取消标志
  std::atomic<bool> has_pending_;         // 是否有待执行任务
  vector<int> pending_args_;              // 待执行参数
};

}  // namespace problem_2627
}  // namespace leetcode

#endif  // LEETCODE_PROBLEMS_DEBOUNCE_H__
