#include "leetcode/solution.hpp"

#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace {

using Func = std::function<int(int)>;

int plus_one(int x) { return x + 1; }

int times_two(int x) { return x * 2; }

TEST(SolutionBaseTest, StoresStructuredStrategyMetadataInRegistrationOrder) {
  SolutionBase<Func> solution;
  solution.setMetaInfo({.id = 0, .title = "Framework Test", .url = ""});

  solution.registerStrategy({.name = "Brute Force",
                             .expected = "Time Limit Exceeded",
                             .time_complexity = "O(n^2)",
                             .space_complexity = "O(1)",
                             .tags = {"brute-force", "oracle"},
                             .notes = "Small input oracle"},
                            plus_one);
  solution.registerStrategy({.name = "Optimal",
                             .expected = "Accepted",
                             .time_complexity = "O(n)",
                             .space_complexity = "O(n)",
                             .tags = {"hash-table"}},
                            times_two);

  EXPECT_EQ((std::vector<std::string>{"Brute Force", "Optimal"}),
            solution.getStrategyNames());

  const auto metadata = solution.getStrategyMetadata();
  ASSERT_EQ(2, metadata.size());
  EXPECT_EQ("Brute Force", metadata[0].name);
  EXPECT_EQ("Time Limit Exceeded", metadata[0].expected);
  EXPECT_EQ("O(n^2)", metadata[0].time_complexity);
  EXPECT_EQ((std::vector<std::string>{"brute-force", "oracle"}),
            metadata[0].tags);
  EXPECT_EQ("Optimal", metadata[1].name);
  EXPECT_EQ("Accepted", metadata[1].expected);
}

TEST(SolutionBaseTest, MinimalRegistrationGetsAcceptedMetadata) {
  SolutionBase<Func> solution;
  solution.setMetaInfo({.id = 0, .title = "Framework Test", .url = ""});

  solution.registerStrategy({.name = "Minimal"}, plus_one);

  const auto metadata = solution.getStrategyMetadata();
  ASSERT_EQ(1, metadata.size());
  EXPECT_EQ("Minimal", metadata[0].name);
  EXPECT_EQ("Accepted", metadata[0].expected);
}

TEST(SolutionBaseTest, DefaultStrategyUsesLastRegisteredStrategy) {
  SolutionBase<Func> solution;
  solution.setMetaInfo({.id = 0, .title = "Framework Test", .url = ""});
  solution.registerStrategy({.name = "First"}, plus_one);
  solution.registerStrategy({.name = "Last"}, times_two);

  solution.setDefaultStrategy();

  EXPECT_EQ(10, solution.getSolution()(5));
}

TEST(SolutionBaseTest, DuplicateStructuredStrategyNameThrows) {
  SolutionBase<Func> solution;
  solution.setMetaInfo({.id = 0, .title = "Framework Test", .url = ""});
  solution.registerStrategy({.name = "Duplicate"}, plus_one);

  EXPECT_THROW(solution.registerStrategy({.name = "Duplicate"}, times_two),
               std::invalid_argument);
}

}  // namespace
