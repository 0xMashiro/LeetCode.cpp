#include "leetcode/utils/queue.h"

namespace leetcode {
MyQueue::MyQueue() {}

void MyQueue::move() {
  while (!stackInput.empty()) {
    stackOutput.push(stackInput.top());
    stackInput.pop();
  }
}

void MyQueue::push(int x) { stackInput.push(x); }

int MyQueue::pop() {
  if (stackOutput.empty()) {
    move();
  }
  int top = stackOutput.top();
  stackOutput.pop();
  return top;
}

int MyQueue::peek() {
  if (stackOutput.empty()) {
    move();
  }
  return stackOutput.top();
}

bool MyQueue::empty() { return stackInput.empty() && stackOutput.empty(); }
}  // namespace leetcode