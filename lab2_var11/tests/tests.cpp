#include <gtest/gtest.h>
#include "thirteen_num_syst.h"
#include "exceptions.h"

using namespace thirteen;

class ToThirteenTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ToThirteenTest, DefaultConstructor) {
    Thirteen d;
    EXPECT_EQ(d.Show(), "0");
}

TEST_F(ToThirteenTest, SizeValueConstructor) {
    Thirteen d(3, 5);
    EXPECT_EQ(d.Show(), "555");
}

TEST_F(ToThirteenTest, InitializerListConstructor) {
    Thirteen d{1, 2, 10};
    EXPECT_EQ(d.Show(), "12A");
    
    Thirteen d2{0, 0, 1, 2, 10};
    EXPECT_EQ(d2.Show(), "12A");
}

TEST_F(ToThirteenTest, StringConstructor) {
    Thirteen d("12C45");
    EXPECT_EQ(d.Show(), "12C45");
    
    Thirteen d2("0001B3");
    EXPECT_EQ(d2.Show(), "1B3");
}

TEST_F(ToThirteenTest, StringConstructorInvalidInput) {
    EXPECT_THROW(Thirteen d("12D45"), exception::ExceptionNull);
    EXPECT_THROW(Thirteen d("12.45"), exception::ExceptionNull);
    EXPECT_THROW(Thirteen d("xx"), exception::ExceptionNull);
}

TEST_F(ToThirteenTest, CopyConstructor) {
    Thirteen d1("12345AA");
    Thirteen d2(d1);
    EXPECT_EQ(d2.Show(), "12345AA");
}

TEST_F(ToThirteenTest, MoveConstructor) {
    Thirteen d1("1234BCA5");
    Thirteen d2(std::move(d1));
    EXPECT_EQ(d2.Show(), "1234BCA5");
}

TEST_F(ToThirteenTest, ComparisonOperators) {
    Thirteen d1("123A");
    Thirteen d2("4563");
    Thirteen d3("123A");
    Thirteen d4("1234B");
    Thirteen d5("12C");
    
    EXPECT_TRUE(d1.LessThen(d2));
    EXPECT_FALSE(d2.LessThen(d1));
    EXPECT_TRUE(d1.Equal(d3));
    EXPECT_FALSE(d1.Equal(d2));
    EXPECT_TRUE(d1.GreaterThen(d5));
    EXPECT_FALSE(d5.GreaterThen(d1));

    EXPECT_TRUE(d1.LessThen(d4));
    EXPECT_TRUE(d4.GreaterThen(d1));
}

TEST_F(ToThirteenTest, Addition) {
    Thirteen d1("123");
    Thirteen d2("456");
    Thirteen result1 = Thirteen::Add(d1, d2);
    EXPECT_EQ(result1.Show(), "579");

    Thirteen d3("999");
    Thirteen d4("1");
    Thirteen result2 = Thirteen::Add(d3, d4);
    EXPECT_EQ(result2.Show(), "99A");

    Thirteen d5("0");
    Thirteen result3 = Thirteen::Add(d1, d5);
    EXPECT_EQ(result3.Show(), "123");

    Thirteen d6("123456789");
    Thirteen d7("987654321");
    Thirteen result4 = Thirteen::Add(d6, d7);
    EXPECT_EQ(result4.Show(), "AAAAAAAAA");
}

TEST_F(ToThirteenTest, Subtraction) {
    Thirteen d1("456");
    Thirteen d2("123");
    Thirteen result1 = Thirteen::Sub(d1, d2);
    EXPECT_EQ(result1.Show(), "333");

    Thirteen d3("1000");
    Thirteen d4("1");
    Thirteen result2 = Thirteen::Sub(d3, d4);
    EXPECT_EQ(result2.Show(), "CCC");

    Thirteen d5("123");
    Thirteen result3 = Thirteen::Sub(d5, d5);
    EXPECT_EQ(result3.Show(), "0");
        
}

TEST_F(ToThirteenTest, SubtractionNegativeResult) {
    Thirteen d1("123");
    Thirteen d2("456");
    
    EXPECT_THROW(Thirteen::Sub(d1, d2), exception::NegativeException);
}

TEST_F(ToThirteenTest, EdgeCases) {
    Thirteen zero1("0");
    Thirteen zero2("0000");
    EXPECT_EQ(zero1.Show(), "0");
    EXPECT_EQ(zero2.Show(), "0");
    EXPECT_TRUE(zero1.Equal(zero2));

    Thirteen large("123456789012345678901234567890");
    EXPECT_EQ(large.Show(), "123456789012345678901234567890");

    Thirteen withLeadingZeros("0000000123");
    EXPECT_EQ(withLeadingZeros.Show(), "123");
}

TEST_F(ToThirteenTest, CopyMethod) {
    Thirteen d1("12345");
    Thirteen d2("67890");
    
    d1.Copy(d2);
    EXPECT_EQ(d1.Show(), "67890");
    EXPECT_TRUE(d1.Equal(d2));
}

TEST_F(ToThirteenTest, ShowMethod) {
    Thirteen d1("12345");
    Thirteen d2(0, 0);
    Thirteen d3{1, 2, 3};
    
    EXPECT_EQ(d1.Show(), "12345");
    EXPECT_EQ(d2.Show(), "0");
    EXPECT_EQ(d3.Show(), "123");
}

TEST_F(ToThirteenTest, ComplexOperations) {
    Thirteen a("A000");
    Thirteen b("5B0");
    Thirteen c("30C");
    
    Thirteen sum = Thirteen::Add(a, b);
    Thirteen result = Thirteen::Sub(sum, c);
    EXPECT_EQ(result.Show(), "A2A1");

    Thirteen x("AAABB10");
    Thirteen y("CB20");
    Thirteen z("5CB0");
    
    Thirteen res1 = Thirteen::Add(x, y);
    Thirteen final_result = Thirteen::Add(res1, z);
    EXPECT_EQ(final_result.Show(), "AAC4910");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}