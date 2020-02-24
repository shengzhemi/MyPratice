class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word2.size() == 0) {
            return word1.size();
        }

        vector<int> v;
        for (int i = 0; i <= word2.size(); i++) {
            v.push_back(i);
        }

        for (int i = 1; i <= word1.size(); i++) {
            int last = i;
            for (int j = 1; j <= word2.size(); j++) {
                int current = 0;
                if (word1[i - 1] == word2[j - 1]) {
                    current = v[j - 1];
                } else {
                    current = v[j - 1] < v[j] ? v[j - 1] : v[j];
                    current = current < last ? current : last;
                    current += 1;
                }
                v[j - 1] = last;
                last = current;
            }
            v[word2.size()] = last;
        }

        return v[word2.size()];
    }
};
