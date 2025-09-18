#include <gtest/gtest.h>
#include "../include/is_number_clean.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(IsNumberClean("123"));
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(IsNumberClean("1"));
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(IsNumberClean("000"));
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(!IsNumberClean("321"));
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(!IsNumberClean("21"));
}

TEST(test_06, basic_test_set)
{
    ASSERT_TRUE(IsNumberClean("1234566789"));
}

TEST(test_07, basic_test_set)
{
    ASSERT_TRUE(!IsNumberClean("90"));
}

TEST(test_08, basic_test_set)
{
    ASSERT_TRUE(IsNumberClean("1111111"));
}

TEST(test_09, basic_test_set)
{
    ASSERT_TRUE(IsNumberClean("112233445566"));
}

TEST(test_10, basic_test_set)
{
    ASSERT_TRUE(!IsNumberClean("101"));
}

TEST(test_11, basic_test_set)
{
    ASSERT_TRUE(!IsNumberClean("abv"));
}

TEST(test_12, basic_test_set)
{
    ASSERT_TRUE(!IsNumberClean("1a2b3v"));
}

TEST(test_13, basic_test_set)
{
    ASSERT_TRUE(!IsNumberClean("a"));
}

TEST(test_14, basic_test_set)
{
    ASSERT_TRUE(!IsNumberClean("101/"));
}

TEST(test_15, basic_test_set)
{
    ASSERT_TRUE(!IsNumberClean("aaaaa"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}