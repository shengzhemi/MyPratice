#include <vector>
#include <cstdlib>
#include <unordered_map>
#include "gtest/gtest.h"
#include <set>
using namespace std;
struct pair_hash {
    template<class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        return hash<T1>()(p.first) ^ hash<T2>()(p.second);
    }
};

class  GridLamp {
public:
    vector<int> gridIllumination(int N, vector<vector<int> >& lamps, vector<vector<int> >& queries) {
        unordered_map<int, int> xlines;
        unordered_map<int, int> ylines;
        unordered_map<int, int> posDiags;
        unordered_map<int, int> negDiags;
        vector<int> result;
        result.resize(queries.size(), 0);
        set<vector<int> > lampsMap(lamps.begin(), lamps.end());
        for (int i = 0; i < lamps.size(); i++) {
            xlines[lamps[i][0]]++;
            ylines[lamps[i][1]]++;
            posDiags[lamps[i][0] - lamps[i][1]]++;
            negDiags[lamps[i][0] + lamps[i][1]]++;
        }

        for (int i = 0; i < queries.size(); i++) {
            int x = queries[i][0];
            int y = queries[i][1];
            if (xlines[x] > 0 || ylines[y] > 0 || posDiags[x - y] > 0 || negDiags[x + y] > 0) {
                result[i] = 1;
            } else {
                result[i] = 0;
            }

            vector<int> v;
            v.resize(2, 0);
            for (int m = x - 1; m < 2 + x; m++) {
                for (int n = y - 1; n < 2 + y; n++) {
                    if (n >= 0 && m >= 0) {
                        v[0] = m;
                        v[1] = n;
                        if (lampsMap.count(v)) {
                            xlines[m]--;
                            ylines[n]--;
                            posDiags[m - n]--;
                            negDiags[m + n]--;
                            lampsMap.erase(v);
                        }
                    }
                }
            }
        }

        return result;
    }

    vector<int> gridIllumination2(int N, vector<vector<int> >& lamps, vector<vector<int> >& queries) {
        unordered_map<pair<int, int>, int, pair_hash> lampsMap;
        initMap(lampsMap, lamps);
        vector<int> result;
        result.resize(queries.size(), 0);
        for (int i = 0; i < queries.size(); i++) {
            result[i] = judge(lampsMap, queries[i]) ? 1 : 0;
            deleteLmap(lampsMap, queries[i]);
        }

        return result;
    }

    void deleteLmap(unordered_map<pair<int, int>, int, pair_hash> &lamps, vector<int> query) {
        int x = query[0] - 1;
        int y = query[1] - 1;
        for (int i = x; i < 3 + x; i++) {
            for (int j = y; j < 3 + y; j++) {
                if (i >= 0 && j >= 0) {
                    unordered_map<pair<int, int>, int, pair_hash>::iterator it = lamps.find(make_pair(i, j));
                    if (it != lamps.end()) {
                        lamps.erase(it);
                    }
                }
            }
        }
    }

    bool judge(unordered_map<pair<int, int>, int, pair_hash> &lamps, vector<int> query) {
        unordered_map<pair<int, int>, int, pair_hash>::iterator it;
        for (it = lamps.begin(); it != lamps.end(); it++) {
            if (judgeIfIlluminate(it->first.first, it->first.second, query[0], query[1])) {
                return true;
            }
        }
        
        return false;
    }

    void initMap(unordered_map<pair<int, int>, int, pair_hash> &lampsMap, const vector<vector<int> > &lamps) {
        for (int i = 0; i < lamps.size(); i++) {
            lampsMap[make_pair(lamps[i][0], lamps[i][1])] = i;
        } 
    }

    bool judgeIfIlluminate(int x1, int y1, int x2, int y2) {
        return (x1 == x2)
            || (y1 == y2)
            || (abs(x1- x2) == abs(y1 - y2));
    }

    bool judgeIfIlluminate(const vector<int> &light, const vector<int> &grid) {
        return judgeIfIlluminate(light[0], light[1], grid[0], grid[1]);
    }
};

TEST(No1001_testsuilt1, test_case_initMap) {
    GridLamp gl;
    vector<vector<int> > lamps;
    lamps.push_back(vector<int>());
    lamps[0].push_back(0);
    lamps[0].push_back(0);
    lamps.push_back(vector<int>());
    lamps[1].push_back(4);
    lamps[1].push_back(4);
    lamps.push_back(vector<int>());
    lamps[2].push_back(5);
    lamps[2].push_back(1);

    unordered_map<pair<int, int>, int, pair_hash> maps;
    EXPECT_EQ(0, maps.size());

    gl.initMap(maps, lamps);

    unordered_map<pair<int, int>, int, pair_hash>::iterator it;
    EXPECT_EQ(3, maps.size());

    it = maps.find(make_pair(0, 0));
    EXPECT_EQ(true, it != maps.end());
    EXPECT_EQ(0, it->first.first);
    EXPECT_EQ(0, it->first.second);

    it = maps.find(make_pair(4, 4));
    EXPECT_EQ(true, it != maps.end());
    EXPECT_EQ(4, it->first.first);
    EXPECT_EQ(4, it->first.second);

    it = maps.find(make_pair(4, 5));
    EXPECT_EQ(true, it == maps.end());

    it = maps.find(make_pair(5, 1));
    EXPECT_EQ(true, it != maps.end());
    EXPECT_EQ(5, it->first.first);
    EXPECT_EQ(1, it->first.second);
}

