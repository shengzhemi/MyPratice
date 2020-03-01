const int MAX_NUM = 2147483646;
class Solution {
public:
    int reverse(int x) {
        if (x == 0x80000000) {
            return 0;
        }

        int sign = 1;
        if (x < 0) {
            sign = -1;
            x = - x;     
        }
 
        int num = 0;
        while (x) {
            if ((num > MAX_NUM / 10) 
                || ((num == MAX_NUM / 10) && (x % 10 > MAX_NUM % 10))) {
                return 0;
            }

            num = num * 10 + x % 10;
            x /= 10;
        }

        return num * sign;
    }
};
