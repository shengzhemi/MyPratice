class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }

        vector<int> v;
        int sum = 0;
        for (int i = 1; i <= grid[0].size(); i++) {
            sum += grid[0][i - 1];
            v.push_back(sum);
        }

        for (int i = 2; i <= grid.size(); i++) {
            int last = v[1];
            for (int j = 1; j <= grid[i - 1].size(); j++) {
                int current = (v[j] > last) ? last : v[j];
                current += grid[i - 1][j - 1];

                v[j - 1] = last;
                last = current;
            }
            v[grid[i - 1].size()] = last;
        }

        return v[grid[0].size()];
    }
};
