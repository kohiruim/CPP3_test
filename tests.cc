#include "calcView/calcController.h"
#include <gtest/gtest.h>
#include <iostream>

class CalcTest : public ::testing::Test {
 protected:
  s21::CalcController test;
};

TEST_F(CalcTest, test1) {
    QString result = test.calc("546.021598745+78.2356487", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 624.257247445);
}

TEST_F(CalcTest, test2) {
    QString result = test.calc("546.021598745-78.2356487", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 67.785950045);
}

TEST_F(CalcTest, test3) {
    QString result1 = test.calc("45^5", "");
    QString result2 = test.calc("-7^5", "");
    QString result3 = test.calc("45^(-3)", "");
    QString result4 = test.calc("0.123^0.456", "");
    QString result5 = test.calc("2^3^3", "");
    QString result6 = test.calc("2^(2*3)", "");
    EXPECT_DOUBLE_EQ(result1.toDouble(), 184528125);
    EXPECT_DOUBLE_EQ(result2.toDouble(), -16807);
    EXPECT_DOUBLE_EQ(result3.toDouble(), 0.00001097393);
    EXPECT_DOUBLE_EQ(result4.toDouble(), 0.38458888701);
    EXPECT_DOUBLE_EQ(result5.toDouble(), 134217728);
    EXPECT_DOUBLE_EQ(result6.toDouble(), 64);
}

TEST_F(CalcTest, test4) {
    QString result1 = test.calc("(75.02456-0.456)*0.45", "");
    QString result2 = test.calc("(75.02456-0.456)*(123+456)", "");
    EXPECT_DOUBLE_EQ(result1.toDouble(), 33.555852);
    EXPECT_DOUBLE_EQ(result2.toDouble(), 43175.19624);
}

TEST_F(CalcTest, test5) {
    QString result1 = test.calc("(X-0.456)*0.45", "0.98");
    QString result2 = test.calc("(75.02456-0.456)*X^X", "0.5");
    EXPECT_DOUBLE_EQ(result1.toDouble(), 0.2358);
    EXPECT_DOUBLE_EQ(result2.toDouble(), 52.7279344393);
}

TEST_F(CalcTest, test6) {
    QString result = test.calc("", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), );
}

TEST_F(CalcTest, test7) {
    QString result = test.calc("15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), -30.0721649485);
}

TEST_F(CalcTest, test8) {
    QString result = test.calc("0.25/(0.02*45)", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.27777778);
}

TEST_F(CalcTest, test9) {
    QString result = test.calc("90mod(45+7)", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 38);
}

TEST_F(CalcTest, test10) {
    QString result = test.calc("90mod45+7", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 9);
}

TEST_F(CalcTest, test11) {
    QString result = test.calc("90mod80mod7", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 3);
}

TEST_F(CalcTest, test12) {
    QString result = test.calc("111.23mod78+0.5", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 33.73);
}

TEST_F(CalcTest, test13) {
    QString result = test.calc("111.23modX+0.5", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 6.73);
}

TEST_F(CalcTest, test14) {
    QString result = test.calc("sin(X)*0.789", "0.78");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.55488746174);
}

TEST_F(CalcTest, test15) {
    QString result = test.calc("sin(sin(X^0.7))", "4.02");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.45607214834);
}

TEST_F(CalcTest, test16) {
    QString result = test.calc("sin(78mod(10+0.45))", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), -0.99054653596);
}

TEST_F(CalcTest, test17) {
    QString result = test.calc("cos(X)*0.789", "0.78");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.56091078149);
}

TEST_F(CalcTest, test18) {
    QString result = test.calc("cos(sin(X^0.7))", "4.02");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.88994280462);
}

TEST_F(CalcTest, test19) {
    QString result = test.calc("cos(78mod(10+0.45))", "0");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.1371771121);
}

TEST_F(CalcTest, test20) {
    QString result = test.calc("tan(-X)*sin(X)*cos(-X)*atan(X)*asin(-X)*acos(X)", "0.56");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.08359499073);
}

TEST_F(CalcTest, test21) {
    QString result = test.calc("asin(-X)", "-0.78923");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.9095541131);
}

TEST_F(CalcTest, test22) {
    QString result = test.calc("acos(-X)", "-0.78923");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.661242214);
}

TEST_F(CalcTest, test23) {
    QString result = test.calc("asin(0.236)^acos(-1)", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.01103765695);
}

TEST_F(CalcTest, test24) {
    QString result = test.calc("asin(0.236)/acos(-1)*sin(-85.65)", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.0558082829);
}

TEST_F(CalcTest, test25) {
    QString result = test.calc("sqrt(asin(0.5)/acos(-0.002))", "-789.23");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.57698306696);
}

TEST_F(CalcTest, test26) {
    QString result = test.calc("tan(-X)", "-789.23");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.8257463099);
}

TEST_F(CalcTest, test27) {
    QString result = test.calc("tan(65)^(-2)/9.01", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.05135916262);
}

TEST_F(CalcTest, test28) {
    QString result = test.calc("tan(tan(-X))", "100.023");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.62234791294);
}

TEST_F(CalcTest, test29) {
    QString result = test.calc("atan(X)", "-789.23");
    EXPECT_DOUBLE_EQ(result.toDouble(), -1.56952927);
}

TEST_F(CalcTest, test30) {
    QString result = test.calc("atan(65)^2/9.01", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.26851380325);
}

TEST_F(CalcTest, test31) {
    QString result = test.calc("atan(atan(X))", "100.023");
    EXPECT_DOUBLE_EQ(result.toDouble(), 1.00098847);
}

TEST_F(CalcTest, test32) {
    QString result = test.calc("sqrt(X)", "0.001");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.0316227766);
}

TEST_F(CalcTest, test33) {
    QString result = test.calc("sqrt(-1*(cos(89)*sin(67)*sqrt(97)+0.235))", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 2.015861606);
}

TEST_F(CalcTest, test34) {
    QString result = test.calc("sqrt(sqrt(sqrt(56.555)))", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 1.65599444584);
}

TEST_F(CalcTest, test35) {
    QString result1 = test.calc("ln(58.456)", "");
    QString result2 = test.calc("log(0.000007)", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 4.06827433449);
    EXPECT_DOUBLE_EQ(result.toDouble(), -5.15490195999);
}

TEST_F(CalcTest, test36) {
    QString result = test.calc("sin(X)*cos(X)*ln(X)^3", "45");
    EXPECT_DOUBLE_EQ(result.toDouble(), 24.6569310271);
}

TEST_F(CalcTest, test37) {
    QString result = test.calc("log(32.02)^ln(10)", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 2.56491401678);
}

TEST_F(CalcTest, test38) {
    QString result = test.calc("log(1)", "");
    QString result = test.calc("log(0.0001)", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 0);
    EXPECT_DOUBLE_EQ(result.toDouble(), -4);
}

TEST_F(CalcTest, test39) {
    QString result = test.calc("log(X)^3", "45");
    EXPECT_DOUBLE_EQ(result.toDouble(), 4.51841432466);
}

TEST_F(CalcTest, test40) {
    QString result = test.calc("log(32.02)^log(4)", "");
    EXPECT_DOUBLE_EQ(result.toDouble(), 1.27926586827);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
