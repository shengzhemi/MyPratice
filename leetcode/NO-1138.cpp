#include "gtest/gtest.h"
#include <cstring>
#include <iostream>
using namespace std;

class BoardPath{
public:
    string alphabetBoardPath(string target) {
        string path = "";
        string src = "a" + target;
        for (int i = 0; i < src.size() - 1; i++) {
            path += getPathFromTwoAlphabets(src[i], src[i + 1]);
        }

        return path;
    }

    bool checkStringPath(string path, char startChar, string target) {
        string src = startChar + target;
        int startPos = 0;
        for (int i = 0; i < src.size() - 1; i++) {
            string p = getNextPath(path, startPos);
            if (!checkPath(p, src[i], src[i + 1])) {
                return false;
            }
            startPos += p.size();
        }
        return true;
    }

    string getNextPath(string path, int start) {
        int startPos = start;
        while (startPos < path.size() && path[startPos] != '!') {
            startPos++;
        }
        return path.substr(start, startPos - start + 1);
    }

    bool checkPath(string path, char src, char dest) {
        if (src == dest) {
            return path == "!";
        }

        int indexSrc = src - 'a';
        int indexSrcX = indexSrc % NUM_PER_LINE;
        int indexSrcY = indexSrc / NUM_PER_LINE;

        for (int i = 0; i < path.size(); i++) {
            if (path[i] == 'R') {
                indexSrcX++;
            } else if (path[i] == 'L') {
                indexSrcX--;
            } else if (path[i] == 'U') {
                indexSrcY--;
            } else if (path[i] == 'D') {
                indexSrcY++;
            } else if (path[i] == '!') {
                int index = indexSrcY * NUM_PER_LINE + indexSrcX;
                return ('a' + index) == dest;
            } else {
                return false;
            }
        }
        return false;
    }

    string getPathFromTwoAlphabets(char src, char dest) {
        if (src == dest) {
            return "!";
        }

        string path = "";
        if (src == 'z') {
            path += "U";
            src = 'u';
        }
        
        bool downFlag = false;
        if (dest == 'z') {
            downFlag = true;
            dest = 'u';
        }

        int indexSrc = src - 'a';
        int indexDest = dest - 'a';

        int indexSrcX = indexSrc % NUM_PER_LINE;
        int indexSrcY = indexSrc / NUM_PER_LINE;
        int indexDestX = indexDest % NUM_PER_LINE;
        int indexDestY = indexDest / NUM_PER_LINE;

        string charMoveX = "";
        int moveX = 0;
        if (indexSrcX > indexDestX) {
            charMoveX = "L";
            moveX = indexSrcX - indexDestX;
        } else if (indexSrcX < indexDestX) {
            charMoveX = "R";
            moveX = indexDestX - indexSrcX;
        }

        string charMoveY = "";
        int moveY = 0;
        if (indexSrcY > indexDestY) {
            charMoveY = "U";
            moveY = indexSrcY - indexDestY;
        } else if (indexSrcY < indexDestY) {
            charMoveY = "D";
            moveY = indexDestY - indexSrcY;
        }
        
        for (int i = 0; i < moveX; i++) {
            path += charMoveX;
        }

        for (int i = 0; i < moveY; i++)  {
            path += charMoveY;
        }

        if (downFlag) {
            path += "D";
        }

        path += "!";
        return path;
    }
private:
    const static int NUM_PER_LINE = 5;

};

TEST(NO1138_testsuit1, test_case1) {
    BoardPath bp;
    EXPECT_EQ("R!", bp.getPathFromTwoAlphabets('a', 'b'));
    EXPECT_EQ("RRRR!", bp.getPathFromTwoAlphabets('a', 'e'));
    EXPECT_EQ("RRRRD!", bp.getPathFromTwoAlphabets('a', 'j'));
    EXPECT_EQ("RRDD!", bp.getPathFromTwoAlphabets('a', 'm'));
    EXPECT_EQ("DDDDD!", bp.getPathFromTwoAlphabets('a', 'z'));
    EXPECT_EQ("LLLLDD!", bp.getPathFromTwoAlphabets('t', 'z'));
    EXPECT_EQ("!", bp.getPathFromTwoAlphabets('z', 'z'));
    EXPECT_EQ("URR!", bp.getPathFromTwoAlphabets('z', 'w'));
    EXPECT_EQ("!", bp.getPathFromTwoAlphabets('a', 'a'));
    EXPECT_EQ("RDD!", bp.getPathFromTwoAlphabets('f', 'q'));
    EXPECT_EQ("LLLLDDD!", bp.getPathFromTwoAlphabets('o', 'z'));
    EXPECT_EQ("URRUUU!", bp.getPathFromTwoAlphabets('z', 'h'));
    EXPECT_EQ("LDD!", bp.getPathFromTwoAlphabets('q', 'z'));
    EXPECT_EQ("RRRR!", bp.getPathFromTwoAlphabets('f', 'j'));
    EXPECT_EQ("LLLL!", bp.getPathFromTwoAlphabets('j', 'f'));
}

TEST(NO1138_testsuit1, test_case2) {
    BoardPath bp;
    EXPECT_EQ(true, bp.checkPath("LLLL!", 'j', 'f'));
    EXPECT_EQ(false, bp.checkPath("LLLL", 'j', 'f'));
    EXPECT_EQ(false, bp.checkPath("LLDL!", 'j', 'f'));
    EXPECT_EQ(true, bp.checkPath("LLLLDDD!", 'o', 'z'));
    EXPECT_EQ(true, bp.checkPath(bp.getPathFromTwoAlphabets('o', 'z'), 'o', 'z'));
    EXPECT_EQ(true, bp.checkPath(bp.getPathFromTwoAlphabets('a', 'l'), 'a', 'l'));
    EXPECT_EQ(true, bp.checkPath(bp.getPathFromTwoAlphabets('x', 'p'), 'x', 'p'));
}

TEST(NO1138_testsuit2, test_case1) {
    BoardPath bp;
    EXPECT_EQ(true, bp.checkStringPath(bp.alphabetBoardPath("leetcode"), 'a', "leetcode"));
    EXPECT_EQ(true, bp.checkStringPath(bp.alphabetBoardPath("leet"), 'a', "leet"));
    EXPECT_EQ("RDD!RRRUU!!DDD!", bp.alphabetBoardPath("leet"));
    EXPECT_EQ("", bp.alphabetBoardPath(""));
    EXPECT_EQ("!", bp.alphabetBoardPath("a"));
    EXPECT_EQ(true, bp.checkStringPath(bp.alphabetBoardPath("helloworld"), 'a', "helloworld"));
    EXPECT_EQ(false, bp.checkStringPath(bp.alphabetBoardPath("helloworld"), 'a', "kelloworld"));
}
