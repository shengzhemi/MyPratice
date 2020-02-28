class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = nums.size();
        int last = -1;
        searchRange_(nums, 0, nums.size() - 1, target, first, last);
        if (first == nums.size()) {
            first = -1;
        }

        vector<int> v;
        v.push_back(first);
        v.push_back(last);
        return v;
    }

    void searchRange_(vector<int> &nums, int begin, int end, int target, int &first, int &last) {
        if (end < begin) {
            return;
        }

        if (begin == end || nums[begin] == nums[end]) {
            if (begin < first && nums[begin] == target) {
                first = begin;
            }

            if (end > last && nums[end] == target) {
                last = end;
            }
            return;
        }

        int mid = (begin + end) / 2;
        if (nums[mid] > target) {
            searchRange_(nums, begin, mid - 1, target, first, last);
        } else if (nums[mid] < target) {
            searchRange_(nums, mid + 1, end, target, first, last);
        } else {
            searchRange_(nums, begin, mid, target, first, last);
            searchRange_(nums, mid + 1, end, target, first, last);
        }
    }
};
