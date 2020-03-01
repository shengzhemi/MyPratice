#include <vector>
using namespace std;
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return NULL;
        }

        vector<int> vec;
        for (int i = 0; i < lists.size(); i++) {
            ListNode *p = lists[i];
            while (p) {
                vec.push_back(p->val);
                p = p->next;
            }
        }

        sort(vec.begin(), vec.end());
        ListNode *mergeResult = new ListNode(0);
        ListNode *pre = mergeResult;
        for (int i = 0; i < vec.size(); i++) {
            ListNode *temp = new ListNode(vec[i]);
            pre->next = temp;
            pre = temp;
        }

        pre = mergeResult->next;
        delete mergeResult;
        return pre;
    }
};
