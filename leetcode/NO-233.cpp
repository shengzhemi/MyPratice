#include "gtest/gtest.h"

class CountDigitOne {
public:
    int countDigitOne(int n) {
        return countDigitOne3(n);
    }

    int countDigitOne1(int n) {
        if (n <= 0) {
            return 0;
        }

        return countDigitOne1(n - 1) + countSingleDigitOne(n);
    }

    int countDigitOne2(int n) {
        if (n <= 0) {
            return 0;
        }

        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            cnt += countSingleDigitOne(i);
        }

        return cnt;
    }

    int countDigitOne3(int n) {
        if (n <= 0) {
            return 0;
        }

        int cnt = 0;
        int high = 0;
        int low = 0;
        int multi = 1;
        while (n) {
            high = n / 10;
            cnt += countSpecifyDigitOne(high, low, multi, n % 10);
            low = (n % 10) * multi + low;
            n /= 10;
            if (n) {
                multi *= 10;
            }
        }
        return cnt;
    }

    int countSpecifyDigitOne(int high, int low, int multi, int val) {
        if (val == 0) {
            return high * multi;
        } else if (val == 1) {
            if (multi > 1) {
                return high * multi + low + 1;
            } else {
                return high + 1;
            }
        } else {
            return (high + 1) * multi;
        }
    }

    int countSingleDigitOne(int n) {
        int cnt = 0;
        while (n) {
            if (n % 10 == 1) {
                cnt++;
            }
            n /= 10;
        }
        return cnt;
    }
};

TEST(NO233_testsuite0, countOneDigit_test) {
    CountDigitOne c;
    EXPECT_EQ(0, c.countSingleDigitOne(0));
    EXPECT_EQ(1, c.countSingleDigitOne(1));
    EXPECT_EQ(0, c.countSingleDigitOne(2));
    EXPECT_EQ(0, c.countSingleDigitOne(3));
    EXPECT_EQ(1, c.countSingleDigitOne(10));
    EXPECT_EQ(2, c.countSingleDigitOne(11));
    EXPECT_EQ(3, c.countSingleDigitOne(111));
    EXPECT_EQ(2, c.countSingleDigitOne(211));
    EXPECT_EQ(1, c.countSingleDigitOne(41));
    EXPECT_EQ(2, c.countSingleDigitOne(1001));
    EXPECT_EQ(8, c.countSingleDigitOne(11111111));
}

TEST(NO233_testsuite1, zero_test) {
    CountDigitOne c;
    EXPECT_EQ(0, c.countDigitOne(-1));
    EXPECT_EQ(0, c.countDigitOne(-100));
    EXPECT_EQ(0, c.countDigitOne(-100));
    EXPECT_EQ(0, c.countDigitOne(-123456));
    EXPECT_EQ(0, c.countDigitOne(0));
}

TEST(NO233_testsuite2, normal_test) {
    CountDigitOne c;
    EXPECT_EQ(1, c.countDigitOne(1));
    EXPECT_EQ(1, c.countDigitOne(2));
    EXPECT_EQ(1, c.countDigitOne(3));
    EXPECT_EQ(1, c.countDigitOne(4));
    EXPECT_EQ(1, c.countDigitOne(5));
    EXPECT_EQ(1, c.countDigitOne(6));
    EXPECT_EQ(1, c.countDigitOne(7));
    EXPECT_EQ(1, c.countDigitOne(8));
    EXPECT_EQ(1, c.countDigitOne(9));
    EXPECT_EQ(2, c.countDigitOne(10));
    EXPECT_EQ(4, c.countDigitOne(11));
    EXPECT_EQ(5, c.countDigitOne(12));
    EXPECT_EQ(6, c.countDigitOne(13));
    EXPECT_EQ(23, c.countDigitOne(101));
    EXPECT_EQ(21, c.countDigitOne(100));
    EXPECT_EQ(33, c.countDigitOne(110));
    EXPECT_EQ(53, c.countDigitOne(120));
    EXPECT_EQ(7618, c.countDigitOne(12012));
    EXPECT_EQ(7751, c.countDigitOne(12112));
    EXPECT_EQ(7958, c.countDigitOne(12212));
    EXPECT_EQ(8078, c.countDigitOne(12312));
    EXPECT_EQ(8798, c.countDigitOne(12912));
}

TEST(NO233_testsuite3, big_num_test) {
    CountDigitOne c;
    //EXPECT_EQ(-1323939513, c.countDigitOne(2147483647));
    EXPECT_EQ(8121, c.countDigitOne(12345));
    EXPECT_EQ(93553, c.countDigitOne(123456));
    EXPECT_EQ(1058985, c.countDigitOne(1234567));
    EXPECT_EQ(11824417, c.countDigitOne3(12345678));
    //EXPECT_EQ(11824417, c.countDigitOne2(12345678));
    EXPECT_EQ(c.countDigitOne3(123), c.countDigitOne2(123));
    EXPECT_EQ(c.countDigitOne3(3333), c.countDigitOne2(3333));
    EXPECT_EQ(c.countDigitOne3(13579), c.countDigitOne2(13579));
    EXPECT_EQ(c.countDigitOne3(13579), c.countDigitOne2(13579));
    EXPECT_EQ(767944060, c.countDigitOne(824883294));
    EXPECT_EQ(1737167499, c.countDigitOne(1410065408));
}
