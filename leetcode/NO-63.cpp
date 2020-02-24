class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid.empty() || obstacleGrid[0].empty()) {
            return 0;
        }

        preprocess(obstacleGrid);

        int a[101] = {0};
        a[1] = 1;
        for (int i = 1; i <= obstacleGrid.size(); i++) {
            int last = 0;
            for (int j = 1; j <= obstacleGrid[i - 1].size(); j++) {
                int current = 0;
                if (obstacleGrid[i - 1][j - 1]) {
                    current = 0;
                } else {
                    current = last + a[j];
                }
                last = current;
                a[j] = current;
            }
        }
        return a[obstacleGrid[0].size()];
    }

    void preprocess(vector<vector<int>>& obstacleGrid) {
        for (int i = obstacleGrid.size() - 1; i >= 0; i--) {
            for (int j = obstacleGrid[i].size() - 1; j >= 0; j--) {
                if ((i == obstacleGrid.size() - 1) && (j == obstacleGrid[i].size() - 1)) {
                    continue;
                }

                if (isDownObstacle(obstacleGrid, i, j) && isRightObstacle(obstacleGrid, i, j)) {
                    obstacleGrid[i][j] = 1;
                }
            }
        }
    }

    bool isRightObstacle(vector<vector<int>>& obstacleGrid, int i, int j) {
        return (j == obstacleGrid[0].size() - 1) || (obstacleGrid[i][j + 1]);
    }

    bool isDownObstacle(vector<vector<int>>& obstacleGrid, int i, int j) {
        return (i == obstacleGrid.size() - 1) || (obstacleGrid[i + 1][j]);
    }
};
