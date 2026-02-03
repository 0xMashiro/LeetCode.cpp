
#include "leetcode/problems/mini-parser.h"

namespace leetcode {
namespace problem_385 {

// NestedInteger implementation
NestedInteger::NestedInteger() : is_integer_(false), value_(0) {}

NestedInteger::NestedInteger(int value) : is_integer_(true), value_(value) {}

bool NestedInteger::isInteger() const {
  return is_integer_;
}

int NestedInteger::getInteger() const {
  return value_;
}

void NestedInteger::setInteger(int value) {
  is_integer_ = true;
  value_ = value;
  list_.clear();
}

void NestedInteger::add(const NestedInteger &ni) {
  is_integer_ = false;
  list_.push_back(ni);
}

const vector<NestedInteger> &NestedInteger::getList() const {
  return list_;
}

// Solution implementation using recursive descent parsing
NestedInteger MiniParserSolution::deserialize(string s) {
  int index = 0;
  
  function<NestedInteger()> parse = [&]() -> NestedInteger {
    // Parse a single integer
    if (s[index] != '[') {
      bool negative = false;
      if (s[index] == '-') {
        negative = true;
        index++;
      }
      int num = 0;
      while (index < s.size() && isdigit(s[index])) {
        num = num * 10 + (s[index] - '0');
        index++;
      }
      return NestedInteger(negative ? -num : num);
    }
    
    // Parse a list: skip '['
    index++;
    
    // Empty list: "[]"
    if (s[index] == ']') {
      index++;
      return NestedInteger();
    }
    
    NestedInteger result;
    
    while (index < s.size()) {
      // Parse the next element (could be a number or a nested list)
      NestedInteger element = parse();
      result.add(element);
      
      // After parsing an element, we expect either ',' or ']'
      if (s[index] == ',') {
        index++;  // Skip ',' and continue to parse next element
      } else if (s[index] == ']') {
        index++;  // Skip ']' and return
        break;
      }
    }
    
    return result;
  };
  
  return parse();
}

}  // namespace problem_385
}  // namespace leetcode
