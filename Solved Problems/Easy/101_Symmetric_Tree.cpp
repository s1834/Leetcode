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
private:
    bool sameTree(TreeNode* rootLeft, TreeNode* rootRight) {
        if(!rootLeft && !rootRight) return true;
        if(!rootLeft || !rootRight) return false;
        if(rootLeft->val != rootRight->val) return false;
        return sameTree(rootLeft->left, rootRight->right) && sameTree(rootLeft->right, rootRight->left);
    }

public:
    bool isSymmetric(TreeNode* root) {
        return sameTree(root->left, root->right);
    }
};