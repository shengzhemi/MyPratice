class Solution {
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
    const int maxNum = 2147483647;
    const int minNum = -2147483648;
};
