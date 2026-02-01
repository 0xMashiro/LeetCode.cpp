#include "leetcode/problems/debounce.h"

namespace leetcode {
namespace problem_2627 {

Debounce::Debounce(std::function<void(vector<int>)> fn, int t)
    : fn_(fn), t_(t), cancelled_(false), has_pending_(false) {}

Debounce::~Debounce() {
  {
    std::lock_guard<std::mutex> lock(mutex_);
    cancelled_ = true;
  }
  cv_.notify_all();
  if (timer_thread_.joinable()) {
    timer_thread_.join();
  }
}

void Debounce::operator()(vector<int> args) {
  std::lock_guard<std::mutex> lock(mutex_);

  // 取消之前的定时任务
  cancelled_ = true;

  // 如果有正在运行的线程，先等待它结束
  if (timer_thread_.joinable()) {
    // 通知线程退出
    cv_.notify_all();
    mutex_.unlock();
    timer_thread_.join();
    mutex_.lock();
  }

  // 重置状态并保存新参数
  cancelled_ = false;
  has_pending_ = true;
  pending_args_ = args;

  // 启动新的定时线程
  timer_thread_ = std::thread([this]() {
    std::unique_lock<std::mutex> lock(mutex_);
    // 等待指定时间，或直到被取消
    cv_.wait_for(lock, std::chrono::milliseconds(t_),
                 [this]() { return cancelled_.load(); });

    // 如果没有被取消，则执行函数
    if (!cancelled_ && has_pending_) {
      vector<int> args_copy = pending_args_;
      has_pending_ = false;
      lock.unlock();
      fn_(args_copy);
    }
  });
}

}  // namespace problem_2627
}  // namespace leetcode
