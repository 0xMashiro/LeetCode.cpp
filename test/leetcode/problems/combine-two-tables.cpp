#include "leetcode/problems/combine-two-tables.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_175 {

class CombineTwoTablesTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CombineTwoTablesSolution solution;
};

TEST_P(CombineTwoTablesTest, Example1) {
  // Person table
  vector<Person> person = {
    {1, "Wang", "Allen"},
    {2, "Alice", "Bob"}
  };
  
  // Address table
  vector<Address> address = {
    {1, 2, "New York City", "New York"},
    {2, 3, "Leetcode", "California"}
  };
  
  // Expected output
  // Allen | Wang | null | null
  // Bob | Alice | New York City | New York
  vector<ResultRow> expected = {
    {"Allen", "Wang", nullopt, nullopt},
    {"Bob", "Alice", string("New York City"), string("New York")}
  };
  
  auto result = solution.combineTwoTables(person, address);
  
  ASSERT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(get<0>(expected[i]), get<0>(result[i]));
    EXPECT_EQ(get<1>(expected[i]), get<1>(result[i]));
    EXPECT_EQ(get<2>(expected[i]), get<2>(result[i]));
    EXPECT_EQ(get<3>(expected[i]), get<3>(result[i]));
  }
}

TEST_P(CombineTwoTablesTest, EmptyAddressTable) {
  vector<Person> person = {
    {1, "Smith", "John"},
    {2, "Doe", "Jane"}
  };
  
  vector<Address> address;  // Empty
  
  vector<ResultRow> expected = {
    {"John", "Smith", nullopt, nullopt},
    {"Jane", "Doe", nullopt, nullopt}
  };
  
  auto result = solution.combineTwoTables(person, address);
  
  ASSERT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(get<0>(expected[i]), get<0>(result[i]));
    EXPECT_EQ(get<1>(expected[i]), get<1>(result[i]));
    EXPECT_EQ(get<2>(expected[i]), get<2>(result[i]));
    EXPECT_EQ(get<3>(expected[i]), get<3>(result[i]));
  }
}

TEST_P(CombineTwoTablesTest, EmptyPersonTable) {
  vector<Person> person;  // Empty
  
  vector<Address> address = {
    {1, 1, "City1", "State1"},
    {2, 2, "City2", "State2"}
  };
  
  auto result = solution.combineTwoTables(person, address);
  
  EXPECT_TRUE(result.empty());
}

TEST_P(CombineTwoTablesTest, AllPersonsHaveAddress) {
  vector<Person> person = {
    {1, "Smith", "John"},
    {2, "Doe", "Jane"}
  };
  
  vector<Address> address = {
    {1, 1, "New York", "NY"},
    {2, 2, "Los Angeles", "CA"}
  };
  
  vector<ResultRow> expected = {
    {"John", "Smith", string("New York"), string("NY")},
    {"Jane", "Doe", string("Los Angeles"), string("CA")}
  };
  
  auto result = solution.combineTwoTables(person, address);
  
  ASSERT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(get<0>(expected[i]), get<0>(result[i]));
    EXPECT_EQ(get<1>(expected[i]), get<1>(result[i]));
    EXPECT_EQ(get<2>(expected[i]), get<2>(result[i]));
    EXPECT_EQ(get<3>(expected[i]), get<3>(result[i]));
  }
}

TEST_P(CombineTwoTablesTest, MultipleAddressesSamePerson) {
  // In real scenario, this shouldn't happen due to FK constraint
  // But we test the behavior - should use one of them
  vector<Person> person = {
    {1, "Smith", "John"}
  };
  
  vector<Address> address = {
    {1, 1, "City1", "State1"},
    {2, 1, "City2", "State2"}
  };
  
  auto result = solution.combineTwoTables(person, address);
  
  ASSERT_EQ(1, result.size());
  EXPECT_EQ("John", get<0>(result[0]));
  EXPECT_EQ("Smith", get<1>(result[0]));
  // City and state should be set (either one is acceptable)
  EXPECT_TRUE(get<2>(result[0]).has_value());
  EXPECT_TRUE(get<3>(result[0]).has_value());
}

TEST_P(CombineTwoTablesTest, SinglePersonNoAddress) {
  vector<Person> person = {{1, "Only", "Person"}};
  vector<Address> address;
  
  auto result = solution.combineTwoTables(person, address);
  
  ASSERT_EQ(1, result.size());
  EXPECT_EQ("Person", get<0>(result[0]));
  EXPECT_EQ("Only", get<1>(result[0]));
  EXPECT_FALSE(get<2>(result[0]).has_value());
  EXPECT_FALSE(get<3>(result[0]).has_value());
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CombineTwoTablesTest,
    ::testing::ValuesIn(CombineTwoTablesSolution().getStrategyNames()));

}  // namespace problem_175
}  // namespace leetcode