TEST(No1001_testsuilt1, test_case_judgeIfIllumanate) {
    GridLamp gl;
    vector<int> light;
    light.push_back(3);
    light.push_back(3);
    
    vector<int> grid;
    grid.push_back(0);
    grid.push_back(0);
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 1;
    grid[1] = 1;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 4;
    grid[1] = 4;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 3;
    grid[1] = 1000;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 3922;
    grid[1] = 3;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 1;
    grid[1] = 4;
    EXPECT_EQ(false, gl.judgeIfIlluminate(light, grid));

    light[0] = 5;
    light[1] = 9;
    EXPECT_EQ(false, gl.judgeIfIlluminate(light, grid));

    grid[0] = 4;
    grid[1] = 8;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 3;
    grid[1] = 7;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 6;
    grid[1] = 10;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 7;
    grid[1] = 11;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 5;
    grid[1] = 8911;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 523;
    grid[1] = 9;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 6;
    grid[1] = 8;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 4;
    grid[1] = 10;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 5;
    grid[1] = 10;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 5;
    grid[1] = 8;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 4;
    grid[1] = 9;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));

    grid[0] = 6;
    grid[1] = 9;
    EXPECT_EQ(true, gl.judgeIfIlluminate(light, grid));
}

TEST(No1001_testsuilt1, test_case_judge) {
    GridLamp gl;
    vector<vector<int> > lamps;
    lamps.push_back(vector<int>());
    lamps[0].push_back(0);
    lamps[0].push_back(0);
    lamps.push_back(vector<int>());
    lamps[1].push_back(4);
    lamps[1].push_back(4);
    lamps.push_back(vector<int>());
    lamps[2].push_back(5);
    lamps[2].push_back(1);

    unordered_map<pair<int, int>, int, pair_hash> maps;
    gl.initMap(maps, lamps);

    vector<int> query;
    query.push_back(0);
    query.push_back(0);
    EXPECT_EQ(true, gl.judge(maps, query));

    query[0] = 4;
    query[1] = 2;
    EXPECT_EQ(true, gl.judge(maps, query));

    query[0] = 5;
    query[1] = 111;
    EXPECT_EQ(true, gl.judge(maps, query));

    query[0] = 45;
    query[1] = 111;
    EXPECT_EQ(false, gl.judge(maps, query));
}

TEST(No1001_testsuilt1, test_case_deleteMap) {
    GridLamp gl;
    vector<vector<int> > lamps;
    lamps.push_back(vector<int>());
    lamps[0].push_back(0);
    lamps[0].push_back(0);
    lamps.push_back(vector<int>());
    lamps[1].push_back(1);
    lamps[1].push_back(0);
    lamps.push_back(vector<int>());
    lamps[2].push_back(0);
    lamps[2].push_back(1);
    lamps.push_back(vector<int>());
    lamps[3].push_back(2);
    lamps[3].push_back(0);
    lamps.push_back(vector<int>());
    lamps[4].push_back(1);
    lamps[4].push_back(1);

    unordered_map<pair<int, int>, int, pair_hash> maps;
    gl.initMap(maps, lamps);
    EXPECT_EQ(5, maps.size());

    vector<int> query;
    query.push_back(0);
    query.push_back(0);
    gl.deleteLmap(maps, query);
    EXPECT_EQ(1, maps.size());

    query[0] = 3;
    query[1] = 5;
    gl.deleteLmap(maps, query);
    EXPECT_EQ(1, maps.size());

    query[0] = 1;
    query[1] = 0;
    gl.deleteLmap(maps, query);
    EXPECT_EQ(0, maps.size());
}

TEST(No1001_testsuilt2, test_case) {
    GridLamp gl;
    vector<vector<int> > lamps;
    lamps.push_back(vector<int>());
    lamps[0].push_back(0);
    lamps[0].push_back(0);
    lamps.push_back(vector<int>());
    lamps[1].push_back(1);
    lamps[1].push_back(1);

    vector<vector<int> > queries;
    queries.push_back(vector<int>());
    queries[0].push_back(1);
    queries[0].push_back(1);
    queries.push_back(vector<int>());
    queries[1].push_back(1);
    queries[1].push_back(0);

    vector<int> result = gl.gridIllumination(5, lamps, queries);
    EXPECT_EQ(2, result.size());
    EXPECT_EQ(1, result[0]);
    EXPECT_EQ(0, result[1]);
}

TEST(No1001_testsuilt2, test_case2) {
    GridLamp gl;
    vector<vector<int> > lamps;
    lamps.push_back(vector<int>());
    lamps[0].push_back(0);
    lamps[0].push_back(0);
    lamps.push_back(vector<int>());
    lamps[1].push_back(2);
    lamps[1].push_back(4);

    vector<vector<int> > queries;
    queries.push_back(vector<int>());
    queries[0].push_back(1);
    queries[0].push_back(1);
    queries.push_back(vector<int>());
    queries[1].push_back(3);
    queries[1].push_back(2);
    queries.push_back(vector<int>());
    queries[2].push_back(3);
    queries[2].push_back(5);

    vector<int> result = gl.gridIllumination(5, lamps, queries);
    EXPECT_EQ(3, result.size());
    EXPECT_EQ(1, result[0]);
    EXPECT_EQ(0, result[1]);
    EXPECT_EQ(1, result[2]);
}
