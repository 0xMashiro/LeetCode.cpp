#ifndef LEETCODE_UTILS_QUEUE_H__
#define LEETCODE_UTILS_QUEUE_H__

#include <stack>

namespace leetcode {

class MyQueue {
 public:
  MyQueue();

  void push(int x);

  int pop();

  int peek();

  bool empty();

 private:
  std::stack<int> stackInput;
  std::stack<int> stackOutput;
  void move();
};

}  // namespace leetcode

#endif  // LEETCODE_UTILS_QUEUE_H__