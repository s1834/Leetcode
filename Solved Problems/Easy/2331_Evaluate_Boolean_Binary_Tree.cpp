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
    bool evaluateTree(TreeNode* root) {
        if(root->val == 0) return false;
        else if(root->val == 1) return true;
        else if(root->val == 2) return evaluateTree(root->left) || evaluateTree(root->right);
        else return evaluateTree(root->left) && evaluateTree(root->right);
    }
};

/*
1) The evaluateTree function checks the value of the current node.
2) If the value is 0, it returns false (logical AND).
3) If the value is 1, it returns true (logical OR).
4) If the value is 2, it evaluates the left and right subtrees with logical OR.
5) If the value is 3, it evaluates the left and right subtrees with logical AND.
*/