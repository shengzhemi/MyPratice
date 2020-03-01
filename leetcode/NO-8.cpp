#include "gtest/gtest.h"
#include <cstring>
using namespace std;
class  MyAtoi{
public:
    int myAtoi(string str) {
        int num = 0;
        int sign = 1;
        int i = 0;
        while (str[i] == ' ') {
            i++;
        }

        if (str[i] == '+') {
            i++;
        } else if (str[i] == '-') {
            i++;
            sign = -1;
        } 

        for (; i < str.size(); i++) {
            if ((str[i] < '0') || (str[i] > '9')) {
                break;
            }

            if ((num > maxNum / 10) || 
                    ((num == maxNum / 10) && ((str[i] - '0') > maxNum % 10))) {
                return (sign == -1) ? minNum : maxNum;
            }

            int temp = str[i] - '0';
            num = num * 10 + temp;
        }
        
        return num * sign;
    }
private:
    const static int maxNum = 2147483647;
    const static int minNum = -2147483648;
};

TEST(myatoitestsuit1, empty_value) {
    MyAtoi s;
    EXPECT_EQ(0, s.myAtoi(""));
}

TEST(myatoitestsuit2, positive_value) {
    MyAtoi s;
    EXPECT_EQ(23, s.myAtoi("23abc"));
    EXPECT_EQ(23, s.myAtoi("+23abc"));
    EXPECT_EQ(23, s.myAtoi("23abc123"));
    EXPECT_EQ(23, s.myAtoi("   23abc123"));
    EXPECT_EQ(1, s.myAtoi("1"));
    EXPECT_EQ(0, s.myAtoi("0"));
    EXPECT_EQ(0, s.myAtoi(" 0"));
    EXPECT_EQ(0, s.myAtoi(" +0"));
    EXPECT_EQ(2147483647, s.myAtoi("+2147483647"));
    EXPECT_EQ(2147483647, s.myAtoi("  2147483647"));
    EXPECT_EQ(2147483647, s.myAtoi("2147483647ecvd"));
}

TEST(myatoitestsuit3, negtive_value) {
    MyAtoi s;
    EXPECT_EQ(-23, s.myAtoi("-23"));
    EXPECT_EQ(-23, s.myAtoi("-23acv"));
    EXPECT_EQ(-23, s.myAtoi("-23acv123"));
    EXPECT_EQ(-2147483648, s.myAtoi("-2147483648"));
    EXPECT_EQ(-2147483648, s.myAtoi(" -2147483648"));
    EXPECT_EQ(-2147483648, s.myAtoi("-2147483648cvf"));
}

TEST(myatoitestsuilt4, invalid_value) {
    MyAtoi s;
    EXPECT_EQ(0, s.myAtoi("+"));
    EXPECT_EQ(0, s.myAtoi("++"));
    EXPECT_EQ(0, s.myAtoi("++55"));
    EXPECT_EQ(0, s.myAtoi("+ 55"));
    EXPECT_EQ(0, s.myAtoi("abc"));
    EXPECT_EQ(0, s.myAtoi(" dc123"));
    EXPECT_EQ(0, s.myAtoi("--123"));
    EXPECT_EQ(0, s.myAtoi("- 123"));
    EXPECT_EQ(0, s.myAtoi(" _d0122d"));
}

TEST(myatoitestsuit5, beyond_up_limit_value) {
    MyAtoi s;
    EXPECT_EQ(2147483647, s.myAtoi("2147483648"));
    EXPECT_EQ(2147483647, s.myAtoi("21474836471"));
}

TEST(myatoitestsuit5, beyond_dowm_limit_value) {
    MyAtoi s;
    EXPECT_EQ(-2147483648, s.myAtoi("-2147483649"));
    EXPECT_EQ(-2147483648, s.myAtoi("-21474836481"));
}
