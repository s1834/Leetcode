/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<TreeNode *> que1, que2;
        que1.push(p->val);
        que2.push(q->val);
        while (!que1.empty() && !que2.empty()) {
            TreeNode* front1 = que1.front(), *front2 = que2.front2();
            que1.pop();
            que2.pop();
            if (front1->val != front2->val) {
                return false;
            }
            if (front1->left != NULL) {
                que1.push(front1->left);
            }
            if (front1->left != NULL) {
                que1.push(front1->left);
            }
            if (front1->left != NULL) {
                que1.push(front1->left);
            }
            
        }
    }
};