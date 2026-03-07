#include <gtest/gtest.h>
#include "long_number.hpp"

using namespace rva;

class Numbers : public testing::Test{
  protected:
    void SetUp() override {
        // Можно добавить инициализацию если нужно
    }
    
    rva::LongNumber zero = rva::LongNumber("0");
    
    rva::LongNumber num1 = rva::LongNumber("1");
    rva::LongNumber num1_copy = rva::LongNumber("1");
    rva::LongNumber num1_neg = rva::LongNumber("-1");
    rva::LongNumber num1_neg_copy = rva::LongNumber("-1");
    
    rva::LongNumber num2 = rva::LongNumber("2");
    rva::LongNumber num2_neg = rva::LongNumber("-2");
    rva::LongNumber num3 = rva::LongNumber("3");
    rva::LongNumber num3_neg = rva::LongNumber("-3");
    rva::LongNumber num4 = rva::LongNumber("4");
    rva::LongNumber num4_neg = rva::LongNumber("-4");
    rva::LongNumber num5 = rva::LongNumber("7");  // Это 7, а не 5
    rva::LongNumber num5_neg = rva::LongNumber("-7");
    rva::LongNumber num6 = rva::LongNumber("10");
    rva::LongNumber num6_neg = rva::LongNumber("-10");
    rva::LongNumber num7 = rva::LongNumber("21");
    rva::LongNumber num7_neg = rva::LongNumber("-21");
    
    // Добавим недостающие числа
    rva::LongNumber num11 = rva::LongNumber("123");
    rva::LongNumber num11_neg = rva::LongNumber("-123");
    rva::LongNumber num8 = rva::LongNumber("45");  // Для 123 - 45 = 78
    rva::LongNumber big_num = rva::LongNumber("1234567");
    rva::LongNumber big_num_neg = rva::LongNumber("-1234567");
    rva::LongNumber big_num_copy = rva::LongNumber("1234567");
    
    rva::LongNumber long_num = rva::LongNumber("12345");
    rva::LongNumber long_num_neg = rva::LongNumber("-12345");
    rva::LongNumber long_num_copy = rva::LongNumber("12345");
};

TEST_F(Numbers, EQ_Test) {
    EXPECT_TRUE(num1 == num1_copy);        // 1 = 1
    EXPECT_TRUE(num1_neg == num1_neg_copy); // -1 = -1
    EXPECT_FALSE(num1 == num1_neg);        // 1 != -1
    EXPECT_FALSE(long_num == long_num_neg); // 12345 != -12345
    EXPECT_TRUE(long_num == long_num_copy); // 12345 = 12345
}

TEST_F(Numbers, NE_Test) {
    EXPECT_TRUE(num1 != num1_neg);      // 1 != -1
    EXPECT_TRUE(num2 != num3);           // 2 != 3
    EXPECT_TRUE(num1 != num2);           // 1 != 2
    EXPECT_TRUE(num1_neg != num2_neg);   // -1 != -2
    EXPECT_TRUE(big_num != big_num_neg); // 1234567 != -1234567
    EXPECT_TRUE(num1 != zero);           // 1 != 0
    EXPECT_TRUE(num1_neg != zero);       // -1 != 0
}

TEST_F(Numbers, Gt_Test) {
    // Положительные
    EXPECT_TRUE(num3 > num2);            // 3 > 2
    EXPECT_TRUE(num5 > num3);            // 7 > 3
    EXPECT_TRUE(num6 > num5);            // 10 > 7
    EXPECT_TRUE(num7 > num5);            // 21 > 7
    EXPECT_TRUE(num11 > num5);            // 123 > 7
    EXPECT_TRUE(big_num > num11);         // 1234567 > 123
    
    // Отрицательные
    EXPECT_TRUE(num2_neg > num3_neg);    // -2 > -3
    EXPECT_TRUE(num3_neg > num5_neg);    // -3 > -7
    EXPECT_TRUE(num5_neg > num6_neg);    // -7 > -10
    EXPECT_TRUE(num6_neg > num7_neg);    // -10 > -21
    EXPECT_TRUE(num11_neg > big_num_neg); // -123 > -1234567
    
    // Положительные и отрицательные
    EXPECT_TRUE(num1 > num1_neg);        // 1 > -1
    EXPECT_TRUE(num2 > num3_neg);        // 2 > -3
    EXPECT_TRUE(num5 > num6_neg);        // 7 > -10
    EXPECT_TRUE(big_num > big_num_neg);  // 1234567 > -1234567
    EXPECT_TRUE(zero > num1_neg);        // 0 > -1
    EXPECT_TRUE(num1 > zero);            // 1 > 0
}

TEST_F(Numbers, Lt_Test) {
    // Положительные
    EXPECT_TRUE(num2 < num3);            // 2 < 3
    EXPECT_TRUE(num3 < num5);            // 3 < 7
    EXPECT_TRUE(num5 < num6);            // 7 < 10
    EXPECT_TRUE(num5 < num7);            // 7 < 21
    EXPECT_TRUE(num11 < big_num);         // 123 < 1234567
    
    // Отрицательные
    EXPECT_TRUE(num3_neg < num2_neg);    // -3 < -2
    EXPECT_TRUE(num5_neg < num3_neg);    // -7 < -3
    EXPECT_TRUE(num6_neg < num5_neg);    // -10 < -7
    EXPECT_TRUE(num7_neg < num6_neg);    // -21 < -10
    EXPECT_TRUE(big_num_neg < num11_neg); // -1234567 < -123
    
    // Положительные и отрицательные
    EXPECT_TRUE(num1_neg < num1);        // -1 < 1
    EXPECT_TRUE(num3_neg < num2);        // -3 < 2
    EXPECT_TRUE(num6_neg < num5);        // -10 < 7
    EXPECT_TRUE(big_num_neg < big_num);  // -1234567 < 1234567
    EXPECT_TRUE(num1_neg < zero);        // -1 < 0
    EXPECT_TRUE(zero < num1);            // 0 < 1
}

