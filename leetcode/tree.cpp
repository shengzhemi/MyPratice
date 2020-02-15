#include <cstdlib>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

typedef int treeNodeElem;
typedef struct tagTreeNode {
    treeNodeElem val;
    struct tagTreeNode *leftChild;
    struct tagTreeNode *rightChild;
}TreeNode;

typedef void (*visit_func)(const TreeNode *node);
void default_visit(const TreeNode *node) {
    if (node) {
        cout << node->val << "-->" ;
    }
}

class Tree {
public:
    Tree() {
        root = NULL;
        visit = default_visit;
    }

    ~Tree() {
       deleteTree(root); 
    }

    void buildTree(const vector<treeNodeElem> elems) {    
        if (elems.empty()) {
            return;
        }

        root = makeNode(elems[0]);
        return buildTreeNode(root, elems, 1);
    }

    void preorderTraversal() {
        cout << "Preorder Traversal Binary Tree: ";
        preorderTraversal_(root, visit);
        cout << "END" << endl;
    }

    void preorderTraversal2() {
        stack<TreeNode*> st;
        if (root) {
            st.push(root);
        }

        cout << "Preorder Traversal2 Binary Tree:";
        while (!st.empty()) {
            TreeNode *node = st.top();
            st.pop();
            visit(node);
            
            if (node->rightChild) {
                st.push(node->rightChild);
            }

            if (node->leftChild) {
                st.push(node->leftChild);
            }
        } 
        cout << "END" << endl;
    }
    
    void inorderTraversal2() {
        stack<TreeNode*> st;
        TreeNode *p = root;

        cout << "Inorder Traversal2 Binary Tree:";
        while (!st.empty() || p) {
            if (p) {
                st.push(p);
                p = p->leftChild;
            } else {
                p = st.top();
                st.pop();
                visit(p);
                p = p->rightChild;
            }
        } 
        cout << "END" << endl;
    }

    void inorderTraversal() {
        cout << "Inorder Traversal Binary Tree: ";
        inorderTraversal_(root, visit);
        cout << "END" << endl;
    }
    
    void postorderTraversal() {
        cout << "Postorder Traversal Binary Tree: ";
        postorderTraversal_(root, visit);
        cout << "END" << endl;
    }

    void postorderTraversal2() {
        stack<TreeNode*> st;
        TreeNode *p, *q;
        p = root;
        cout << "Postorder Traversal2 Binary Tree:";
        do {
            while (p) {
                st.push(p);
                p = p->leftChild;
            }

            q = NULL;
            while (!st.empty()) {
                p = st.top();
                st.pop();
                
                if (p->rightChild == q) {
                    visit(p);
                    q = p;
                } else {
                    st.push(p);
                    p = p->rightChild;
                    break;
                }
            }
        
        } while(!st.empty());
        cout << "END" << endl;
    }

    void treeBFS() {
        if (!root) {
            return;
        }

        cout << "BFS Binary Tree: ";
        queue<TreeNode*> q;
        TreeNode *p = root;
        q.push(root);

        while (!q.empty()) {
            p = q.front();
            q.pop();

            visit(p);

            if (p->leftChild) {
                q.push(p->leftChild);
            }

            if (p->rightChild) {
                q.push(p->rightChild);
            }
        }

        cout << "END" << endl;
    }

    void setVisit(visit_func vf) {
        visit = vf;
    }

private:
    TreeNode* makeNode(treeNodeElem elem) {
        TreeNode *node = new TreeNode;
        if (!node) {
            return NULL;
        }

        node->val = elem;
        node->leftChild = NULL;
        node->rightChild = NULL;

        return node;
    }

    void deleteTree(TreeNode *root) {
        if (!root) {
            return;
        }

        if (!root->leftChild) {
            deleteTree(root->leftChild);
        }

        if (!root->rightChild) {
            deleteTree(root->rightChild);
        }

        delete root;
    }

    // middle --> left --> right
    void preorderTraversal_(const TreeNode *root, visit_func vf) {
        if (!root) {
            return;
        }

        vf(root);
        preorderTraversal_(root->leftChild, visit);
        preorderTraversal_(root->rightChild, visit);
    }
    
    // left --> middle --> right
    void inorderTraversal_(const TreeNode *root, visit_func vf) {
        if (!root) {
            return;
        }

        inorderTraversal_(root->leftChild, visit);
        vf(root);
        inorderTraversal_(root->rightChild, visit);
    }

    // left --> right --> middle
    void postorderTraversal_(const TreeNode *root, visit_func vf) {
        if (!root) {
            return;
        }

        postorderTraversal_(root->leftChild, visit);
        postorderTraversal_(root->rightChild, visit);
        vf(root);
    }

    void buildTreeNode(TreeNode *root, const vector<treeNodeElem> &elems, int nodeNo) {
        if (!root) {
            return;
        }

        size_t leftChildNo = 2 * nodeNo;
        size_t rightChildNo = 2 * nodeNo + 1;
        if (leftChildNo <= elems.size()) {
            root->leftChild = makeNode(elems[leftChildNo - 1]);
            buildTreeNode(root->leftChild, elems, leftChildNo);
        }

        if (rightChildNo <= elems.size()) {
            root->rightChild = makeNode(elems[rightChildNo - 1]);
            buildTreeNode(root->rightChild, elems, rightChildNo);
        }
    }


private:
    TreeNode *root;
    visit_func visit; 
};

int main(int argc, char **argv) {
    treeNodeElem elems[] = {1, 2, 4, 6, 3, 8, 5, 9};
    vector<treeNodeElem> v(elems, elems + sizeof(elems) / sizeof(treeNodeElem));
    
    Tree tree;
    tree.buildTree(v);
    tree.preorderTraversal();
    tree.preorderTraversal2();
    tree.inorderTraversal();
    tree.inorderTraversal2();
    tree.postorderTraversal();
    tree.postorderTraversal2();
    tree.treeBFS();

    return 0;
}



