class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> dp;
        dp.push_back(0);
        int maxLength = 0;
        for (int i = 1; i < s.size(); i++) {
            dp.push_back(0);
            if (s[i] == ')') {
                int pre = i - dp[i - 1] - 1;
                if (pre >= 0 && s[pre] == '(') {
                    dp[i] = dp[i - 1] + 2;
                    if (pre > 0) {
                        dp[i] += dp[pre - 1];
                    }
                    maxLength = (dp[i] > maxLength) ? dp[i] : maxLength;
                }
            }
        }
        return maxLength;
    }
};
