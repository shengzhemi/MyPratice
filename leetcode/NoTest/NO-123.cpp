class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }

        // 将prices[j] - prices[i]处理成s[i] + .... + s[j]的形式
        // 即变为处理连续和的问题
        for (int i = 0; i < prices.size() - 1; i++) {
            prices[i] = prices[i + 1] - prices[i];
        }
        prices[prices.size() - 1] = 0;

        int result = maxProfit_(prices, 2);
        return result > 0 ? result : 0;
    }

    int maxProfit_(vector<int> &prices, int times) {
        vector<int> pre; // 存放前times - 1个子段的最大和[times - 1][j]
        for (int i = 0; i <= prices.size(); i++) {
            pre.push_back(0);
        }

        int total = 0;
        for (int i = 1; i <= times; i++) {
            int maxNum = 0;
            int last = 0;
            for (int j = 1; j <= prices.size(); j++) {
                int current = 0;
                if (pre[j - 1] < last) {
                    current = last + prices[j - 1];
                } else {
                    current = pre[j - 1] + prices[j - 1];
                }

                pre[j - 1] = maxNum;
                if (maxNum < current) {
                    maxNum = current;
                }
                last = current;
            }
            
            if (total < maxNum) {
                total = maxNum;
            }
        }
        return total;
    }
};
