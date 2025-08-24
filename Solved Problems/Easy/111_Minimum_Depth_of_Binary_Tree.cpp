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
    int minDepth(TreeNode* root) {
        if(!root) return NULL;
        if(!root->left) return 1 + minDepth(root->right);
        if(!root->right) return 1 + minDepth(root->left);
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};

/*
1) The minDepth function calculates the minimum depth of a binary tree.
2) If the root is null, it returns 0 (base case).
3) If the left child is null, it recursively calculates the depth of the right subtree.
4) If the right child is null, it recursively calculates the depth of the left subtree.
5) If both children are present, it returns 1 plus the minimum of the depths of the left and right subtrees.

A leaf node is a node that does not have any children (both left and right pointers are null).
*/