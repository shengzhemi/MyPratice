/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        current = NULL;
        ListNode *listSum = NULL;
        int carry = 0;
        while ((l1 != NULL) || (l2 != NULL)) {
            int add1 = getAndWorkNext(l1);
            int add2 = getAndWorkNext(l2);

            int sum = add1 + add2 + carry;
            carry = sum / 10;
            sum = sum % 10;

            if (!insert(listSum, new ListNode(sum))) {
                return NULL;
            }
        }

        if (carry != 0) {
            if (!insert(listSum, new ListNode(carry))) {
                return NULL;
            }
        }

        return listSum;
    }

private:
    bool insert(ListNode *&listSum, ListNode *node) {
        if (node == NULL) {
            return false;
        }

        if (listSum == NULL) {
            listSum = node;
            current = listSum;
        } else {
            current->next = node;
            current = node;
        }

        return true;
    }

    int getAndWorkNext(ListNode *&node) {
        int val = 0;
        if (node != NULL) {
            val = node->val;
            node = node->next;
        }
        return val;
    }
private:
    ListNode *current;
};
