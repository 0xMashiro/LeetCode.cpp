#include "leetcode/problems/destroying-asteroids.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2126 {

class DestroyingAsteroidsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DestroyingAsteroidsSolution solution;
};

TEST_P(DestroyingAsteroidsTest, Example1) {
  int mass = 10;
  std::vector<int> asteroids = {3, 9, 19, 5, 21};
  EXPECT_TRUE(solution.asteroidsDestroyed(mass, asteroids));
}

TEST_P(DestroyingAsteroidsTest, Example2) {
  int mass = 5;
  std::vector<int> asteroids = {4, 9, 23, 4};
  EXPECT_FALSE(solution.asteroidsDestroyed(mass, asteroids));
}

TEST_P(DestroyingAsteroidsTest, SelfAuthoredSingleAsteroidDestroyable) {
  int mass = 10;
  std::vector<int> asteroids = {5};
  EXPECT_TRUE(solution.asteroidsDestroyed(mass, asteroids));
}

TEST_P(DestroyingAsteroidsTest, SelfAuthoredSingleAsteroidNotDestroyable) {
  int mass = 3;
  std::vector<int> asteroids = {10};
  EXPECT_FALSE(solution.asteroidsDestroyed(mass, asteroids));
}

TEST_P(DestroyingAsteroidsTest, SelfAuthoredAllSmallAsteroids) {
  int mass = 1;
  std::vector<int> asteroids = {1, 1, 1, 1};
  EXPECT_TRUE(solution.asteroidsDestroyed(mass, asteroids));
}

TEST_P(DestroyingAsteroidsTest, SelfAuthoredMassiveMass) {
  int mass = 100000;
  std::vector<int> asteroids = {1, 2, 3, 4, 5};
  EXPECT_TRUE(solution.asteroidsDestroyed(mass, asteroids));
}

TEST_P(DestroyingAsteroidsTest, SelfAuthoredFirstAsteroidTooBig) {
  int mass = 1;
  std::vector<int> asteroids = {2, 2};
  EXPECT_FALSE(solution.asteroidsDestroyed(mass, asteroids));
}

TEST_P(DestroyingAsteroidsTest, SelfAuthoredSortedAscending) {
  int mass = 5;
  std::vector<int> asteroids = {1, 2, 3, 4, 5};
  EXPECT_TRUE(solution.asteroidsDestroyed(mass, asteroids));
}

TEST_P(DestroyingAsteroidsTest, SelfAuthoredCumulativeGrowth) {
  int mass = 1;
  std::vector<int> asteroids = {1, 2, 4, 8, 16};
  EXPECT_TRUE(solution.asteroidsDestroyed(mass, asteroids));
}

TEST_P(DestroyingAsteroidsTest, SelfAuthoredNearlyFails) {
  int mass = 7;
  std::vector<int> asteroids = {3, 5, 100};
  EXPECT_FALSE(solution.asteroidsDestroyed(mass, asteroids));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DestroyingAsteroidsTest,
    ::testing::ValuesIn(DestroyingAsteroidsSolution().getStrategyNames()));

}  // namespace problem_2126
}  // namespace leetcode
