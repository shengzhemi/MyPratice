class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        return longestCommonSubsequence2(text1, text2);
    }

    int longestCommonSubsequence1(string text1, string text2) {
        if (text1.empty() || text2.empty()) {
            return 0;
        }

        vector<vector<int>> v;
        for (int i = 0; i <= text1.size(); i++) {
            v.push_back(vector<int>());
            for (int j = 0; j <= text2.size(); j++) {
                v[i].push_back(0);
            }
        }

        for (int i = 1; i <= text1.size(); i++) {
            for (int j = 1; j <= text2.size(); j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    v[i][j] = v[i - 1][j - 1] + 1;
                } else {
                    v[i][j] = (v[i - 1][j] > v[i][j - 1]) ? v[i - 1][j] : v[i][j - 1];
                }
            }
        }

        return v[text1.size()][text2.size()];
    }

    int longestCommonSubsequence2(string text1, string text2) {
        if (text1.empty() || text2.empty()) {
            return 0;
        }

        vector<int> v;
        for (int i = 0; i <= text2.size(); i++) {
            v.push_back(0);
        }

        for (int i = 1; i <= text1.size(); i++) {
            int last = 0;
            for (int j = 1; j <= text2.size(); j++) {
                int current = 0;
                if (text1[i - 1] == text2[j - 1]) {
                    current = v[j - 1] + 1;
                } else {
                    current = last > v[j] ? last : v[j];
                }
                v[j - 1] = last;
                last = current;
            }
            v[text2.size()] = last;
        }

        return v[text2.size()];
    }
};
