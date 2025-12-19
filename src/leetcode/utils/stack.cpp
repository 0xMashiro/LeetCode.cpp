#include "leetcode/utils/stack.h"

namespace leetcode {
MyStack::MyStack() {}

void MyStack::push(int x) { queueMain.push(x); }

int MyStack::pop() {
  // Move all elements to queueAux except the last one
  while (queueMain.size() > 1) {
    queueAux.push(queueMain.front());
    queueMain.pop();
  }
  int result = queueMain.front();
  queueMain.pop();

  // Move all elements back to queueMain
  while (!queueAux.empty()) {
    queueMain.push(queueAux.front());
    queueAux.pop();
  }
  return result;
}

int MyStack::top() { return queueMain.back(); }

bool MyStack::empty() { return queueMain.empty(); };
}  // namespace leetcode