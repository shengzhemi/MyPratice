#include <vector>
using namespace std;
class Solution {
public:
    string longestPalindrome(string s) {
        size_t startPos = 0;
        size_t lenOfPalindrome = 1;

        size_t size = s.size();
        if (size == 0) {
            return "";
        }

        /*for (size_t len = 2; len <= 1000 && len <= size; len++) {
            for (size_t pos = 0; pos <= size - len; pos++) {
                if (checkIfPalindrome(s, pos, pos + len - 1)) {
                    lenOfPalindrome = len;
                    startPos = pos;
                    break;
                }
            }
        }*/

        vector<vector<bool>> vec;
        for (size_t i = 0; i < size; i++) {
            vec.push_back(vector<bool>());
            for (size_t j = 0; j < size; j++) {
                vec[i].push_back(false);
            }
        }
        for (size_t j = 0; j < size; j++) {
            for (size_t i = 0; i <= j; i++) {
                if (i == j) {
                    vec[i][j] = true;
                } else if (i == j -1) {
                    vec[i][j] = (s[i] == s[j]);
                } else {
                    vec[i][j] = (vec[i + 1][j - 1]) && (s[i] == s[j]);
                }

                if (vec[i][j] && (j - i + 1 > lenOfPalindrome)) {
                    startPos = i;
                    lenOfPalindrome = j - i + 1;
                }
            }
        }

        return string(s, startPos, lenOfPalindrome);
    }

    bool checkIfPalindrome(const string &s, size_t begin, size_t end) {
        while (begin < end) {
            if (s[begin] != s[end]) {
                return false;
            }
            begin++;
            end--;
        }
        return true;
    }
};
