#include "gtest/gtest.h"
#include <queue>
#include <unordered_set>
using namespace std;

class SlidingPuzzle{
public:
    int slidingPuzzle(vector<vector<int> >& board) {
        if (board.size() == 0 || board[0].size() == 0) {
            return -1;
        }

        const int finalState = 0x5054321;
        int initState = getInitState(board);
        queue<int> q;
        queue<int> q2;
        unordered_set<int> s;
        q.push(initState);
        s.insert(initState);
        bool findFlag = false;
        int times = 0;
        while (!q.empty() || !q2.empty()) {
            if (findFinal(q, q2, s, times, finalState)) {
                findFlag = true;
                break;
            }

            if (findFinal(q2, q, s, times, finalState)) {
                findFlag = true;
                break;
            }
        }

        return findFlag ? times : -1;
    }

    bool findFinal(queue<int> &src, queue<int> &dest, unordered_set<int> &flags, int &times, int finalState) {
        while (!src.empty()) {
            int state = src.front();
            src.pop();
            if (finalState == state) {
                return true;
            }

            getNextStates(state, dest, flags);
        }

        if (!dest.empty()) {
            times++;
        }

        return false;
    }

    int getInitState(vector<vector<int> > &board) {
        int zeroIndex = 0;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 0) {
                    zeroIndex = i * 3 + j;
                }
            }
        }
        int nextStatus = board[0][0] + (board[0][1] << 4) + (board[0][2] << 8) + (board[1][0] << 12) + (board[1][1] << 16) + (board[1][2]<< 20) + (zeroIndex << 24);
        return nextStatus;
    }

    void getNextStates(int currentStatus, queue<int> &statusQueue, unordered_set<int> &flag) {
        int index[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; 
        int zeroIndex = (currentStatus >> 24) & 0x0F;
        int y = zeroIndex % 3;
        int x = zeroIndex / 3;
        for (int i = 0; i < 4; i++) {
            int newX = x + index[i][0];
            int newY = y + index[i][1];
            if (newX >= 0 && newX <= 1 && newY >= 0 && newY <= 2) {
                int newIndex = newX * 3 + newY;
                int nextStatus = getNextState(currentStatus, zeroIndex, newIndex);
                if (0 == flag.count(nextStatus)) {
                    flag.insert(nextStatus);
                    statusQueue.push(nextStatus);
                }
            }
        }
    }

    int getNextState(int currentStatus, int zeroIndex, int changeIndex) {
        int a[6] = {currentStatus & 0x0F, (currentStatus >> 4) & 0x0F, (currentStatus >> 8) & 0x0F,
                    (currentStatus >> 12) & 0x0F, (currentStatus >> 16) & 0x0F, (currentStatus >> 20) & 0x0F};
        int temp = a[zeroIndex];
        a[zeroIndex] = a[changeIndex];
        a[changeIndex] = temp;

        int nextStatus = a[0] + (a[1] << 4) + (a[2] << 8) + (a[3] << 12) + (a[4] << 16) + (a[5] << 20) + (changeIndex << 24);
        return nextStatus;
    }
};

TEST(No773_testsuit1, testcase1) {
    SlidingPuzzle sp;
    EXPECT_EQ(0x2354021, sp.getNextState(0x5054321, 5, 2));
    EXPECT_EQ(0x4504321, sp.getNextState(0x5054321, 5, 4));
    EXPECT_EQ(0x0543210, sp.getNextState(0x1543201, 1, 0));
    EXPECT_EQ(0x0543210, sp.getNextState(0x3540213, 3, 0));
}

TEST(No773_testsuit1, testcase2) {
    SlidingPuzzle sp;
    unordered_set<int> s;
    int initState = 0x4305214;
    s.insert(initState);
    queue<int> q;
    sp.getNextStates(initState, q, s);
    EXPECT_EQ(3, q.size());
    int next = q.front();
    q.pop();
    EXPECT_EQ(0x1315204, next);
    next = q.front();
    q.pop();
    EXPECT_EQ(0x5035214, next);
    next = q.front();
    q.pop();
    EXPECT_EQ(0x3350214, next);
    EXPECT_EQ(1, s.count(initState));
    EXPECT_EQ(1, s.count(0x1315204));
    EXPECT_EQ(1, s.count(0x5035214));
    EXPECT_EQ(1, s.count(0x3350214));
}

TEST(No773_testsuit1, testcase3) {
    SlidingPuzzle sp;
    vector<vector<int> >board;
    board.resize(2);
    board[0].resize(3, 0);
    board[1].resize(3, 0);
    board[0][0] = 1;
    board[0][1] = 2;
    board[0][2] = 3;
    board[1][0] = 4;
    board[1][1] = 5;
    board[1][2] = 0;
    EXPECT_EQ(0x5054321, sp.getInitState(board));
}
