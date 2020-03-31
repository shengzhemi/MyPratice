#include "gtest/gtest.h"
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class CheckIfBinarySearchTree{
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST_(root, (long)INT_MAX + 1, (long)INT_MIN - 1);
    }

    bool isValidBST_(TreeNode *root, long upperBound, long lowerBound) {
        if (!root) {
            return true;
        }

        if (root->val <= lowerBound || root->val >= upperBound) {
            return false;
        }

        return isValidBST_(root->right, upperBound, root->val) && isValidBST_(root->left, root->val, lowerBound);
    }
};

TEST(CheckIfBinarySearchTree_testsuilt, test_testcase) {
    CheckIfBinarySearchTree cbt;

}