TEST_F(Numbers, Add_Test) {
    EXPECT_TRUE(num6 == num5 + num3);    // 7 + 3 = 10
    EXPECT_TRUE(num5_neg == num3_neg + num4_neg); // -3 + -4 = -7
    EXPECT_TRUE(num5 == num6 + num3_neg); // 10 + -3 = 7
	EXPECT_TRUE(zero == zero + zero);     // 0 + 0 = 0
    
    rva::LongNumber sum = rva::LongNumber("1234569");
    EXPECT_TRUE(sum == big_num + num2);   // 1234567 + 2 = 1234569
    
    rva::LongNumber sum2 = rva::LongNumber("1234564");
    EXPECT_TRUE(sum2 == big_num + num3_neg); // 1234567 + -3 = 1234564
}

TEST_F(Numbers, Sub_Test) {
    EXPECT_TRUE(num1_neg == num3 - num4); // 3 - 4 = -1
    EXPECT_TRUE(num3 == num5_neg - num6_neg); // -7 - -10 = 3
        
    EXPECT_TRUE(num1_neg == num1_neg - zero); // -1 - 0 = -1
    EXPECT_TRUE(zero == zero - zero);     // 0 - 0 = 0
    
    rva::LongNumber sub = rva::LongNumber("1234565");    
    rva::LongNumber sub2 = rva::LongNumber("1234570");
    EXPECT_TRUE(sub2 == big_num - num3_neg); // 1234567 - -3 = 1234570
}

TEST_F(Numbers, Mul_Test) {
    EXPECT_TRUE(num2 == num2 * num1);     // 2 * 1 = 2
    EXPECT_TRUE(num2 == num1_neg * num2_neg); // -1 * -2 = 2
    EXPECT_TRUE(num2_neg == num2 * num1_neg); // 2 * -1 = -2
    EXPECT_TRUE(rva::LongNumber("-6") == num2_neg * num3); // -2 * 3 = -6
    
    EXPECT_TRUE(zero == num1 * zero);      // 1 * 0 = 0
    EXPECT_TRUE(zero == zero * num5);      // 0 * 7 = 0
    EXPECT_TRUE(zero == zero * zero);      // 0 * 0 = 0
    
    EXPECT_TRUE(num5 == num5 * num1);      // 7 * 1 = 7
    EXPECT_TRUE(num5_neg == num5_neg * num1); // -7 * 1 = -7
    
    rva::LongNumber mul = rva::LongNumber("2469134");
    EXPECT_TRUE(mul == num2 * big_num);    // 2 * 1234567 = 2469134
    
    rva::LongNumber mul2 = rva::LongNumber("3703701");
    EXPECT_TRUE(mul2 == num3 * big_num);   // 3 * 1234567 = 3703701
}

TEST_F(Numbers, Div_Test) {
    EXPECT_TRUE(num5 == num7 / num3);      // 21 / 3 = 7
    EXPECT_TRUE(num2 == num5 / num3);      // 7 / 3 = 2 (целочисленное)    
    
    EXPECT_TRUE(num2 == num5_neg / num3_neg); // -7 / -3 = 2
    EXPECT_TRUE(zero == num3_neg / num4_neg); // -3 / -4 = 0
    
    EXPECT_TRUE(num5_neg == num7_neg / num3); // -21 / 3 = -7
    EXPECT_TRUE(rva::LongNumber("-3") == num5 / num2_neg); // 7 / -2 = -3
    EXPECT_TRUE(zero == num4_neg / num5); // -4 / 7 = 0
    EXPECT_TRUE(zero == num4 / num5_neg); // 4 / -7 = 0
    
    EXPECT_TRUE(num5 == num5 / num1);      // 7 / 1 = 7
    EXPECT_TRUE(num5_neg == num5_neg / num1); // -7 / 1 = -7
    
    rva::LongNumber div = rva::LongNumber("617283");
    EXPECT_TRUE(div == big_num / num2);    // 1234567 / 2 = 617283
    
    rva::LongNumber div2 = rva::LongNumber("411522");
    EXPECT_TRUE(div2 == big_num / num3);   // 1234567 / 3 = 411522
}

TEST_F(Numbers, Rem_Test) {
    EXPECT_TRUE(num3 == num5 % num4);      // 7 % 4 = 3
    EXPECT_TRUE(zero == num7 % num3);      // 21 % 3 = 0
    EXPECT_TRUE(num3 == num3 % num4);      // 3 % 4 = 3
    
    EXPECT_TRUE(num1_neg == num5_neg % num3_neg); // -7 % -3 = -1
    EXPECT_TRUE(num3_neg == num3_neg % num4_neg); // -3 % -4 = -3
    EXPECT_TRUE(zero == num4_neg % num2_neg);     // -4 % -2 = 0
    EXPECT_TRUE(num6 == num6 % num7_neg);         // 10 % -21 = 10
        
    EXPECT_TRUE(rva::LongNumber("1") == big_num % num2); // 1234567 % 2 = 1
    EXPECT_TRUE(rva::LongNumber("0") == big_num % num1); // 1234567 % 1 = 0
}