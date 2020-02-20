class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 0 || n == 0) {
            return 0;
        }

        int a[101] = {0};
        a[1] = 1;
        for (int i = 1; i <= m; i++) {
            int last = 0;
            for (int j = 1; j <= n; j++) {
                int current = last + a[j];
                last = current;
                a[j] = current;
            }
        }
        return a[n];
    }
};
