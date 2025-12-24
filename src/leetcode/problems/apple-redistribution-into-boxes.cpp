
#include "leetcode/problems/apple-redistribution-into-boxes.h"

namespace leetcode {
namespace problem_3074 {

// Strategy 1: Sorting Greedy
// Sort capacities in descending order, then pick the largest capacities until
// total capacity >= total apples.
// Time complexity: O(m log m), Space complexity: O(1) (excluding sort)
static int solution1(vector<int>& apple, vector<int>& capacity) {
  int total_apples = 0;
  for (int a : apple) {
    total_apples += a;
  }

  // Sort in descending order
  sort(capacity.rbegin(), capacity.rend());

  int used_boxes = 0;
  int accumulated_capacity = 0;
  for (int c : capacity) {
    accumulated_capacity += c;
    used_boxes++;
    if (accumulated_capacity >= total_apples) {
      return used_boxes;
    }
  }
  // According to the problem, it's always possible to redistribute
  return used_boxes;
}

// Strategy 2: Counting Sort Greedy
// Since capacity[i] <= 50, we can use counting sort for better theoretical
// complexity when m is large relative to max capacity.
// Time complexity: O(m + max_capacity) = O(m + 50), Space complexity: O(max_capacity)
static int solution2(vector<int>& apple, vector<int>& capacity) {
  int total_apples = 0;
  for (int a : apple) {
    total_apples += a;
  }

  // Count frequencies of each capacity value (1 to 50)
  const int MAX_CAPACITY = 50;
  vector<int> count(MAX_CAPACITY + 1, 0);  // index 0 unused
  for (int c : capacity) {
    count[c]++;
  }

  int used_boxes = 0;
  int accumulated_capacity = 0;
  // Pick from largest capacity to smallest
  for (int cap = MAX_CAPACITY; cap >= 1; --cap) {
    while (count[cap] > 0 && accumulated_capacity < total_apples) {
      accumulated_capacity += cap;
      used_boxes++;
      count[cap]--;
    }
    if (accumulated_capacity >= total_apples) {
      return used_boxes;
    }
  }
  // According to the problem, it's always possible to redistribute
  return used_boxes;
}

AppleRedistributionIntoBoxesSolution::AppleRedistributionIntoBoxesSolution() {
  setMetaInfo({.id = 3074,
               .title = "Apple Redistribution into Boxes",
               .url = "https://leetcode.com/problems/apple-redistribution-into-boxes/"});
  registerStrategy("Sorting Greedy", solution1);
  registerStrategy("Counting Sort Greedy", solution2);
}

int AppleRedistributionIntoBoxesSolution::minimumBoxes(vector<int>& apple, vector<int>& capacity) {
  return getSolution()(apple, capacity);
}

}  // namespace problem_3074
}  // namespace leetcode