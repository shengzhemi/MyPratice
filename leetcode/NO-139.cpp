#include "gtest/gtest.h"
#include <set>
#include <unordered_set>

using namespace std;

class WordBreak {
public:
    bool wordBreak(string s, vector<string> &wordDict) {
        //set<string> dict(wordDict.begin(), wordDict.end());
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        //return wordBreakExist(s, dict); 
        //return wordBreakExist2(s, dict); 
        return wordBreakExist3(s, dict); 
    }

    bool wordBreakExist3(string s, const unordered_set<string> &dict) {
        vector<bool> exist; 
        exist.resize(s.size() + 1, false);
        exist[0] = true;

        for (int i = 1; i <= s.size(); i++) {
            if (dict.count(s.substr(0, i))) {
                exist[i] = true;
                continue;
            }

            for (int j = 0; j < i; j++) {
                bool flag = exist[j] && dict.count(s.substr(j, i - j));
                if (flag) {
                    exist[i] = true;
                    break;
                }
            }
        }

        return exist[s.size()];
    }

    bool wordBreakExist2(string s, const set<string> &dict) {
        vector<bool> exist; 
        exist.resize(s.size() + 1, false);
        exist[0] = true;

        for (int i = 1; i <= s.size(); i++) {
            if (dict.count(s.substr(0, i))) {
                exist[i] = true;
                continue;
            }

            for (int j = 0; j < i; j++) {
                bool flag = exist[j] && dict.count(s.substr(j, i - j));
                if (flag) {
                    exist[i] = true;
                    break;
                }
            }
        }

        return exist[s.size()];
    }

    bool wordBreakExist(string s, const set<string> &dict) {
        if (s.size() == 0) {
            return true;
        }

        if (dict.count(s)) {
            return true;
        }

        for (int i = 1; i < s.size(); i++) {
            //std::cout << "string: " << s.substr(0, i) << ", " << s.substr(i, s.size() - i) << std::endl;
            if (wordBreakExist(s.substr(0, i), dict) && wordBreakExist(s.substr(i, s.size() - i), dict)) {
                return true;
            }
        }

        return false;
    }
};

TEST(No139_testsuit1, testcase_1) {
    WordBreak wb;
    vector<string> dict;
    EXPECT_EQ(true, wb.wordBreak("", dict));
    EXPECT_EQ(false, wb.wordBreak("test", dict));
    dict.push_back("leet");
    dict.push_back("code");
    EXPECT_EQ(true, wb.wordBreak("", dict));
    EXPECT_EQ(true, wb.wordBreak("leetcode", dict));
    EXPECT_EQ(false, wb.wordBreak("keetcode", dict));
    dict.push_back("h");
    dict.push_back("e");
    dict.push_back("l");
    dict.push_back("o");
    dict.push_back("w");
    dict.push_back("r");
    dict.push_back("d");
    EXPECT_EQ(true, wb.wordBreak("helloworld", dict));
    EXPECT_EQ(false, wb.wordBreak("t", dict));
    EXPECT_EQ(true, wb.wordBreak("l", dict));
    EXPECT_EQ(true, wb.wordBreak("lll", dict));
    EXPECT_EQ(false, wb.wordBreak(" l", dict));
}

TEST(No139_testsuit2, testcase_big) {
    WordBreak wb;
    vector<string> dict;
    dict.push_back("leet");
    dict.push_back("code");
    dict.push_back("a");
    dict.push_back("b");
    dict.push_back("c");
    dict.push_back("d");
    dict.push_back("e");
    dict.push_back("f");
    dict.push_back("g");
    dict.push_back("h");
    dict.push_back("i");
    dict.push_back("j");
    dict.push_back("k");
    dict.push_back("l");
    dict.push_back("n");
    dict.push_back("m");
    dict.push_back("o");
    dict.push_back("p");
    dict.push_back("q");
    dict.push_back("r");
    dict.push_back("s");
    dict.push_back("t");
    dict.push_back("u");
    dict.push_back("v");
    dict.push_back("w");
    dict.push_back("x");
    dict.push_back("y");
    dict.push_back("z");
    EXPECT_EQ(false, wb.wordBreak("llljiusheafgdsahsaklewpqwafdjschsahefweoefjasjgaewudasafhsahqwoadskjfdshfwjahvsajhvsadsacbzMnsjahcsdfjsabvbsaxnxbcjabd", dict));
    EXPECT_EQ(true, wb.wordBreak("asdfdsakjfhsdfjhsdfkeqwertyuiokkdsjhhdhdjeiuwjqjsjdmndjajhekelkwkwidjdhaahdhuqudajdkjktgoqorutpykakxmnbjskfsabvbsaxnxbcjabd", dict));
    EXPECT_EQ(true, wb.wordBreak("asdfdsakjfhsdfjhsdfkeqwertyuiokkdsjhhdhdjeiuwjqjsjdmndjajhekelkwkwidjdhaahdhuqudajdkjktgoqorutpykakxmnbjskfsabvbsaxnxbcjabadwyerueirortppldakdanvnzmdjasjgasdlfgjweiqoqwpldafgjajdiejthgkjaldoadkgjqijejtkagjqoweiruajgkaskgjadhjgkadjd", dict));
    EXPECT_EQ(true, wb.wordBreak("helloworldthisisshengyi", dict));
}
