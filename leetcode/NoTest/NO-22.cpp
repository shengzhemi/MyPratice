class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> v;
        generateParenthesisRecursion(v, "", 0, 0, n);
        //generateParenthesisIteration(v, n);
        return v;
    }

    void generateParenthesisRecursion(vector<string> &v, string s, int left, int right, int n) {
        if (left > n || right > n || right > left) {
            return;
        }

        if (left == n && right == n) {
            v.push_back(s);
        }

        generateParenthesisRecursion(v, s + "(", left + 1, right, n);
        generateParenthesisRecursion(v, s + ")", left, right + 1, n);
    }

    /*void generateParenthesisIteration(vector<string> &v, int n) {
        stack<char> s;
        s.push('(');
        int left = 0;
        int right = 0;
        string str;
        while (!s.empty()) {
            char ch = s.top();
            s.pop();
            str += ch;
            (ch == '(') ? left++ : right++;
            if (ch == '(') {
                if (left == n && right < n) {
                    s.push(')');
                    continue;
                }
            } else {
                if (right > left) {
                    continue;
                }
            }

            if (left == right && left == n) {
                v.push_back(str);
                left = 0;
                right = 0;
                str = "";
                continue;
            }

            if (left > n || right > n || right > left) {
                left = 0;
                right = 0;
                str = "";
                continue;
            }

            s.push(')');
            s.push('(');
        }
    }*/
};
