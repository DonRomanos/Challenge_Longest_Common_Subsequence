#include "gtest/gtest.h"

#include "src/reference/implementation.hpp"
#include "src/implementation.hpp"

class LongestCommonSequenceTestHelper : public ::testing::TestWithParam<int (*)(std::string_view, std::string_view)>
{
};

TEST_P(LongestCommonSequenceTestHelper, Should_return_0_for_empty_strings)
{
    auto to_test = GetParam();
    EXPECT_EQ(to_test("", ""), 0);
}

TEST_P(LongestCommonSequenceTestHelper, Should_return_correct_result_for_simple_case)
{
    auto to_test = GetParam();
    EXPECT_EQ(to_test("AXYUIZ", "CXYO"), 2);
}

TEST_P(LongestCommonSequenceTestHelper, Should_return_length_of_strings_for_equal_strings)
{
    auto to_test = GetParam();
    auto expected = std::string(80, 'A');
    EXPECT_EQ(to_test(expected, expected), expected.size());
}

TEST_P(LongestCommonSequenceTestHelper, Should_be_case_sensitive)
{
    auto to_test = GetParam();
    EXPECT_EQ(to_test("AxyUIZ", "CXYO"), 0);
}

INSTANTIATE_TEST_CASE_P(
    LongestCommonSequenceTests,
    LongestCommonSequenceTestHelper,
    ::testing::Values(
        reference::get_length_of_longest_common_sequence, challenge::get_length_of_longest_common_sequence));

TEST(GtestDependency, Should_Compile_if_gtest_was_found)
{
    SUCCEED();
}