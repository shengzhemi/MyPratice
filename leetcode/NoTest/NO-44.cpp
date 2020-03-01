#include <vector>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        return isMatchDP2(s, p);
    }

private:
    bool isMatch_(const char *s, const char *p) {
        if (*p == 0) {
            return *s == 0;
        }

        bool firstMatch = (*s == *p) || (*p == '?');
        if (*p == '*') {
            return isMatch_(s, p + 1) || isMatch_(s + 1, p) || isMatch_(s + 1, p + 1);
        } else {
            return firstMatch && isMatch_(++s, ++p);
        }
    }

    bool isMatchDP(string s, string p) {
        vector<vector<bool>> v;
        v.push_back(vector<bool>());
        v[0].push_back(true);

        for (int i = 1; i <= s.size(); i++) {
            v.push_back(vector<bool>());
            v[i].push_back(false);
        }

        for (int i = 1; i <= p.size(); i++) {
            v[0].push_back(v[0][i - 1] && (p[i - 1] == '*'));
        }

        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= p.size(); j++) {
                bool currentMatch = (s[i - 1] == p[j - 1]) || (p[j - 1] == '?');
                v[i].push_back((currentMatch && v[i - 1][j - 1]) 
                            || ((p[j - 1] == '*') && (v[i - 1][j - 1] || v[i - 1][j] || v[i][j - 1])));
            }
        }

        return v[s.size()][p.size()];
    }

    bool isMatchDP2(string s, string p) {
        vector<bool> v;
        v.push_back(true);
        for (int i = 1; i <= p.size(); i++) {
            v.push_back(v[i - 1] && (p[i - 1] == '*'));
        }

        for (int i = 1; i <= s.size(); i++) {
            bool last = false;
            bool current = false;
            for (int j = 1; j <= p.size(); j++) {
                bool currentMatch = (s[i - 1] == p[j - 1]) || (p[j - 1] == '?');
                current = (currentMatch && v[j - 1]) || ((p[j - 1] == '*') && (v[j - 1] || v[j] || last));
                v[j - 1] = last;
                last = current;
            }
            v[p.size()] = current;
        }

        return v[p.size()];
    }
};
