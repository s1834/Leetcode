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
    bool isValid(TreeNode* root, long long int mn, long long int mx) {
        if(!root) return true;
        if(root->val < mx && root->val > mn) return isValid(root->left, mn, root->val) && isValid(root->right, root->val, mx);
        return false;
    }

public:
    bool isValidBST(TreeNode* root) {
        return isValid(root, LLONG_MIN, LLONG_MAX);
    }
};

/*
1) The isValid function checks if the current node's value is within the valid range (mn, mx).
2) If the current node is null, it means we've reached a leaf node, and we return true.
3) If the current node's value is not within the valid range, we return false.
4) We recursively check the left and right subtrees with updated ranges.
   - For the left subtree, the maximum value is updated to the current node's value.
   - For the right subtree, the minimum value is updated to the current node's value.
*/