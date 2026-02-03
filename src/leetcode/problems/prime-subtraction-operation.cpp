#include "leetcode/problems/prime-subtraction-operation.h"

namespace leetcode {
namespace problem_2601 {

// 预处理1000以内的质数
static vector<int> getPrimes() {
  const int MAX = 1000;
  vector<bool> isPrime(MAX + 1, true);
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i * i <= MAX; ++i) {
    if (isPrime[i]) {
      for (int j = i * i; j <= MAX; j += i) {
        isPrime[j] = false;
      }
    }
  }
  vector<int> primes;
  for (int i = 2; i <= MAX; ++i) {
    if (isPrime[i]) primes.push_back(i);
  }
  return primes;
}

// 二分查找：找到小于x的最大质数，使得prime > lowerBound
// 即找到一个质数p，使得 nums[i] - p > prev，即 p < nums[i] - prev
// 我们希望p尽可能大，这样nums[i] - p尽可能小
static int findBestPrime(const vector<int>& primes, int target, int prev) {
  // target是当前nums[i]，prev是处理后的nums[i-1]
  // 需要找到最大的p，使得 p < target 且 target - p > prev
  // 即 p < target - prev
  int maxP = target - prev - 1;  // p必须严格小于target - prev
  if (maxP < 2) return -1;  // 没有可用的质数
  
  // 二分查找小于等于maxP的最大质数
  int left = 0, right = primes.size() - 1;
  int result = -1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (primes[mid] <= maxP) {
      result = primes[mid];
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return result;
}

static bool solution1(vector<int>& nums) {
  static const vector<int> primes = getPrimes();
  int n = nums.size();
  
  // 处理第一个元素，prev设为0（因为要严格大于，第一个元素减完后需要>0）
  int prev = 0;
  
  for (int i = 0; i < n; ++i) {
    // 如果当前元素已经大于prev，可以尝试找更好的质数，也可以不操作
    // 但为了后面元素更容易满足条件，我们希望当前元素尽可能小
    int p = findBestPrime(primes, nums[i], prev);
    if (p != -1) {
      nums[i] -= p;
    }
    // 检查是否满足严格递增
    if (nums[i] <= prev) {
      return false;
    }
    prev = nums[i];
  }
  
  return true;
}

PrimeSubtractionOperationSolution::PrimeSubtractionOperationSolution() {
  setMetaInfo({.id = 2601,
               .title = "Prime Subtraction Operation",
               .url = "https://leetcode.com/problems/prime-subtraction-operation/"});
  registerStrategy("Greedy", solution1);
}

bool PrimeSubtractionOperationSolution::primeSubOperation(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2601
}  // namespace leetcode
