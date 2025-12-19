#include "leetcode/utils/linked-list.h"

namespace leetcode {

ListNode* constructLinkedList(const std::vector<int>& nums) {
  ListNode* head = nullptr;
  ListNode* tail = nullptr;
  for (int num : nums) {
    if (!head) {
      head = new ListNode(num);
      tail = head;
    } else {
      tail->next = new ListNode(num);
      tail = tail->next;
    }
  }
  return head;
}

std::vector<int> traverse(ListNode* head) {
  std::vector<int> result;
  while (head) {
    result.push_back(head->val);
    head = head->next;
  }
  return result;
}

ListNode* removeElements(ListNode* head, int val) {
  ListNode* dummy = new ListNode(0, head);
  ListNode* cur = dummy;
  while (cur->next != nullptr) {
    if (cur->next->val == val) {
      ListNode* tmp = cur->next;
      cur->next = cur->next->next;
      delete tmp;
    } else {
      cur = cur->next;
    }
  }
  head = dummy->next;
  delete dummy;
  return head;
}

ListNode* reverseList(ListNode* head) {
  ListNode* prev = nullptr;
  ListNode* cur = head;
  ListNode* next = nullptr;
  while (cur != nullptr) {
    next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  return prev;
}

ListNode* getNode(ListNode* head, int index) {
  if (index < 0) {
    return nullptr;
  }
  ListNode dummy(0, head);
  ListNode* cur = &dummy;
  for (int i = 0; i <= index; ++i) {
    cur = cur->next;
    if (cur == nullptr) {
      return nullptr;  // index 超出范围
    }
  }
  return cur;
};

ListNode* getTail(ListNode* head) {
  if (head == nullptr) {
    return nullptr;
  }
  ListNode* cur = head;
  while (cur->next != nullptr) {
    cur = cur->next;
  }
  return cur;
}

/* MyLinkedList */

MyLinkedList::MyLinkedList(ListNode* head)
    : head(head), tail(nullptr), dummy(0), size(0) {
  ListNode* cur = head;
  while (cur) {
    ++size;
    tail = cur;
    cur = cur->next;
  }
  dummy.next = head;
}

MyLinkedList::~MyLinkedList() {
  while (head) {
    ListNode* tmp = head;
    head = head->next;
    delete tmp;
  }
}

ListNode* MyLinkedList::getNode(int index) {
  dummy.next = head;
  ListNode* cur = &dummy;
  for (int i = 0; i <= index; ++i) {
    cur = cur->next;
  }
  return cur;
};

int MyLinkedList::get(int index) {
  if (index < 0 || index >= size) {
    return -1;
  }
  return getNode(index)->val;
}

void MyLinkedList::addAtHead(int val) {
  head = new ListNode(val, head);
  if (size++ == 0) {  // empty list before adding
    tail = head;
  }
}

void MyLinkedList::addAtTail(int val) {
  if (size++ == 0) {  // empty list before adding
    head = tail = new ListNode(val);
  } else {
    tail->next = new ListNode(val);
    tail = tail->next;
  }
}

void MyLinkedList::addAtIndex(int index, int val) {
  if (index < 0 || index > size) {
    return;
  }
  if (index == 0) {
    addAtHead(val);
  } else if (index == size) {
    addAtTail(val);
  } else {
    ListNode* prev = getNode(index - 1);
    prev->next = new ListNode(val, prev->next);
    ++size;
  }
}

void MyLinkedList::deleteAtIndex(int index) {
  if (index < 0 || index >= size) {
    return;
  }
  bool is_tail = (index == size - 1);  // 在 size 减1之前检查
  ListNode* prev = getNode(index - 1);
  ListNode* del = prev->next;
  prev->next = del->next;
  delete del;
  --size;
  if (size == 0) {  // empty list after deleting
    head = tail = nullptr;
  } else if (index == 0) {  // head node deleted
    head = prev->next;
  } else if (is_tail) {  // tail node deleted
    tail = prev;
  }
}

};  // namespace leetcode