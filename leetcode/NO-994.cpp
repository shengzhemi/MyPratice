#include "gtest/gtest.h"
#include <stack>
using namespace std;
class Orange{
public:
    int orangesRotting(vector<vector<int> >& grid) {
        stack<vector<int> > s1;
        stack<vector<int> > s2;

        int oranges = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 2) {
                    vector<int> v;
                    v.resize(2);
                    v[0] = i;
                    v[1] = j;
                    s1.push(v);
                } else if (grid[i][j] == 1) {
                    oranges++;
                }
            }
        }


        int times = 0;
        int orangesBad = 0;
        while (!s1.empty() || !s2.empty()) {
            orangesBad += getBadOranges(grid, s1, s2, times);
            orangesBad += getBadOranges(grid, s2, s1, times);

        }

        if (oranges != orangesBad) {
            return -1;
        }
        return times;
    }

    int getBadOranges(vector<vector<int> > &grid, stack<vector<int> > &src, stack<vector<int> > &dest, int &times) {
        int orangesBad = 0;
        int index[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        while (!src.empty()) {
            vector<int> v = src.top();
            src.pop();
            for (int i = 0; i < 4; i++) {
                if (v[0] + index[i][0] >= 0 && v[1] + index[i][1] >= 0 && v[0] + index[i][0] < grid.size() && v[1] + index[i][1] < grid[0].size()) {
                    if (grid[v[0] + index[i][0]][v[1] + index[i][1]] == 1) {
                        grid[v[0] + index[i][0]][v[1] + index[i][1]] = 2;
                        vector<int> tmp;
                        tmp.resize(2);
                        tmp[0] = v[0] + index[i][0];
                        tmp[1] = v[1] + index[i][1];
                        dest.push(tmp);
                        orangesBad++;
                    }
                }
            }
        }

        if (!dest.empty()) {
            times++;
        }

        return orangesBad;
    }
};
