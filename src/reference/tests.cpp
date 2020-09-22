#include "gtest/gtest.h"

template <typename T>
class Some_typed_Test : public ::testing::Test
{

};
TYPED_TEST_CASE_P(Some_typed_Test);

/***************************************************************/
TYPED_TEST_P(Some_typed_Test, Should_Succeed) {
  // Inside a test, refer to TypeParam to get the type parameter.
  // TypeParam n = 0;
  SUCCEED();
}

// Register all test names, e.g. Should_Succeed
REGISTER_TYPED_TEST_CASE_P(Some_typed_Test,
                            Should_Succeed);

// Now we can instantiate it with our types.
#ifdef BUILD_REFERENCE
    using TypesToTest = ::testing::Types<challenge::SomeClass, reference::SomeClass>;
#else
    using TypesToTest = ::testing::Types<reference::SomeClass>;
#endif

INSTANTIATE_TYPED_TEST_CASE_P(WhateverNameYouWant, Some_typed_Test, TypesToTest);

TEST(GtestDependency, Should_Compile_if_gtest_was_found)
{
    SUCCEED();
}