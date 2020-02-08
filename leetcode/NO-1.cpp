#include <map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ret;
        /*for (int i = 0; i < nums.size() - 1; i++) {
            int sub = target - nums[i];
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] == sub) {
                    ret.push_back(i);
                    ret.push_back(j);
                    return ret;
                }
            }
        }*/

        map<int, int> numToIndex;
        for (int i = 0; i < nums.size(); i++) {
            int sub = target - nums[i];
            map<int, int>::iterator it = numToIndex.find(sub);
            if (it != numToIndex.end()) {
                ret.push_back(it->second);
                ret.push_back(i);
                return ret;
            }

            numToIndex[nums[i]] = i;
        }

        return ret;
    }
};
